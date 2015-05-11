#include <iostream>
#include <cmath>
#include <random>
#include <windows.h>
#include <pthread.h>
#include <cairo.h>
#include <gtk/gtk.h>

#define M_PI 3.14159f

#define CENTER_X 300.0f
#define CENTER_Y 200.0f

#define NLS 0
#define NRS 1
#define NRE 2
#define NEX 3
#define NLM 4
#define NRM 5

class agent_t {
private:
	float neuron_l_sense;
	float nls_wgts[6];

	float neuron_r_sense;
	float nrs_wgts[6];

	float neuron_reinforce;
	float nre_wgts[6];

	float neuron_extra;
	float nex_wgts[6];

	float neuron_l_motor;
	float nlm_wgts[6];

	float neuron_r_motor;
	float nrm_wgts[6];
public:
	pthread_mutex_t lock;
	float x, y, ang;
	void update();
	agent_t();
};

agent_t agent;