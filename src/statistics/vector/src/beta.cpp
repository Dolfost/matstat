#include "vector.hpp"

namespace ss {

void Vector::Beta::adapt(size_t k) {
  double *betaValue = &s_values[k];

  if (k % 2) {
    k /= 2;
    *betaValue = (s_vector.centralMoment(3, Measure::Population) *
                  s_vector.centralMoment(2 * k + 3, Measure::Population)) /
                 pow(s_vector.centralMoment(2, Measure::Population), k + 3);
 } else {
    k /= 2;
    *betaValue = s_vector.centralMoment(2 * k + 2, Measure::Population) /
                 pow(s_vector.centralMoment(2, Measure::Population), k + 1);
  }
}

}
