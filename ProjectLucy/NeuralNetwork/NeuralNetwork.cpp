#include "NeuralNetwork.hpp"

NeuralNetwork::~NeuralNetwork() {
	while (!neurons.empty()) {
		Neuron* n = neurons.back();
		neurons.pop_back();
		delete n;
	}
}

void NeuralNetwork::init() {
	outputs.resize(neurons_per_layer.back());
}

void NeuralNetwork::apply(vector<float>* inputs) {
	unsigned int n_input_neurons = neurons_per_layer.at(0);
	assert(inputs->size() == n_input_neurons);
	for (unsigned int in = 0; in < n_input_neurons; ++in) {
		neurons.at(in)->apply(inputs->at(in));
	}
}

void NeuralNetwork::simulate() {
	// Iterate through all input and hidden neurons
	unsigned int n_neurons = neurons.size();
	unsigned int i_output_neuron = n_neurons - neurons_per_layer.back();
	for (unsigned int in = 0; in < i_output_neuron; ++in) {
		neurons.at(in)->simulate(); // THIS CLEARS OUTPUT NEURONS!!! bad!
	}

	// Iterate through output neurons and update output state
	for (unsigned int in = i_output_neuron, io = 0; in < n_neurons; ++in, ++io) {
		outputs.at(io) = neurons.at(in)->get();
		neurons.at(in)->simulate();
	}

	// Output the data over a socket?
}

vector<float>* NeuralNetwork::get() {
	return &outputs;
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
		Neuron* next_input_neuron = new Neuron();
		Neuron* next_forget_neuron = new Neuron();
		Neuron* next_output_neuron = new Neuron();

		// Create the LSTM neuron and connect the gate neurons
		LSTMNeuron* next_lstm_neuron = new LSTMNeuron();
		next_lstm_neuron->initialize(next_input_neuron, next_forget_neuron, next_output_neuron);
		neurons.push_back(next_lstm_neuron);

		// Register the regular neurons after the LSTM
		// - avoids clearing the potential too early
		neurons.push_back(next_input_neuron);
		neurons.push_back(next_forget_neuron);
		neurons.push_back(next_output_neuron);
	}
}

void NeuralNetwork::connect_layers(unsigned int layer_0, unsigned int layer_1) {
	// Get the index of the neuron at the start of layer 0
	unsigned int i_layer_0_neuron;
	for (unsigned int il = 0; il < layer_0; ++il) {
		i_layer_0_neuron += neurons_per_layer.at(il);
	}

	// Get the index of the neuron at the start of layer 1
	unsigned int i_layer_1_neuron;
	for (unsigned int il = 0; il < layer_1; ++il) {
		i_layer_1_neuron += neurons_per_layer.at(il);
	}

	// Iterate through layer 0 neurons and add synapses to layer 1 neurons
	unsigned int i_layer_0_end = i_layer_0_neuron + neurons_per_layer.at(layer_0);
	unsigned int i_layer_1_end = i_layer_1_neuron + neurons_per_layer.at(layer_1);
	for (unsigned int il0 = i_layer_0_neuron; il0 < i_layer_0_end; ++il0) {
		for (unsigned int il1 = i_layer_1_neuron; il1 < i_layer_1_end; ++il1) {
			connect_neurons(il0, il1);
		}
	}
}

void NeuralNetwork::connect_neurons(unsigned int neuron_0, unsigned int neuron_1) {
	Neuron* n0 = neurons.at(neuron_0);
	Neuron* n1 = neurons.at(neuron_1);

	// Make the new synapse
	Synapse s;
	s.weight = 0.5; // default weight?
	s.neuron = n1;
	n0->synapses.push_back(s);
	++n_total_synapses;
}

void NeuralNetwork::randomize_weights() {
	// Create the seeded RNG
	typedef chrono::system_clock clk;
	clk::time_point tp = clk::now();
	clk::duration dur = tp.time_since_epoch();
	unsigned int time_seed = dur.count();
	default_random_engine generator(time_seed);
	uniform_real_distribution<float> distribution(NN_WEIGHT_MIN, NN_WEIGHT_MAX);

	// Iterate through all neurons and their synapses
	unsigned int n_neurons = neurons.size();
	for (unsigned int in = 0; in < n_neurons; ++in) {
		unsigned int n_synapses = neurons.at(in)->synapses.size();
		for (unsigned int is = 0; is < n_synapses; ++is) {
			neurons.at(in)->synapses.at(is).weight = distribution(generator);
		}
	}
}

void NeuralNetwork::set_weights(vector<float>* weights) {
	assert(weights->size() == n_total_synapses);

	// Iterate through all neurons and their synapses
	unsigned int n_neurons = neurons.size();
	for (unsigned int in = 0; in < n_neurons; ++in) {
		unsigned int n_synapses = neurons.at(in)->synapses.size();
		for (unsigned int is = 0; is < n_synapses; ++is) {
			neurons.at(in)->synapses.at(is).weight = weights->at(is);
		}
	}
}

vector<float>* NeuralNetwork::get_weights() {
	vector<float>* weights = new vector<float>;

	// Iterate through all neurons and their synapses
	unsigned int n_neurons = neurons.size();
	for (unsigned int in = 0; in < n_neurons; ++in) {
		unsigned int n_synapses = neurons.at(in)->synapses.size();
		for (unsigned int is = 0; is < n_synapses; ++is) {
			float this_weight = neurons.at(in)->synapses.at(is).weight;
			weights->push_back(this_weight);
		}
	}

	return weights;
}
