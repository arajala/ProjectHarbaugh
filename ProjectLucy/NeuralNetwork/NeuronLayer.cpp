#include "NeuronLayer.hpp"

void NeuronLayer::initialize(unsigned int n) {
	n_neurons = n;
	neurons.resize(n);
}

void NeuronLayer::apply(vector<float>* inputs) {
	assert(inputs->size() == n_neurons);
	for (unsigned int i = 0; i < neurons.size(); ++i) {
		neurons.at(i).potential = sigmoid(inputs->at(i));
	}
}
