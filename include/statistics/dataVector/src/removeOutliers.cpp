#include "../dataVector.hpp"

bool DataVector::removeOutliers() {
  int popCount = 0;

  while (true) {
    double a, b, t1 = 2 + 0.2 * log10(0.04 * size()),
                 t2 = sqrt(19 * sqrt(kurtosis(Measure::SampleM) + 2) + 1);

    if (skew(Measure::SampleM) < -0.2) {
      a = mean() - t2 * standardDeviation(Measure::SampleM);
      b = mean() + t1 * standardDeviation(Measure::SampleM);
    } else if (skew() <= 0.2) { // skew in [-0.2;0.2]
      a = mean() - t1 * standardDeviation(Measure::SampleM);
      b = mean() + t1 * standardDeviation(Measure::SampleM);
    } else {
      a = mean() - t1 * standardDeviation(Measure::SampleM);
      b = mean() + t2 * standardDeviation(Measure::SampleM);
    }

    if (a > dataVector.front()) {
      dataVector.pop_front();
      clearStatistics();
      popCount++;
      continue;
    }

    if (b < dataVector.back()) {
      dataVector.pop_back();
      clearStatistics();
      popCount++;
      continue;
    }

    break;
  }

  if (popCount == 0)
    return false;

  return true;
}
