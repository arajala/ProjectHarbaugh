#include "../NeuralNetwork/NeuralNetwork.hpp"

int main() {
	cout << "Constructing the network..." << endl;
	NeuralNetwork skynet;
	skynet.add_layer(1, 0);
	cout << "added layer 0" << endl;
	skynet.add_layer(20, 0);
	cout << "added layer 1" << endl;
	skynet.add_layer(20, 0);
	cout << "added layer 2" << endl;
	skynet.add_layer(10, 0);
	cout << "added layer 3" << endl;

	skynet.connect_layers(0, 1);
	cout << "connected layers 0-1" << endl;
	skynet.connect_layers(1, 2);
	cout << "connected layers 1-2" << endl;
	skynet.connect_layers(2, 3);
	cout << "connected layers 2-3" << endl;
	skynet.connect_layers(2, 1);
	cout << "connected layers 2-1" << endl;
	skynet.connect_layers(3, 2);
	cout << "connected layers 3-2" << endl;

	skynet.randomize_weights();
	cout << "randomized weights" << endl;

	skynet.initialize();
	cout << "initialized" << endl;
	cout << endl;

	// cout << "Printing network weights ..." << endl;
	// vector<float>* w = skynet.get_weights();
	// for (unsigned int i = 0; i < w->size(); ++i) {
	// 	cout << w->at(i) << " ";
	// }
	// cout << endl << endl;

	cout << "Applying an input..." << endl;
	vector<float> inputs;
	inputs.resize(1);
	skynet.apply(&inputs);
	cout << endl;

	for (unsigned int j = 0; j < 1; ++j) {
		cout << "Simulating one pass..." << endl;
		skynet.simulate();
		cout << endl;

		cout << "Printing output..." << endl;
		vector<float>* outputs = skynet.get();
		for (unsigned int i = 0; i < outputs->size(); ++i) {
			cout << outputs->at(i) << " ";
		}
		cout << endl << endl;
	}

	return 0;
}
