#include "../dataVector.hpp"

double DataVector::standardDeviation(Measure m) {
  if (!stat.standardDeviation.second)
    computeStandardDeviation();

  if (m == Measure::PopulationM)
    return stat.standardDeviation.first.first;
  if (m == Measure::SampleM)
    return stat.standardDeviation.first.second;
  else
    return qQNaN();
}

void DataVector::computeStandardDeviation() {
  stat.standardDeviation.first.first =
      std::sqrt(centralMoment(2, Measure::PopulationM));
  stat.standardDeviation.first.second =
      std::sqrt(centralMoment(2, Measure::SampleM));

  stat.standardDeviation.second = true;
}
