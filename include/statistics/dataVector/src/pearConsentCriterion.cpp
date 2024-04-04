#include "../dataVector.hpp"
#include "classSeries.hpp"

double DataVector::pearConsentCriterion() {
  if (rep.model == DistributionReproducer::Distribution::UnknownD)
    return qQNaN();

  if (stat.pearConsentCriterion.second == false)
    computePearConsentCriterion();

  return stat.pearConsentCriterion.first;
}

void DataVector::computePearConsentCriterion() {
  stat.pearConsentCriterion.first = 0;
  for (int i = 0; i < cs->classCount(); i++) {
    double ni = cs->series()[i].second,
           nio = rep.cdf(min() + (i + 1) * (cs->step()));
    nio -= rep.cdf(min() + i * (cs->step()));
    nio *= size();

    stat.pearConsentCriterion.first += std::pow(ni - nio, 2) / nio;
  }

  stat.pearConsentCriterion.second = true;
}
