#include "vector.hpp"

namespace ss {

void MeanAbsoluteDeviation::adapt() {
  std::list<double> madVector;
  double medValue = s_vector.med();

  for (auto const &i : s_vector) {
    madVector.push_back(abs(i - medValue));
  }

  Vector madDataVector(madVector);

  s_value = 1.483 * madDataVector.med();
}

}
