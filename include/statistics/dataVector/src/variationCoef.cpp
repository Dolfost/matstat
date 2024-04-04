#include "../dataVector.hpp"
#include <cfloat>

double DataVector::variationCoef(Measure m) {
  if (!stat.variationCoef.second)
    computeVariationCoef();

  if (m == Measure::PopulationM)
    return stat.variationCoef.first.first;
  if (m == Measure::SampleM)
    return stat.variationCoef.first.second;
  else
    return qQNaN();
}

double DataVector::nonparametricVariationCoef() {
  if (!stat.nonparametricVariationCoef.second)
    computeNonparametricVariationCoef();

  return stat.nonparametricVariationCoef.first;
}

void DataVector::computeVariationCoef() {
  if (mean() == 0) {
    stat.variationCoef.first.first = DBL_MAX;
    stat.variationCoef.first.second = DBL_MAX;
  } else {
    stat.variationCoef.first.first = variance(Measure::PopulationM) / mean();
    stat.variationCoef.first.second = variance(Measure::SampleM) / mean();
  }

  stat.variationCoef.second = true;
}

void DataVector::computeNonparametricVariationCoef() {
  stat.nonparametricVariationCoef.first = mad() / med();
  stat.nonparametricVariationCoef.second = true;
}
