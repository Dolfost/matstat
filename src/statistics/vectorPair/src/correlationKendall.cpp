#include <vectorPair.hpp>

#include "vector/quantile.hpp"

namespace ss {

void VectorPair::CorrelationKendall::adapt() {
	double sum = 0;
	for (auto y = s_vector->ranks().begin(); y != --s_vector->ranks().end(); y++) {
		for (auto y1 = y; y1 != s_vector->ranks().end(); y1++) {
			if (*y < *y1)
				sum++;
			if (*y > *y1)
				sum--;
		}
	}

	s_value = 2*sum/(s_vector->size()*(s_vector->size()-1));
}

void VectorPair::CorrelationKendallDeviation::adapt() {
	s_value = std::sqrt(
		(4*s_vector->size()+10) / 
		(9*(std::pow(s_vector->size(), 2) - s_vector->size()))
	);
}

void VectorPair::CorrelationKendallConfidence::adapt(double alpha) {
	s_values[alpha] = thetaDeviation(
		s_vector->corKendall(), 
		s_vector->corKendallDeviation(), 
		alpha, 61
	);
}

}
