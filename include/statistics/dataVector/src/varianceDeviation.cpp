#include "../dataVector.hpp"

double DataVector::varianceDeviation() {
  if (stat.varianceDeviation.second == false)
    computeVarianceDeviation();

  return stat.varianceDeviation.first;
}

void DataVector::computeVarianceDeviation() {
  stat.varianceDeviation.first = sqrt(
      (1.0 / size()) * (centralMoment(4) - (size() - 3.0) / (size() - 1.0) *
                                               pow(standardDeviation(), 4)));
  stat.varianceDeviation.second = true;
}
