#ifndef NEURALWEIGHTMAP_H
#define NEURALWEIGHTMAP_H

#include "Common.hpp"

class NeuralWeightMap {
private:
public:
	FloatMatrix weights;
	NeuralWeightMap() {}
	void initialize(unsigned int n_rows, unsigned int n_cols);
	void assign(FloatMatrix* new_weights);
};

#endif
