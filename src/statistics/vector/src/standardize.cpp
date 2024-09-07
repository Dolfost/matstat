#include "vector.hpp"

namespace ss {

void Vector::standardize() {
  double meanValue = mean();
  double sdValue = sd(Measure::Sample);

  for (auto &x : static_cast<std::list<double>&>(*this)) {
    x = (x - meanValue) / sdValue;
  }

  invalidate();
}

}
