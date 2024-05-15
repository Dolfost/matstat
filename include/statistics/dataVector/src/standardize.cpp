#include "../dataVector.hpp"

void DataVector::standardize() {
  double meanValue = mean();
  double standardDeviationValue = standardDeviation(Measure::SampleM);

  for (auto &x : dataVector) {
    x = (x - meanValue) / standardDeviationValue;
  }

  for (auto &x : timeSeries) {
    x = (x - meanValue) / standardDeviationValue;
  }

  clearStatistics();
}
