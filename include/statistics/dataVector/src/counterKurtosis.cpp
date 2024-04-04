#include "../dataVector.hpp"

double DataVector::counterKurtosis(Measure m) {
  if (!stat.counterKurtosis.second)
    computeCounterKurtosis();

  if (m == Measure::PopulationM)
    return stat.counterKurtosis.first.first;
  if (m == Measure::SampleM)
    return stat.counterKurtosis.first.second;
  else
    return qQNaN();
}

void DataVector::computeCounterKurtosis() {
  stat.counterKurtosis.first.first =
      1.0 / sqrt(abs(kurtosis(Measure::SampleM)));
  stat.counterKurtosis.first.second =
      1.0 / sqrt(abs(kurtosis(Measure::PopulationM)));

  stat.counterKurtosis.second = true;
}
