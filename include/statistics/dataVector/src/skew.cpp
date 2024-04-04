#include "../dataVector.hpp"

double DataVector::skew(Measure m) {
  if (!stat.skew.second)
    computeSkew();

  if (m == Measure::PopulationM)
    return stat.skew.first.first;
  if (m == Measure::SampleM)
    return stat.skew.first.second;
  else
    return qQNaN();
}

void DataVector::computeSkew() {
  double N = size();
  stat.skew.first.first = centralMoment(3, Measure::PopulationM) /
                          pow(standardDeviation(Measure::PopulationM), 3);
  stat.skew.first.second =
      (std::sqrt(N * (N - 1)) / (N - 2)) * stat.skew.first.first;

  stat.skew.second = true;
}
