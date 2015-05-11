#ifndef NEURON_H
#define NEURON_H

#include "Common.hpp"

#define NEURON_THRESHOLD	0.5f	// Value on [0.0, 1.0] to trigger activation
#define NEURON_ACTIVATION	1.0f	// Value of activation signal once triggered

class Neuron {
	float potential;
	Neuron();
};

class LSTMNeuron {
	float potential;
	float memory;
	LSTMNeuron();
};

#endif
