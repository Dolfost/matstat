#include "../dataVector.hpp"

double DataVector::kurtosisConfidence(double alpha, Limit lim) {
  if (stat.kurtosisConfidence.count(alpha) != 1)
    computeKurtosisConfidence(alpha);

  if (lim == Limit::LowerL)
    return stat.kurtosisConfidence[alpha].first;
  else if (lim == Limit::UpperL)
    return stat.kurtosisConfidence[alpha].second;
  else
    return qQNaN();
};

void DataVector::computeKurtosisConfidence(double alpha) {
  stat.kurtosisConfidence[alpha] = Statistics::thetaDeviation(
      kurtosis(Measure::PopulationM), kurtosisDeviation(), alpha, size());
}
