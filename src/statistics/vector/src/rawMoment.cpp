#include "vector.hpp"
#include "vector/quantile.hpp"

namespace ss {

void Vector::RawMoment::adapt(double degree) {
	double& moment = s_values[degree];
	moment = 0;

	if (s_vector->size() == 0)
		return;

	for (auto const &i : *s_vector) {
		moment += std::pow(i, degree);
	}

	moment /= s_vector->size();
}

void Vector::MeanDeviation::adapt() {
	s_value = this->s_vector->sd() / sqrt(this->s_vector->size());
}

void Vector::MeanConfidence::adapt(double alpha) {
	s_values[alpha] = thetaDeviation(
		s_vector->mean(), 
		s_vector->meanDeviation(), 
		alpha, s_vector->size()
	);
}

}
