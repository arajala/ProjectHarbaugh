#include "../NeuralNetwork/NeuralNetwork.hpp"

int main() {
	NeuralNetwork skynet;

	skynet.add_layer(1, 0); // 0
	skynet.add_layer(1, 0); // 1
	skynet.connect_neurons(0, 1);
	skynet.connect_neurons(1, 0);
	skynet.randomize_weights();

	vector<float>* w = skynet.get_weights();

	for (unsigned int i = 0; i < w->size(); ++i) {
		cout << w->at(i) << " ";
	}
	cout << endl;

	return 0;
}
