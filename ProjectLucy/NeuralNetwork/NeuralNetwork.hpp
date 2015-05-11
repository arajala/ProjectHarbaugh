#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "NeuronLayer.hpp"

struct LayerSetup {
	unsigned int n_in_neurons;
	unsigned int n_out_neurons;
	unsigned int n_hid_layers;
	unsigned int* n_hid_neurons;
};

struct BackConnections {
	vector<pair<unsigned int, unsigned int>> connections;
};

class NeuralNetwork {
private:
	unsigned int n_hidden_layers;
	vector<NeuronLayer> layers;
	map<pair<NeuronLayer*, NeuronLayer*>, NeuralWeightMap*> weight_map;
	vector<pair<unsigned int, unsigned int>> back_connections;
public:
	NeuralNetwork(LayerSetup layer_setup, BackConnections back_conns);
	void update(vector<float>* inputs);
	void propogate(NeuronLayer* next, NeuronLayer* prev);
};

#endif
