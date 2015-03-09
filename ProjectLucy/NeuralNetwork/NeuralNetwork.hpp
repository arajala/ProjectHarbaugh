#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "../Common/Common.hpp"
#include <string>
#include <vector>

class NeuralNetwork_t {
private:
	uint64_t n_inputs;
	uint64_t n_outputs;
	uint64_t n_hidden_layers;
	uint64_t n_neurons_per_hidden_layer;
	vector<NeuronLayer_t> layers;
public:
	NeuralNetwork_t();
	vector<float> update(vector<float>& inputs);
	inline float sigmoid(float activation, float response);
};

#endif
