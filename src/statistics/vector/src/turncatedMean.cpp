#include "vector.hpp"

namespace ss {

double Vector::TurncatedMean::value(double degree) {
  size_t k = degree * s_vector.size() - (s_vector.size() % 2 ? 0 : 1);
		if (s_values.count(k) != 1)
			adapt(k);

		return s_values[k];
	}

void Vector::TurncatedMean::adapt(std::size_t k) {
  double& turncatedMean = s_values[k];
	turncatedMean = 0;

  auto front = s_vector.cbegin();
  auto back = s_vector.cend();
  std::advance(front, k);
  std::advance(back, -k);

  while (front != back) {
    turncatedMean += *front;
    front++;
  }

  turncatedMean /= (s_vector.size() - 2 * k);
}

}
