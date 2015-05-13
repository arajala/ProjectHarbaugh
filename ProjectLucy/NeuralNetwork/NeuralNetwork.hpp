#ifndef NEURALNETWORK_HPP
#define NEURALNETWORK_HPP

#include "Neuron.hpp"

#define NN_WEIGHT_MIN	0.0f
#define NN_WEIGHT_MAX	1.0f

class NeuralNetwork {
public:
	// Network creation methods
	NeuralNetwork();
	~NeuralNetwork();
	void init();

	// Network usage methods
	void apply(vector<float>* inputs);
	void simulate();
	vector<float>* get();

	// Network construction methods
	void add_layer(unsigned int n_neurons, unsigned int n_lstm_neurons);
	void connect_layers(unsigned int layer_0, unsigned int layer_1);
	void connect_neurons(unsigned int neuron_0, unsigned int neuron_1);

	// Network tuning methods
	void randomize_weights();
	void set_weights(vector<float>* weights);
	vector<float>* get_weights();	// return value must be deleted

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
