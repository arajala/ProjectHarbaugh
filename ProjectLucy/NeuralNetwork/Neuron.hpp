#ifndef NEURON_HPP
#define NEURON_HPP

#include "Common.hpp"

#define NEURON_MODE_BINARY		0
#define NEURON_MODE_CONTINUOUS	1

#define NEURON_MODE	NEURON_MODE_BINARY

#define NEURON_BINARY_THRESHOLD		0.5f	// Value on [0.0, 1.0] to trigger activation
#define NEURON_BINARY_ACTIVATION	1.0f	// Value of activation signal once triggered

class Synapse {
public:
	Synapse();
	float weight;
	Neuron* neuron;
private:
};

class Neuron {
public:
	Neuron();
	void apply(float input);
	virtual void simulate();
	virtual float get();
protected:
	float potential;
	vector<Synapse> synapses;
};

class LSTMNeuron : public Neuron {
public:
	LSTMNeuron();
	void initialize(Neuron* input, Neuron* forget, Neuron* output);
	void simulate();
	float get();
private:
	float memory;
	Neuron* input_gate;
	Neuron* forget_gate;
	Neuron* output_gate;
};

#endif
