#include "../dataVector.hpp"

double DataVector::beta(int k) {
  if (stat.beta.count(k) != 1)
    computeBeta(k);

  return stat.beta.count(k);
}

void DataVector::computeBeta(int k) {
  double *betaValue = &stat.beta[k];

  if (k % 2) {
    k /= 2;
    *betaValue = (centralMoment(3, Measure::PopulationM) *
                  centralMoment(2 * k + 3, Measure::PopulationM)) /
                 pow(centralMoment(2, Measure::PopulationM), k + 3);
  } else {
    k /= 2;
    *betaValue = centralMoment(2 * k + 2, Measure::PopulationM) /
                 pow(centralMoment(2, Measure::PopulationM), k + 1);
  }
}
