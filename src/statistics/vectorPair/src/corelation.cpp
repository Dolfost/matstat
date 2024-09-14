#include <vectorPair.hpp>

namespace ss {

void VectorPair::Corelation::adapt() {
	double N = s_vector->size();
	s_value = (N/(N-1))*(s_vector->pmean() - s_vector->x.mean()*s_vector->y.mean()) / 
		(s_vector->x.sd()*s_vector->y.sd());
}

}
