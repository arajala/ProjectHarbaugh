#include "NeuralWeightMap.hpp"

void NeuralWeightMap::initialize(unsigned int n_rows, unsigned int n_cols) {
	default_random_engine generator;
	uniform_real_distribution<float> distribution(0.0f, 1.0f);
	weights.resize(n_rows, n_cols);
	for (unsigned int ir = 0; ir < n_rows; ++ir) {
		for (unsigned int ic = 0; ic < n_cols; ++ic) {
			weights.at(ir, ic) = distribution(generator);
		}
	}
}

void NeuralWeightMap::assign(FloatMatrix* new_weights) {
	assert((new_weights->n_rows == weights.n_rows) && (new_weights->n_cols == weights.n_cols));
	weights = *new_weights;
}
