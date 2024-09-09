#ifndef _VECTOR_PAIR_HPP_
#define _VECTOR_PAIR_HPP_	

#include <vector.hpp>

#include <vector/utils.hpp>

#include <utility>

namespace ss {

class VectorPair: public std::pair<Vector, Vector> {
public:
	VectorPair(const std::list<double> ft = {}, const std::list<double> sd = {}) {
		first.setVector(ft);
		second.setVector(sd);

		auto lambda = [this]() {
			this->invalidate();
		};

		first.setInvalidateCallback(lambda);
		second.setInvalidateCallback(lambda);
	}

public:
	void invalidate() {
	};
};

}

#endif // !_VECTOR_PAIR_HPP_
