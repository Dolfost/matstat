#include "vector.hpp"

namespace ss {
#include <cfloat>

void Vector::CoefficientOfVariation::adapt() {
  if (s_vector->mean() == 0) {
    s_value.first = DBL_MAX;
    s_value.second = DBL_MAX;
  } else {
    s_value.first = s_vector->variance(Measure::Population) / s_vector->mean();
    s_value.second = s_vector->variance(Measure::Sample) / s_vector->mean();
  }
}

void Vector::NonparametricCoefficientOfVariation::adapt() {
  s_value = s_vector->mad() / s_vector->med();
}

}
