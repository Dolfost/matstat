#include "vector.hpp"

namespace ss {

double Vector::cdf(double x) {
  if (x >= max())
    return 1.0;

	std::size_t n = 0;
  for (auto const xl : sorted()) {
    if (xl <= x)
      n++;
    else
      break;
  }

  return double(n) / size();
}

}
