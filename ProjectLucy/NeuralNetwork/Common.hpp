#ifndef COMMON_HPP
#define COMMON_HPP

using namespace std;

#include <cstdlib>
#include <cmath>
#include <cassert>
#include <chrono>
#include <random>
#include <iostream>
#include <vector>

inline float sigmoid(float x) {
	return 1.0f / (1.0f + (float)exp(-(double)x));
}

#endif
