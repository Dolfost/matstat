#include "vector.hpp"
#include "vector/quantile.hpp"

namespace ss {

void Vector::Skew::adapt() {
  double N = s_vector.size();
  s_value.first = s_vector.centralMoment(3, Measure::Population) /
                          pow(s_vector.sd(Measure::Population), 3);
  s_value.second =
      (std::sqrt(N * (N - 1)) / (N - 2)) * s_value.first;
}

void Vector::SkewDeviation::adapt() {
  // there is no way this would have ever worked
  // stat.skewDeiviation.first = sqrt(
  // 		(4*beta(4) - 12*beta(3) -
  // 		24*beta(2)+9*beta(2)*beta(1) + 35*beta(1) - 36) /
  // 		 (4*size()));

  double s = s_vector.size();
	s_value = std::sqrt((6 * (s - 2)) / ((s + 1) * (s + 3)));
}

void Vector::SkewConfidence::adapt(double alpha) {
	s_values[alpha] = thetaDeviation(
		s_vector.skew(Measure::Population), 
		s_vector.skewDeviation(), 
		alpha, s_vector.size()
	);
}

}
