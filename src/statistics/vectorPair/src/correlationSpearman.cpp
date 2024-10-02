#include <vectorPair.hpp>

#include "vector/quantile.hpp"

namespace ss {

void VectorPair::CorrelationSpearman::adapt() {
	double A = 0, B = 0;
	for (auto const& a : s_vector->x.ranks.links())
		A += std::pow(a, 3) - a;
	A /= 12;
	for (auto const& b : s_vector->y.ranks.links())
		B += std::pow(b, 3) - b;
	B /= 12;
	
	double r = 0;
	for (auto rx = s_vector->x.ranks().begin(), ry = s_vector->ranks().begin(); rx != s_vector->x.ranks().end(); rx++, ry++)
		r += std::pow(*rx - *ry, 2);

	double c = (1.0/6.0)*s_vector->size()*(std::pow(s_vector->size(), 2)-1);
	s_value =  (c - r - A - B) /
		std::sqrt((c-2*A)*(c-2*B));

	if (s_value < -1)
		s_value = -1;
	else if (s_value > 1)
		s_value = 1;
}

void VectorPair::CorrelationSpearmanDeviation::adapt() {
	s_value = std::sqrt((1 - std::pow(s_vector->corSpearman(), 2))/(s_vector->size()-2));
}

void VectorPair::CorrelationSpearmanConfidence::adapt(double alpha) {
	s_values[alpha] = thetaDeviation(
		s_vector->corSpearman(), 
		s_vector->corSpearmanDeviation(), 
		alpha, 60
	);
}

}
