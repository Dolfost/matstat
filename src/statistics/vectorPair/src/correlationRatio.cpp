#include<vectorPair.hpp>

#include "vector/quantile.hpp"

namespace ss {

void VectorPair::CorrelationRatio::adapt() {
	if (c_count == 0)
		c_count = sqrt(s_vector->size());

	double step = s_vector->x.len()/c_count;

	std::vector<std::list<double>> groups;
	groups.resize(c_count);

	auto xit = s_vector->x.begin();
	auto yit = s_vector->y.begin();

	while (xit != s_vector->x.end()) {
		std::size_t idx = (*xit - s_vector->x.min())/step;
		if (idx >= c_count)
			idx--;
		groups[idx].push_back(*yit);
		xit++, yit++;
	}

	double sum1 = 0;
	for (int i = 0; i < c_count; i++) {
		Vector m(groups[i]);
		sum1 += m.size()*std::pow(m.mean() - s_vector->y.mean(), 2);
	}

	double sum2 = 0;
	for (int i = 0; i < c_count; i++) {
		for (auto const& yij: groups[i]) {
			sum2 += std::pow(yij - s_vector->y.mean(), 2);
		}
	}
	
	s_value = sum1/sum2;
}

void VectorPair::CorrelationRatioDeviation::adapt() {
	s_value = std::sqrt((1 - std::pow(s_vector->corRatio(), 2))/(s_vector->size() - 2));
}

void VectorPair::CorrelationRatioConfidence::adapt(double alpha) {
	s_values[alpha] = thetaDeviation(
		s_vector->corRatio(), 
		s_vector->corRatioDeviation(), 
		alpha, s_vector->size()
	);
}

}
