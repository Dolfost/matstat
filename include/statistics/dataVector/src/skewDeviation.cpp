#include "../dataVector.hpp"

double DataVector::skewDeviation() {
  if (stat.skewDeiviation.second == false)
    computeSkewDeviation();

  return stat.skewDeiviation.first;
}

void DataVector::computeSkewDeviation() {
  // there is no way this would have ever worked
  // stat.skewDeiviation.first = sqrt(
  // 		(4*beta(4) - 12*beta(3) -
  // 		24*beta(2)+9*beta(2)*beta(1) + 35*beta(1) - 36) /
  // 		 (4*size()));

  stat.skewDeiviation.first =
      std::sqrt((6 * (size() - 2)) / ((size() + 1) * (size() + 3)));
  stat.skewDeiviation.second = true;
}
