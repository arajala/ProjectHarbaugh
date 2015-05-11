#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork() {

}

NeuralNetwork::~NeuralNetwork() {
	while (!neurons.empty()) {
		Neuron* n = neurons.back();
		neurons.pop_back();
		delete n;
	}
}

void NeuralNetwork::apply(vector<float>* inputs) {
	unsigned int n_input_neurons = neurons_per_layer.at(0);
	assert(inputs->size() == n_input_neurons);
	for (unsigned int in = 0; in < n_input_neurons; ++in) {
		neurons.at(in)->apply(inputs->at(in));
	}
}

void NeuralNetwork::simulate() {
	unsigned int n_neurons = neurons.size();
	for (unsigned int in = 0; in < n_neurons; ++in) {
		neurons.at(in)->simulate();
	}
}

void NeuralNetwork::add_layer(unsigned int n_neurons, unsigned int n_lstm_neurons) {
	// Register the layer by number of neurons in it
	neurons_per_layer.push_back(n_neurons + 4*n_lstm_neurons);

	// Add the regular neurons first
	for (unsigned int in = 0; in < n_neurons; ++in) {
		Neuron* next_neuron = new Neuron();
		neurons.push_back(next_neuron);
	}

	// Add the LSTM neurons
	for (unsigned int in = 0; in < n_lstm_neurons; ++in) {
		// Create the regular neurons to serve as gate inputs
		Neuron* next_output_neuron = new Neuron();
		Neuron* next_forget_neuron = new Neuron();
		Neuron* next_input_neuron = new Neuron();
		neurons.push_back(next_output_neuron);
		neurons.push_back(next_forget_neuron);
		neurons.push_back(next_input_neuron);

		// Create the LSTM neuron and register the gate neurons
		LSTMNeuron* next_lstm_neuron = new LSTMNeuron();
		next_lstm_neuron->initialize(next_input_neuron, next_forget_neuron, next_output_neuron);
		neurons.push_back(next_lstm_neuron);
	}
}

void NeuralNetwork::connect_layers(unsigned int layer_0, unsigned int layer_1) {

}

void NeuralNetwork::connect_neurons(unsigned int neuron_0, unsigned int neuron_1) {

}
