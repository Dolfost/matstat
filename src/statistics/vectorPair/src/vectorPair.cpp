#include <vectorPair.hpp>

#include <stdexcept>

namespace ss {

VectorPair::VectorPair(const std::vector<double> xx, 
											 const std::vector<double> yy) {
	v_x.setVector(xx);
	v_y.setVector(yy);

	checkSize();

	auto iLambda = [this]() {
		this->invalidate();
	};

	v_x.setInvalidateCallback(iLambda);
	v_y.setInvalidateCallback(iLambda);

	setExprtkSymbolTable(v_exprtkSymbolTable, this);
}

void VectorPair::setX(const std::vector<double>& x) {
	v_x = x;
	invalidate();
}

void VectorPair::setY(const std::vector<double>& y) {
	v_y = y;
	invalidate();
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

	setExprtkSymbolTable(v_exprtkSymbolTable, this);
}

void VectorPair::invalidate() {
	checkSize();

	cor.invalidate();
	nangle.invalidate();
	vs.invalidate();
	cs.invalidate();
}

VectorPair::VectorPair(const VectorPair& other): VectorPair(other.x.list(), other.y.list()) {
}

VectorPair& VectorPair::operator=(const VectorPair& other) {
	auto c = v_x.invalidateCallback();
	v_x.setInvalidateCallback([](){});
	v_y.setInvalidateCallback([](){});

	v_x = other.x;
	v_y = other.y;

	v_x.setInvalidateCallback(c);
	v_y.setInvalidateCallback(c);
	//
	// min = other.min;
	// max = other.max;
	// cs = other.cs;

	return *this;
}

void VectorPair::checkSize() {
	if (v_x.size() != v_y.size()) {
		v_x = {}, v_y = {};
		throw std::logic_error("Вектори різного розміру!");
	}
}

}
