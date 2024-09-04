#include "vector.hpp"

namespace ss {

void Kurtosis::adapt() {
	double N = s_vector.size();

	s_value.first = s_vector.centralMoment(4, Measure::Population) /
		pow(s_vector.sd(Measure::Population), 4);
	s_value.second = ((std::pow(N, 2) - 1) / ((N - 2) * (N - 3))) *
		((s_value.first - 3) + 6 / (N + 1));
}

void KurtosisDeviation::adapt() {
	s_value = sqrt(
		(1.0 / s_vector.size()) * (s_vector.beta(6) - 4 *
		s_vector.beta(4) * s_vector.beta(2) - 8 * s_vector.beta(3) + 4
		* pow(s_vector.beta(2), 3) - pow(s_vector.beta(2), 2) + 16 *
		s_vector.beta(2) * s_vector.beta(1) + 16 * s_vector.beta(1))
	);
}

void KurtosisConfidence::adapt(double alpha) {
	s_values[alpha] = thetaDeviation(
		s_vector.kurtosis(Measure::Population), 
		s_vector.kurtosisDeviation(), 
		alpha, s_vector.size()
	);
}

}
