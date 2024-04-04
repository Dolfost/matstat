#include "../dataVector.hpp"

double DataVector::kurtosis(Measure m) {
  if (!stat.kurtosis.second)
    computeKurtosis();

  if (m == Measure::PopulationM)
    return stat.kurtosis.first.first;
  if (m == Measure::SampleM)
    return stat.kurtosis.first.second;
  else
    return qQNaN();
}

void DataVector::computeKurtosis() {
  double N = size();

  stat.kurtosis.first.first = centralMoment(4, Measure::PopulationM) /
                              pow(standardDeviation(Measure::PopulationM), 4);
  stat.kurtosis.first.second = ((std::pow(N, 2) - 1) / ((N - 2) * (N - 3))) *
                               ((stat.kurtosis.first.first - 3) + 6 / (N + 1));

  stat.kurtosis.second = true;
}
