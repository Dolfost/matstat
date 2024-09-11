#include <vectorPair.hpp>

#include <stdexcept>

namespace ss {

VectorPair::VectorPair(const std::list<double> ft, 
											 const std::list<double> sd) {
	v_x.setVector(ft);
	v_y.setVector(sd);

	auto lambda = [this]() {
		this->invalidate();
	};

	v_x.setInvalidateCallback(lambda);
	v_y.setInvalidateCallback(lambda);
}

void VectorPair::invalidate() {
	checkSize();
}

void VectorPair::checkSize() const {
	if (v_x.size() != v_y.size())
		throw std::logic_error("Вектори різного розміру!");
}

}
