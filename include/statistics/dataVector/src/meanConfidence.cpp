#include "../dataVector.hpp"

double DataVector::meanConfidence(double alpha, Limit lim) {
  if (stat.meanConfidence.count(alpha) != 1)
    computeMeanConfidence(alpha);

  if (lim == Limit::LowerL)
    return stat.meanConfidence[alpha].first;
  else if (lim == Limit::UpperL)
    return stat.meanConfidence[alpha].second;
  else
    return qQNaN();
}

void DataVector::computeMeanConfidence(double alpha) {
  stat.meanConfidence[alpha] =
      Statistics::thetaDeviation(mean(), meanDeviation(), alpha, size());
}
