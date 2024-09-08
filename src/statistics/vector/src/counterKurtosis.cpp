#include "vector.hpp"

namespace ss {

void Vector::CounterKurtosis::adapt() {
  s_value.first =
      1.0 / sqrt(abs(s_vector.kurtosis(Measure::Sample)));
  s_value.second =
      1.0 / sqrt(abs(s_vector.kurtosis(Measure::Population)));
}

}
