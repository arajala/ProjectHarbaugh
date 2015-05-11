#include "Neuron.hpp"

Neuron::Neuron() {
	potential = 0.0f;
}

void Neuron::apply(float input) {
	potential = input;
}

void Neuron::simulate() {
	// Trigger activation
#if NEURON_MODE == NEURON_MODE_BINARY
	if (potential > NEURON_THRESHOLD) {
		unsigned int n_synanpses = synapses.size();
		for (unsigned int is = 0; is < n_synanpses; ++is) {
			Synapse this_synapse = synapses.at(is);
			this_synapse.neuron->potential += this_synapse.weight*NEURON_BINARY_ACTIVATION;
		}
	}
#elif NEURON_MODE == NEURON_MODE_CONTINUOUS
	unsigned int n_synanpses = synapses.size();
	for (unsigned int is = 0; is < n_synanpses; ++is) {
		Synapse this_synapse = synapses.at(is);
		this_synapse.neuron->potential += this_synapse.weight*sigmoid(potential);
	}
#endif

	// Reset potential
	potential = 0.0f;
}

LSTMNeuron::LSTMNeuron() {
	memory = 0.0f;
}

void LSTMNeuron::initialize(Neuron* input, Neuron* forget, Neuron* output) {
	input_gate = input;
	forget_gate = forget;
	output_gate = output;
}

void LSTMNeuron::simulate() {

}
