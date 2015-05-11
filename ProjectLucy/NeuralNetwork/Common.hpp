#ifndef COMMON_H
#define COMMON_H

using namespace std;

#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <iostream>
#include <random>
#include <vector>
#include <map>

class FloatMatrix {
private:
	vector<vector<float>> data;
public:
	unsigned int nrows;
	unsigned int ncols;
	float at(unsigned int x, unsigned int y);
	void resize(uint32_t)
};

float sigmoid(float x);

#endif
