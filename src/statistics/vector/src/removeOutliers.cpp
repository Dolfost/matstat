#include "vector.hpp"

namespace ss {

bool Vector::removeOutliers() {
	std::size_t popCount = 0;

	Vector dataVector = sorted();

  while (true) {
    double a, b, t1 = 2 + 0.2 * log10(0.04 * size()),
                 t2 = sqrt(19 * sqrt(kurtosis(Measure::Sample) + 2) + 1);

    if (skew(Measure::Sample) < -0.2) {
      a = mean() - t2 * sd(Measure::Sample);
      b = mean() + t1 * sd(Measure::Sample);
    } else if (skew() <= 0.2) { // skew in [-0.2;0.2]
      a = mean() - t1 * sd(Measure::Sample);
      b = mean() + t1 * sd(Measure::Sample);
    } else {
      a = mean() - t1 * sd(Measure::Sample);
      b = mean() + t2 * sd(Measure::Sample);
    }

    if (a > dataVector.front()) {
	  auto it = std::find(begin(), end(), front());
	  if(it != end())
		  erase(it);

			erase(begin());
      invalidate();
      popCount++;
      continue;
    }

    if (b < dataVector.back()) {
	  auto it = std::find(begin(), end(), dataVector.back());
	  if(it != end())
		  erase(it);
	  
      dataVector.pop_back();
      invalidate();
      popCount++;
      continue;
    }

    break;
  }

	static_cast<std::vector<double>&>(*this) = dataVector;
	invalidate();

  return popCount != 0;
}

}
