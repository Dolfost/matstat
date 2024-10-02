#include <vectorPair.hpp>

#include "vector/quantile.hpp"

namespace ss {

void VectorPair::Correlation::adapt() {
	double N = s_vector->size();
	s_value = (N/(N-1))*(s_vector->pmean() - s_vector->x.mean()*s_vector->y.mean()) / 
		(s_vector->x.sd()*s_vector->y.sd());
	if (s_value < -1)
		s_value = -1;
	else if (s_value > 1)
		s_value = 1;
}

void VectorPair::CorrelationConfidence::adapt(double alpha) {
	double cor = s_vector->cor(), N = s_vector->size();

	double base = cor + (cor*(1 - std::pow(cor, 2)))/(2*N);
	double q = normQuantile(1-alpha/2)*(1-std::pow(cor, 2))/std::sqrt(N-1);
	//  NOTE: Signs are inverted
	s_values[alpha] = { base + q, base - q};
}

}
