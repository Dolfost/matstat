#include "../dataVector.hpp"

double DataVector::varianceConfidence(double alpha, Limit lim) {
  if (stat.varianceConfidence.count(alpha) != 1)
    computeVarianceConfidence(alpha);

  if (lim == Limit::LowerL)
    return stat.varianceConfidence[alpha].first;
  else if (lim == Limit::UpperL)
    return stat.varianceConfidence[alpha].second;
  else
    return qQNaN();
};

void DataVector::computeVarianceConfidence(double alpha) {
  stat.varianceConfidence[alpha] = Statistics::thetaDeviation(
      variance(Measure::PopulationM), varianceDeviation(), alpha, size());
}
