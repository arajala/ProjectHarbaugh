#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include "Neuron.hpp"

#define NN_WEIGHT_MIN	0.0f
#define NN_WEIGHT_MAX	1.0f

class NeuralNetwork {
public:
	// === Network creation methods ===

	// Cleans up the neurons vector
	~NeuralNetwork();
	// Init must be called after construction, before calling simulate()
	void initialize();

	// === Network usage methods ===

	// Accumulates values into the input layer neurons
	void apply(vector<float>* inputs);
	// Does one calculation pass through the entire network, updating outputs
	void simulate();
	// Returns a pointer to the vector of output values
	vector<float>* get();

	// === Network construction methods ===

	// Adds a new layer with a specified number of neurons
	// Note that n_lstm_neurons adds 4*n_lstm_neurons to the network
	void add_layer(unsigned int n_neurons, unsigned int n_lstm_neurons);
	// Fully forward-connects any two layers of the network
	// (Connects layer_0 to layer_1)
	void connect_layers(unsigned int layer_0, unsigned int layer_1);
	// Forward connects any two neurons in the network, specified by their ID
	// ID numbers start at 0 and increment for every neuron added to the network
	// User should maintain external drawing of network to know ID numbers
	void connect_neurons(unsigned int neuron_0, unsigned int neuron_1);

	// === Network tuning methods ===
	
	// Uses a time-seeded RNG to randomize all network weights
	void randomize_weights();
	// Sets all network weights
	void set_weights(vector<float>* weights);
	// Gets all network weights - return value must be deleted by user
	vector<float>* get_weights();

private:
	// All neurons, packed into a flat structure
	vector<Neuron*> neurons;

	// Number of neurons in each layer
	vector<unsigned int> neurons_per_layer;

	// Number of synapse connections in the network
	unsigned long int n_total_synapses;

	// The current output state
	vector<float> outputs;
};

#endif
