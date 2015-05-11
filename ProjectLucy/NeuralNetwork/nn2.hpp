#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "Neuron.hpp"

class NeuralNetwork {
public:
	NeuralNetwork();
	~NeuralNetwork();
	void apply(vector<float>* inputs);
	void simulate();
	void add_layer(unsigned int n_neurons, unsigned int n_lstm_neurons);
	void connect_layers(unsigned int layer_0, unsigned int layer_1);
	void connect_neurons(unsigned int neuron_0, unsigned int neuron_1);
private:
	vector<Neuron*> neurons;
	vector<unsigned int> neurons_per_layer;
};

#endif
