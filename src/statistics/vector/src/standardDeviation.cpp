#include "vector.hpp"

namespace ss {

void Vector::StandardDeviation::adapt() {
  s_value.first =
      std::sqrt(s_vector->centralMoment(2, Measure::Population));
  s_value.second =
      std::sqrt(s_vector->centralMoment(2, Measure::Sample));
}

}
