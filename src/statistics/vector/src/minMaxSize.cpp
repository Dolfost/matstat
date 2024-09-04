#include "vector.hpp"

namespace ss {

double Vector::min() {
  if (!stat.min.second)
    computeMinMaxSize();
  return stat.min.first;
}

double Vector::max() {
  if (!stat.max.second)
    computeMinMaxSize();
  return stat.max.first;
}

size_t Vector::size() {
  if (!stat.size.second)
    computeMinMaxSize();
  return stat.size.first;
}

void Vector::computeMinMaxSize() {
  stat.min.first = dataVector.front();
  stat.max.first = dataVector.back();
  stat.size.first = dataVector.size();

  stat.min.second = true;
  stat.max.second = true;
  stat.size.second = true;
}


}
