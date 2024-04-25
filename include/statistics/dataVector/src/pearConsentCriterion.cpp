#include "../dataVector.hpp"
#include "classSeries.hpp"
#include <cstdlib>

double DataVector::pearConsentCriterion() {
	if (rep.model == DistributionReproducer::Distribution::UnknownD)
		return qQNaN();

	if (stat.pearConsentCriterion.second == false)
		computePearConsentCriterion();

	return stat.pearConsentCriterion.first;
}

void DataVector::computePearConsentCriterion() {
	stat.pearConsentCriterion.first = 0;

	double k, s;
	if (rep.domain.first != rep.domain.second) {
		k =  std::abs(rep.domain.first - rep.domain.second) /
			std::abs(min() - max());
		s = rep.domain.first;
	} else {
		k = 1;
		s = min();
	}

	for (int i = 0; i < cs->classCount(); i++) {
		double ni = cs->series()[i].first,
			   nio = rep.cdf(s + (i + 1) * (cs->step()*k));
		nio -= rep.cdf(s + i * (cs->step()*k));
		nio *= size();

		stat.pearConsentCriterion.first += std::pow(ni - nio, 2) / nio;
	}

	stat.pearConsentCriterion.second = true;
}
