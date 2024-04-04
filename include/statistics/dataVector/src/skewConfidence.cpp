#include "../dataVector.hpp"

double DataVector::skewConfidence(double alpha, Limit lim) {
  if (stat.skewConfidence.count(alpha) != 1)
    computeSkewConfidence(alpha);

  if (lim == Limit::LowerL)
    return stat.skewConfidence[alpha].first;
  else if (lim == Limit::UpperL)
    return stat.skewConfidence[alpha].second;
  else
    return qQNaN();
};

void DataVector::computeSkewConfidence(double alpha) {
  stat.skewConfidence[alpha] = Statistics::thetaDeviation(
      skew(Measure::PopulationM), skewDeviation(), alpha, size());
}
