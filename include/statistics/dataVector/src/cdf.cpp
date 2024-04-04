#include "../dataVector.hpp"

double DataVector::cdf(double x) {
  if (x >= max())
    return 1.0;

  int n = 0;
  for (auto const &xl : dataVector) {
    if (xl <= x)
      n++;
    else
      break;
  }

  return double(n) / size();
}
