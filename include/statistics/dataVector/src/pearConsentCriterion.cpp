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
	const double k =  std::abs(rep.domain.first - rep.domain.second) /
		std::abs(min() - max());

	for (int i = 0; i < cs->classCount(); i++) {
		double ni = cs->series()[i].first,
			   nio = rep.cdf(rep.domain.first + (i + 1) * (cs->step()*k));
		nio -= rep.cdf(rep.domain.first + i * (cs->step()*k));
		nio *= size();

		stat.pearConsentCriterion.first += std::pow(ni - nio, 2) / nio;
	}

	stat.pearConsentCriterion.second = true;
}
