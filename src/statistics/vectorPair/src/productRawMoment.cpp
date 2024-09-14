#include <vectorPair.hpp>

namespace ss {

void VectorPair::ProductRawMoment::adapt(double degree) {
  double *moment = &s_values[degree];
	*moment = 0;

	auto xit = s_vector->x.begin();
	auto yit = s_vector->y.begin();
  while (xit != s_vector->x.end()) {
    *moment += std::pow(*xit**yit, degree);
  }

  *moment /= s_vector->size();
}

}
