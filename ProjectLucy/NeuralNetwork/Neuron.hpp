#ifndef NEURON_H
#define NEURON_H

#include "../Common/Common.hpp"
#include <string>
#include <vector>

class Neuron_t {
public:
	uint64_t n_inputs;
	vector<float> weights;
	Neuron_t(uint64_t n) : n_inputs(n) {}
};

#endif
