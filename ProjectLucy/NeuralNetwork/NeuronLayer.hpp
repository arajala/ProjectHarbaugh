#ifndef NEURONLAYER_H
#define NEURONLAYER_H

#include "Neuron.hpp"

class NeuronLayer {
	unsigned int n_neurons;
	vector<Neuron> neurons;
	NeuronLayer() {}
	void initialize(unsigned int n);
	void apply(vector<float>* inputs);
};

class LSTMNeuronLayer {
	unsigned int n_neurons;
	vector<LSTMNeuron> neurons;
	LSTMNeuronLayer();
	void initialize(unsigned int n);
	void apply(vector<float>* inputs);
};

#endif
