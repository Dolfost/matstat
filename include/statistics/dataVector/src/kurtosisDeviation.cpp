#include "../dataVector.hpp"

double DataVector::kurtosisDeviation() {
  if (stat.kurtosisDeviation.second == false)
    computeKurtosisDeviation();

  return stat.kurtosisDeviation.first;
}

void DataVector::computeKurtosisDeviation() {
  stat.kurtosisDeviation.first =
      sqrt((1.0 / size()) * (beta(6) - 4 * beta(4) * beta(2) - 8 * beta(3) +
                             4 * pow(beta(2), 3) - pow(beta(2), 2) +
                             16 * beta(2) * beta(1) + 16 * beta(1)));
  stat.kurtosisDeviation.second = true;
}
