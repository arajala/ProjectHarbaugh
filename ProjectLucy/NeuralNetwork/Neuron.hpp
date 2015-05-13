#ifndef NEURON_HPP
#define NEURON_HPP

#include "Common.hpp"

// Which method of output the neurons in this network use
// Will probably be changed to an initialization input so that both
// can be used
#define NEURON_MODE_BINARY		0
#define NEURON_MODE_CONTINUOUS	1
#define NEURON_MODE				NEURON_MODE_BINARY

// Value on [0.0, 1.0] to trigger activation
#define NEURON_BINARY_THRESHOLD		0.5f
// Value of activation signal once triggered
#define NEURON_BINARY_ACTIVATION	1.0f

// Forward declaration needed by Synapse
class Neuron;

// A class describing a connection between neurons
class Synapse {
public:
	// The tunable weight of the connection
	float weight;

	// The neuron on the receiving end of the connection
	Neuron* neuron;
};

// Virtual abstraction of the neuron, so that other types
// of neurons can be derived from and used in place of it
class Neuron {
public:
	// Initializes the potential
	Neuron();

	// Accumulates into the neuron's potential
	void apply(float input);

	// Triggers activation of the neuron and clears the potential
	virtual void simulate();

	// Gets the current activation potential
	virtual float get();

	// A list of all the connections to other neurons
	vector<Synapse> synapses;
protected:
	// The internal activation value of the neuron
	float potential;
};

// A derived type of neuron that holds memory and uses other neurons as gates
// to control when the memory is stored, forgotten, and sent as output
class LSTMNeuron : public Neuron {
public:
	// Initializes the memory
	LSTMNeuron();

	// Registers 3 base class neurons as gate inputs
	void initialize(Neuron* input, Neuron* forget, Neuron* output);

	// Triggers activation of the neuron based on gets,
	// sets the next memory value, and clears the potential
	void simulate();

	// Get the current activation potential
	float get();
private:
	// The internal memory value of the neuron
	float memory;

	// Links to the gate neurons elsewhere in the network
	Neuron* input_gate;
	Neuron* forget_gate;
	Neuron* output_gate;
};

#endif
