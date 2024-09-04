#include "vector.hpp"

namespace ss {

void Vector::standardize() {
  double meanValue = mean();
  double standardDeviationValue = sd(Measure::Sample);

  for (auto &x : dataVector) {
    x = (x - meanValue) / standardDeviationValue;
  }

  for (auto &x : timeSeries) {
    x = (x - meanValue) / standardDeviationValue;
  }

  clearStatistics();
}

}
