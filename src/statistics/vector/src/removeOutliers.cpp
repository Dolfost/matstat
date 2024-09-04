#include "vector.hpp"

namespace ss {

bool Vector::removeOutliers() {
  int popCount = 0;

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
	  auto it = std::find(timeSeries.begin(), timeSeries.end(), dataVector.front());
	  if(it != timeSeries.end())
		  timeSeries.erase(it);

      dataVector.pop_front();
      clearStatistics();
      popCount++;
      continue;
    }

    if (b < dataVector.back()) {
	  auto it = std::find(timeSeries.begin(), timeSeries.end(), dataVector.back());
	  if(it != timeSeries.end())
		  timeSeries.erase(it);
	  
      dataVector.pop_back();
      clearStatistics();
      popCount++;
      continue;
    }

    break;
  }

  if (popCount == 0)
    return false;

  return true;
}

}
