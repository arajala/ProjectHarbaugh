#include "NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(LayerSetup layer_setup, BackConnections back_conns) {
	n_hidden_layers = layer_setup.n_hid_layers;
	layers.resize(n_hidden_layers + 2); // hidden + input + output

	// Initialize input layer
	layers.at(0).initialize(layer_setup.n_in_neurons);

	// Initialize hidden layers
	for (unsigned int ih = 0; ih < n_hidden_layers; ++ih) {
		layers.at(ih+1).initialize(layer_setup.n_hid_neurons[ih]);
	}

	// Initialize output layer
	layers.at(n_hidden_layers+1).initialize(layer_setup.n_out_neurons);

	// Set backwards connections
	back_connections = back_conns;

	// Initialize forward weights
	for (unsigned int il = 0; il < n_hidden_layers+1; ++il) {
		pair<NeuronLayer*, NeuronLayer*> new_layer_pair;
		new_layer_pair.first = &(layers.at(il));
		new_layer_pair.second = &(layers.at(il+1));
		NeuralWeightMap* new_map = new NeuralWeightMap(); // need to free these
		new_map->initialize(layers.at(il).n_neurons, layers.at(il+1).n_neurons);
		weight_map[new_layer_pair] = new_map;
	}

	// Initialize backward weights
	for (unsigned int ic = 0; ic < back_connections.size(); ++ic) {
		unsigned int layer_start = back_connections.at(ic).first;
		unsigned int layer_end = back_connections.at(ic).second;
		assert(layer_start > 0);
		assert(layer_start < n_hidden_layers + 2);
		assert(layer_start > layer_end);
		assert(layer_end >= 0);
		assert(layer_end < n_hidden_layers + 1);
		pair<NeuronLayer*, NeuronLayer*> new_layer_pair;
		new_layer_pair.first = &(layers.at(layer_start));
		new_layer_pair.second = &(layers.at(layer_end));
		NeuralWeightMap* new_map = new NeuralWeightMap(); // need to free these
		new_map->initialize(layers.at(layer_start).n_neurons, layers.at(layer_end).n_neurons);
		weight_map[new_layer_pair] = new_map;
	}
}

void NeuralNetwork::update(vector<float>* inputs) {

}

void NeuralNetwork::propogate(NeuronLayer* next, NeuronLayer* prev) {

}
