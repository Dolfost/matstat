#include "../dataVector.hpp"

double DataVector::mean() { return rawMoment(1); }

double DataVector::rawMoment(double degree) {
  if (stat.rawMoment.count(degree) != 1)
    computeRawMoment(degree);

  return stat.rawMoment[degree];
}

void DataVector::computeRawMoment(double degree) {
  double *moment = &stat.rawMoment[degree];

  for (auto const &i : dataVector) {
    *moment += std::pow(i, degree);
  }

  *moment /= size();
}

