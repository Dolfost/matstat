#include <vectorPair.hpp>

#include <cmath>

void ss::VectorPair::NormalizationAngle::adapt() {
	ss::VectorPair& v = *s_vector;
	s_value = std::atan(
		(2*v.cor() * v.x.sd() * v.y.sd()) / 
		(std::pow(v.x.sd(), 2) - std::pow(v.y.sd(), 2))
	) / 2;
};
