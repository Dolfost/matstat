#include "vector.hpp"

namespace ss {

// double Vector::variance(Measure m) { return centralMoment(2, m); }
//
// double Vector::centralMoment(double degree, Measure m) {
//   if (stat.centralMoment.count(degree) != 1)
//     computeCentralMoment(degree);
//
//   if (m == Measure::PopulationM)
//     return stat.centralMoment[degree].first;
//   if (m == Measure::SampleM)
//     return stat.centralMoment[degree].second;
//   else
//     return qQNaN();
// }

// void Vector::computeCentralMoment(double degree) {
// }
//
// }

void CentralMoment::adapt(double degree) {
  double *populationMoment = &s_values[degree].first;
  double *sampleMoment = &s_values[degree].second;
  double meanValue = s_vector.mean();
  double moment = 0;

  for (auto const &i : s_vector.vector()) {
    moment += std::pow(i - meanValue, degree);
  }

  *populationMoment = moment / s_vector.size();
  *sampleMoment = moment / (s_vector.size() - 1);
}

void VarianceDeviation::adapt() {
	s_value = sqrt(
		(1.0 / s_vector.size()) * (s_vector.centralMoment(4) - (s_vector.size() - 3.0) / (s_vector.size() - 1.0) *
		pow(s_vector.sd(), 4)));
}

void VarianceConfidence::adapt(double alpha) {
	s_values[alpha] = thetaDeviation(
		s_vector.variance(Measure::Population), 
		s_vector.varianceDeviation(), 
		alpha, s_vector.size()
	);
}

}
