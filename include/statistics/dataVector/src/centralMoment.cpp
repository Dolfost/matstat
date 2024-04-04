#include "../dataVector.hpp"

double DataVector::variance(Measure m) { return centralMoment(2, m); }

double DataVector::centralMoment(double degree, Measure m) {
  if (stat.centralMoment.count(degree) != 1)
    computeCentralMoment(degree);

  if (m == Measure::PopulationM)
    return stat.centralMoment[degree].first;
  if (m == Measure::SampleM)
    return stat.centralMoment[degree].second;
  else
    return qQNaN();
}

void DataVector::computeCentralMoment(double degree) {
  double *populationMoment = &stat.centralMoment[degree].first;
  double *sampleMoment = &stat.centralMoment[degree].second;
  double meanValue = mean();
  double moment = 0;

  for (auto const &i : dataVector) {
    moment += std::pow(i - meanValue, degree);
  }

  *populationMoment = moment / size();
  *sampleMoment = moment / (size() - 1);
}
