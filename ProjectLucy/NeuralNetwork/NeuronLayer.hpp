#ifndef NEURONLAYER_H
#define NEURONLAYER_H

#include "../Common/Common.hpp"
#include <string>
#include <vector>

class NeuronLayer_t {
public:
	uint64_t n_neurons;
	vector<Neuron> neurons;
	NeuronLayer_t(uint64_t n, uint64_t inputs_per_neuron);
};

#endif
