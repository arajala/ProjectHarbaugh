#include "chemotaxis.hpp"

static gboolean on_draw_event(GtkWidget* widget, cairo_t* cr, gpointer usr_data) {
	pthread_mutex_lock(&agent.lock);
	// Draw the chemical gradient
	int width, height;
	GtkWidget* win = gtk_widget_get_toplevel(widget);
	gtk_window_get_size(GTK_WINDOW(win), &width, &height);
	cairo_set_source_rgb(cr, 0.7f, 0.2f, 0.0f);
	cairo_translate(cr, width/2, height/2);
	cairo_pattern_t* rad_grad;
	rad_grad = cairo_pattern_create_radial(0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 350.0f);
	cairo_pattern_add_color_stop_rgb(rad_grad, 0.0f, 1.0f, 1.0f, 0.0f);
	cairo_pattern_add_color_stop_rgb(rad_grad, 0.8f, 0.0f, 0.0f, 0.0f);
	cairo_set_source(cr, rad_grad);
	cairo_arc(cr, 0.0f, 0.0f, 200.0f, 0.0f, 2.0f*M_PI);
	cairo_fill(cr);

	// Draw the agent
	float agent_x = agent.x;
	float agent_y = agent.y;
	float agent_ang = agent.ang;
	float wheel_l_x = agent_x+10.0f*sin(agent_ang-M_PI/2.0f);
	float wheel_l_y = agent_y+10.0f*cos(agent_ang-M_PI/2.0f);
	float wheel_r_x = agent_x+10.0f*sin(agent_ang+M_PI/2.0f);
	float wheel_r_y = agent_y+10.0f*cos(agent_ang+M_PI/2.0f);
	float sense_l_x = agent_x+10.0f*sin(agent_ang-M_PI/4.0f);
	float sense_l_y = agent_y+10.0f*cos(agent_ang-M_PI/4.0f);
	float sense_r_x = agent_x+10.0f*sin(agent_ang+M_PI/4.0f);
	float sense_r_y = agent_y+10.0f*cos(agent_ang+M_PI/4.0f);
	// === Draw the body
	cairo_set_source_rgb(cr, 0.2f, 0.7f, 0.0f);
	cairo_arc(cr, agent_x, agent_y, 10.0f, 0.0f, 2.0f*M_PI);
	cairo_fill(cr);
	// === Draw the wheels
	cairo_set_source_rgb(cr, 0.2f, 0.0f, 0.5f);
	cairo_arc(cr, wheel_l_x, wheel_l_y, 5.0f, 0.0f, 2.0f*M_PI);
	cairo_arc(cr, wheel_r_x, wheel_r_y, 5.0f, 0.0f, 2.0f*M_PI);
	cairo_fill(cr);
	// === Draw the sensors
	cairo_set_source_rgb(cr, 0.8f, 0.0f, 0.1f);
	cairo_arc(cr, sense_l_x, sense_l_y, 3.0f, 0.0f, 2.0f*M_PI);
	cairo_arc(cr, sense_r_x, sense_r_y, 3.0f, 0.0f, 2.0f*M_PI);
	cairo_fill(cr);

	// Queue for redraw
	gtk_widget_queue_draw(widget);
	pthread_mutex_unlock(&agent.lock);

	return FALSE;
}

static void* simulation_loop(void* arg) {
	while (1) {
		agent.update();
		Sleep(100);
	}
	return NULL;
}

int main(int argc, char** argv) {
	// Start chemotaxis simulation in new thread
	pthread_mutex_init(&agent.lock, NULL);
	pthread_t simulation_thread;
	pthread_create(&simulation_thread, NULL, &simulation_loop, NULL);

	// Start graphics systems
	GtkWidget* window;
	GtkWidget* draw_area;
	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	draw_area = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window), draw_area);
	g_signal_connect(G_OBJECT(draw_area), "draw", G_CALLBACK(on_draw_event), NULL);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);  
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
	gtk_window_set_title(GTK_WINDOW(window), "Chemotaxis");
	gtk_widget_show_all(window);
	gtk_main();

	return 0;
}

agent_t::agent_t() {
	unsigned int i;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(-0.99,0.99);
	for (i = 0; i < 6; ++i) {
		nls_wgts[i] = dis(gen);
		nrs_wgts[i] = dis(gen);
		nre_wgts[i] = dis(gen);
		nex_wgts[i] = dis(gen);
		nlm_wgts[i] = dis(gen);
		nrm_wgts[i] = dis(gen);
	}
	x = -100.0f;
	y = 50.0f;
	ang = 3.0f*M_PI/2.0f;
	neuron_l_sense = 0.0f;
	neuron_r_sense = 0.0f;
	neuron_reinforce = 0.0f;
	neuron_extra = 0.0f;
	neuron_l_motor = 0.0f;
	neuron_r_motor = 0.0f;
}

void agent_t::update() {
	float agent_x, agent_y, agent_ang;
	float sense_l_x, sense_l_y, sense_r_x, sense_r_y;
	float sense_l, sense_r, sense_avg;
	static float prev_sense_avg = 0.0f;
	float reinforcement;
	pthread_mutex_lock(&agent.lock);
	agent_x = x;
	agent_y = y;
	agent_ang = ang;

	// Compute sensor/reinforcement inputs
	sense_l_x = agent_x+10.0f*sin(agent_ang-M_PI/4.0f);
	sense_l_y = agent_y+10.0f*cos(agent_ang-M_PI/4.0f);
	sense_r_x = agent_x+10.0f*sin(agent_ang+M_PI/4.0f);
	sense_r_y = agent_y+10.0f*cos(agent_ang+M_PI/4.0f);
	sense_l = 250.0f - sqrt((CENTER_X-sense_l_x)*(CENTER_X-sense_l_x) + 
		(CENTER_Y-sense_l_y)*(CENTER_Y-sense_l_y));
	sense_r = 250.0f - sqrt((CENTER_X-sense_r_x)*(CENTER_X-sense_r_x) + 
		(CENTER_Y-sense_r_y)*(CENTER_Y-sense_r_y));
	sense_avg = (sense_l+sense_r) / 2.0f;
	reinforcement = sense_avg - prev_sense_avg;
	if (reinforcement < 0) reinforcement = 0.0f;
	std::cout << "Reinforcement score = " << reinforcement << std::endl;

	// Apply inputs
	neuron_l_sense += sense_l * nls_wgts[NLS];
	neuron_r_sense += sense_r * nrs_wgts[NRS];
	neuron_reinforce += reinforcement * nre_wgts[NRE];

	// Propogate
	neuron_l_sense += neuron_r_sense * nrs_wgts[NLS];
	neuron_l_sense += neuron_reinforce * nre_wgts[NLS];
	neuron_l_sense += neuron_extra * nex_wgts[NLS];
	neuron_l_sense += neuron_l_motor * nlm_wgts[NLS];
	neuron_l_sense += neuron_r_motor * nrm_wgts[NLS];

	neuron_r_sense += neuron_l_sense * nls_wgts[NRS];
	neuron_r_sense += neuron_reinforce * nre_wgts[NRS];
	neuron_r_sense += neuron_extra * nex_wgts[NRS];
	neuron_r_sense += neuron_l_motor * nlm_wgts[NRS];
	neuron_r_sense += neuron_r_motor * nrm_wgts[NRS];

	neuron_reinforce += neuron_l_sense * nls_wgts[NRE];
	neuron_reinforce += neuron_r_sense * nrs_wgts[NRE];
	neuron_reinforce += neuron_extra * nex_wgts[NRE];
	neuron_reinforce += neuron_l_motor * nlm_wgts[NRE];
	neuron_reinforce += neuron_r_motor * nrm_wgts[NRE];

	neuron_extra += neuron_l_sense * nls_wgts[NEX];
	neuron_extra += neuron_r_sense * nrs_wgts[NEX];
	neuron_extra += neuron_reinforce * nre_wgts[NEX];
	neuron_extra += neuron_extra * nex_wgts[NEX];
	neuron_extra += neuron_l_motor * nlm_wgts[NEX];
	neuron_extra += neuron_r_motor * nrm_wgts[NEX];

	neuron_l_motor += neuron_l_sense * nls_wgts[NLM];
	neuron_l_motor += neuron_r_sense * nrs_wgts[NLM];
	neuron_l_motor += neuron_reinforce * nre_wgts[NLM];
	neuron_l_motor += neuron_extra * nex_wgts[NLM];
	neuron_l_motor += neuron_l_motor * nlm_wgts[NLM];
	neuron_l_motor += neuron_r_motor * nrm_wgts[NLM];

	neuron_r_motor += neuron_l_sense * nls_wgts[NRM];
	neuron_r_motor += neuron_r_sense * nrs_wgts[NRM];
	neuron_r_motor += neuron_reinforce * nre_wgts[NRM];
	neuron_r_motor += neuron_extra * nex_wgts[NRM];
	neuron_r_motor += neuron_l_motor * nlm_wgts[NRM];
	neuron_r_motor += neuron_r_motor * nrm_wgts[NRM];

	// Drive motors
	float delta_forward, delta_ang;
	delta_forward = (neuron_l_motor+neuron_r_motor) / 2.0f / 10000.0f;
	if (delta_forward > 5.0f) delta_forward = 5.0f;
	if (delta_forward < -5.0f) delta_forward = -5.0f;
	delta_ang = (neuron_r_motor - neuron_l_motor) / 10.0f / 10000.0f;
	if (delta_ang > 2.0f*M_PI-0.3f) delta_ang = 2.0f*M_PI-0.3f;
	if (delta_ang < -2.0f*M_PI+0.3f) delta_ang = -2.0f*M_PI+0.3f;
	x += delta_forward * sin(agent_ang);
	y += delta_forward * cos(agent_ang);
	ang += delta_ang;

	pthread_mutex_unlock(&agent.lock);
	std::cout << "Angle = " << ang << std::endl;

	prev_sense_avg = sense_avg;
}