#include "Player.hpp"

using namespace std;

Player player;

static gboolean on_draw_event(GtkWidget* widget, cairo_t* cr, gpointer usr_data) {

	int width, height;
	GtkWidget* win = gtk_widget_get_toplevel(widget);
	gtk_window_get_size(GTK_WINDOW(win), &width, &height);
	cairo_set_line_width(cr, 1);

	// Draw the background
	cairo_set_source_rgb(cr, 0.0f, 0.0f, 0.0f);
	cairo_rectangle(0, 0, width, height);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);

	// Draw player 1 paddle
	int player_1_y;
	player_1 = player.getPlayer1Position();
	cairo_set_source_rgb(cr, 1.0f, 1.0f, 1.0f);
	cairo_rectangle(0, player_1_y - (PADDLE_HEIGHT/2), 0 + PADDLE_WIDTH, player_1_y + (PADDLE_HEIGHT/2));
	cairo_stroke_preserve(cr);
	cairo_fill(cr);

	// Draw player 2 paddle
	int player_2_y;
	player_2 = player.getPlayer2Position();
	cairo_set_source_rgb(cr, 1.0f, 1.0f, 1.0f);
	cairo_rectangle(width - 1, player_2_y - (PADDLE_HEIGHT/2), width - 1 - PADDLE_WIDTH, player_2_y + (PADDLE_HEIGHT/2));
	cairo_stroke_preserve(cr);
	cairo_fill(cr);

	// Draw the ball
	int ball_x, ball_y;
	ball_x = player.getBallXPosition();
	ball_y = player.getBallYPosition();
	cairo_set_source_rgb(cr, 1.0f, 1.0f, 1.0f);
	cairo_arc(cr, ball_x, ball_y, 0, 2*M_PI);
	cairo_stroke_preserve(cr);
	cairo_fill(cr);

	// Queue for redraw
	gtk_widget_queue_draw(widget);
}

void* Player::run(void* arg) {
	// listening thread

	// Wait for user input
	unsigned char input = 0;
	//	followed by sending a packet
}

void* Player::listen(void* arg) {

}

void Player::setPort(int port) {
	listen_port = port;
	pthread_mutex_init(&lock, NULL);
}

int Player::getPlayer1Position() {
	pthread_mutex_lock(&lock);
	int val = player_1_position;
	pthread_mutex_unlock(&lock);
	return val;
}

int Player::getPlayer2Position() {
	pthread_mutex_lock(&lock);
	int val = player_2_position;
	pthread_mutex_unlock(&lock);
	return val;
}

int Player::getBallXPosition() {
	pthread_mutex_lock(&lock);
	int val = ball_x_position;
	pthread_mutex_unlock(&lock);
	return val;
}

int Player::getBallYPosition() {
	pthread_mutex_lock(&lock);
	int val = ball_y_position;
	pthread_mutex_unlock(&lock);
	return val;
}

void Player::receiveDataMessage(unsigned char* buf) {
	pthread_mutex_lock(&lock);
	player_1_score = (int)(buf[0]);
	player_2_score = (int)(buf[1]);
	ball_x_position = (int)(buf[2] | ((int)buf[3] << 8));
	ball_y_position = (int)(buf[4] | ((int)buf[5] << 8));
	player_1_position = (int)(buf[6] | ((int)buf[7] << 8));
	player_2_position = (int)(buf[8] | ((int)buf[9] << 8));
	pthread_mutex_unlock(&lock);
}

int main(int argc, char** argv) {

	// Get port input
	if (argc != 2) {
		cout << "E: Must provide player port" << endl;
		return 1;
	}
	int port = atoi(argv[1]);

	// Initialize the player
	player.setPort(port);
	pthread_t player_thread;
	pthread_create(&player_thread, NULL, &Player::run, NULL);

	// Initialize the GUI
	GtkWidget* window;
	GtkWidget* draw_area;
	gtk_init(&argc &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	draw_area = gtk_drawing_area_new();
	gtk_container_add(GTK_CONTAINER(window), draw_area);
	g_signal_connect(G_OBJECT(draw_area), "draw", G_CALLBACK(on_draw_event), NULL);
	g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
	gtk_window_set_title(GTK_WINDOW(window), "Pong Player");
	gtk_window_show_all(window);
	gtk_main();

	return 0;
}
