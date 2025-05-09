#include <vectorPair.hpp>

namespace ss {

void VectorPair::rotate(double phi) {
	double x_1;
	auto n = size();
	for (std::size_t i = 0; i < n; i++) {
		x_1 = x[i];
		x[i] = x_1*std::cos(phi) + y[i]*std::sin(phi);
		y[i] = -x_1*std::sin(phi) + y[i]*std::cos(phi);
	}
	invalidate();
}

}
