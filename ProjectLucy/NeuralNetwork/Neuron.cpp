#include "Neuron.hpp"

Neuron::Neuron() {
	potential = 0.0f;
}

LSTMNeuron::LSTMNeuron() {
	potential = 0.0f;
	memory = 0.0f;
}
