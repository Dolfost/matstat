#include "../dataVector.hpp"

double DataVector::med() { return turncatedMean(0.5); }

double DataVector::turncatedMean(double degree) {
  size_t k = degree * size() - (size() % 2 ? 0 : 1);
  if (stat.turncatedMean.count(k) != 1)
    computeTurncatedMean(k);

  return stat.turncatedMean[k];
}

void DataVector::computeTurncatedMean(size_t k) {
  double *turncatedMean = &stat.turncatedMean[k];

  auto front = dataVector.begin();
  auto back = dataVector.end();
  std::advance(front, k);
  std::advance(back, -k);

  while (front != back) {
    *turncatedMean += *front;
    front++;
  }

  *turncatedMean /= (size() - 2 * k);
}
