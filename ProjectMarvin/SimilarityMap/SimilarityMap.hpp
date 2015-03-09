#ifndef SIMILARITYMAP_HPP
#define SIMILARITYMAP_HPP

#include "../Common/Common.hpp"
#include "Cue.hpp"
#include <string>
#include <vector>

template <typename Type>
class SimilarityMap {
private:
	vector<uint64_t> products;
	vector<Cue> cues;
	vector<Type> actions;
public:
};

#endif
