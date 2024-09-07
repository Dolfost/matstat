#include "vector.hpp"

namespace ss {

void Vector::standardize() {
  double meanValue = mean();
  double sdValue = sd(Measure::Sample);

  for (auto &x : *this) {
    x = (x - meanValue) / sdValue;
  }

  invalidate();
}

}
