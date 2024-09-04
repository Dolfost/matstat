#include "vector.hpp"

namespace ss {

// double Vector::varianceConfidence(double alpha, Bound lim) {
//   if (stat.varianceConfidence.count(alpha) != 1)
//     computeVarianceConfidence(alpha);
//
//   if (lim == Bound::Lower)
//     return stat.varianceConfidence[alpha].first;
//   else if (lim == Bound::Upper)
//     return stat.varianceConfidence[alpha].second;
//   else
//     return qQNaN();
// };
//
// void Vector::computeVarianceConfidence(double alpha) {
//   stat.varianceConfidence[alpha] = Statistics::thetaDeviation(
//       variance(Measure::Population), varianceDeviation(), alpha, size());
// }

}
