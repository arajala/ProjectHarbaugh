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
	if (potential > NEURON_BINARY_THRESHOLD) {
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
#if NEURON_MODE == NEURON_MODE_BINARY
	if ((output_gate->potential > NEURON_BINARY_THRESHOLD) && (memory > NEURON_BINARY_THRESHOLD)) {
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
		this_synapse.neuron->potential += output_gate->potential*this_synapse.weight*memory;
	}
#endif

	// Calculate the new memory state
#if NEURON_MODE == NEURON_MODE_BINARY
	if (memory_gate->potential > NEURON_BINARY_THRESHOLD) {
		float input_component;
		if (input_gate->potential > NEURON_BINARY_THRESHOLD) {
			input_component = NEURON_BINARY_ACTIVATION;
		} else {
			input_component = 0.0f;
		}
		memory = memory + input_component;
	}
#elif NEURON_MODE == NEURON_MODE_CONTINUOUS
	memory = memory_gate->potential*memory + input_gate->potential*potential;
#endif
}

float LSTMNeuron::get() {
#if NEURON_MODE == NEURON_MODE_BINARY
	if ((output_gate->potential > NEURON_BINARY_THRESHOLD) && (memory > NEURON_BINARY_THRESHOLD)) {
		return NEURON_BINARY_ACTIVATION;
	} else {
		return 0.0f;
	}
#elif NEURON_MODE == NEURON_MODE_CONTINUOUS
	return output_gate->potential*memory;
#endif
}
