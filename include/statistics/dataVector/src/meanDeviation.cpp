#include "../dataVector.hpp"

double DataVector::meanDeviation() {
  if (stat.meanDeviation.second == false)
    computeMeanDeviation();

  return stat.meanDeviation.first;
}

void DataVector::computeMeanDeviation() {
  stat.meanDeviation.first = standardDeviation() / sqrt(size());
  stat.standardDeviation.second = true;
}
