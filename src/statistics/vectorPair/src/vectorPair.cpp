#include <vectorPair.hpp>

#include <stdexcept>

namespace ss {

VectorPair::VectorPair(const std::list<double> xx, 
											 const std::list<double> yy) {
	v_x.setVector(xx);
	v_y.setVector(yy);

	checkSize();

	auto iLambda = [this]() {
		this->invalidate();
	};

	v_x.setInvalidateCallback(iLambda);
	v_y.setInvalidateCallback(iLambda);
}

VectorPair::VectorPair(const Vector& xx, 
											 const Vector& yy) {
	v_x = xx;
	v_y = yy;

	checkSize();

	auto iLambda = [this]() {
		this->invalidate();
	};

	v_x.setInvalidateCallback(iLambda);
	v_y.setInvalidateCallback(iLambda);
}

void VectorPair::invalidate() {
	checkSize();
}

VectorPair::VectorPair(const VectorPair& other) {
	operator=(other);
}
VectorPair& VectorPair::operator=(const VectorPair& other) {
	v_x = other.v_x;
	v_y = other.v_y;

	min = other.min;
	max = other.max;
	cs = other.cs;

	return *this;
}

void VectorPair::checkSize() {
	if (v_x.size() != v_y.size()) {
		v_x = {}, v_y = {};
		throw std::logic_error("Вектори різного розміру!");
	}
}

}
