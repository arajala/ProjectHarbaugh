#include "Neuron.hpp"

Neuron::Neuron() {
	potential = 0.0f;
}

void Neuron::apply(float input) {
	potential += input;
}

void Neuron::simulate() {
	// Trigger activation
	float activation = get();
	if (activation) {
		unsigned int n_synanpses = synapses.size();
		for (unsigned int is = 0; is < n_synanpses; ++is) {
			Synapse this_synapse = synapses.at(is);
			this_synapse.neuron->apply(this_synapse.weight*sigmoid(activation));
		}
	}

	// Reset potential
	potential = 0.0f;
}

float Neuron::get() {
#if NEURON_MODE == NEURON_MODE_BINARY
	if (potential > NEURON_BINARY_THRESHOLD) {
		return NEURON_BINARY_ACTIVATION;
	} else {
		return 0.0f;
	}
#elif NEURON_MODE == NEURON_MODE_CONTINUOUS
	return potential;
#endif
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
	// Trigger activation if output gate allows
	float activation = get();
	if (activation) {
		unsigned int n_synanpses = synapses.size();
		for (unsigned int is = 0; is < n_synanpses; ++is) {
			Synapse this_synapse = synapses.at(is);
			this_synapse.neuron->apply(this_synapse.weight*sigmoid(activation));
		}
	}

	// Calculate the new memory state
	float input_gate_activation = input_gate->get();
	float forget_gate_activation = forget_gate->get();
	memory = memory*forget_gate_activation + activation*input_gate_activation;

	// Reset potential
	potential = 0.0f;
}

float LSTMNeuron::get() {
	float output_gate_activation = output_gate->get();
#if NEURON_MODE == NEURON_MODE_BINARY
	if ((output_gate_activation) && (memory > NEURON_BINARY_THRESHOLD)) {
		return NEURON_BINARY_ACTIVATION;
	} else {
		return 0.0f;
	}
#elif NEURON_MODE == NEURON_MODE_CONTINUOUS
	return output_gate_activation*memory;
#endif
}
