#include "vector.hpp"

namespace ss {

void RawMoment::adapt(double degree) {
  double *moment = &s_values[degree];
	*moment = 0;

  for (auto const &i : s_vector) {
    *moment += std::pow(i, degree);
  }

  *moment /= s_vector.size();
}

void MeanDeviation::adapt() {
  s_value = this->s_vector.sd() / sqrt(this->s_vector.size());
}

void MeanConfidence::adapt(double alpha) {
	s_values[alpha] = thetaDeviation(
		s_vector.mean(), 
		s_vector.meanDeviation(), 
		alpha, s_vector.size()
	);
}

}
