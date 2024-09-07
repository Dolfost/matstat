#include "vector.hpp"

#include <cstdlib>

namespace ss {

void PearConsentCriterion::adapt() {
	s_value = 0;

	double k, s;
	if (s_vector.rep.domain.first != s_vector.rep.domain.second) {
		k =  std::abs(s_vector.rep.domain.first - s_vector.rep.domain.second) /
			std::abs(s_vector.min() - s_vector.max());
		s = s_vector.rep.domain.first;
	} else {
		k = 1;
		s = s_vector.min();
	}

	for (int i = 0; i < s_vector.classSeries.count(); i++) {
		double ni = s_vector.classSeries.series()[i].first,
			   nio = s_vector.rep.cdf(s + (i + 1) * (s_vector.classSeries.step()*k));
		nio -= s_vector.rep.cdf(s + i * (s_vector.classSeries.step()*k));
		nio *= s_vector.size();

		s_value += std::pow(ni - nio, 2) / nio;
	}
}

}
