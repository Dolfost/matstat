#include "vector.hpp"

namespace ss {

size_t Vector::trim(double from, double to) {
	std::size_t n = size();
  auto x = begin();
  while (x != end()) {
	  if (*x <= to or *x >= from)
		  x = erase(x);
  }

  invalidate();

  return n - size();
}

}
