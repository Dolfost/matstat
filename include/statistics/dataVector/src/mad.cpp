#include "../dataVector.hpp"

double DataVector::mad() {
  if (!stat.mad.second)
    computeMad();

  return stat.mad.first;
}

void DataVector::computeMad() {
  std::list<double> madVector;
  double medValue = med();

  for (auto const &i : dataVector) {
    madVector.push_back(abs(i - medValue));
  }

  DataVector madDataVector(madVector);

  stat.mad.first = 1.483 * madDataVector.med();

  stat.mad.second = true;
}
