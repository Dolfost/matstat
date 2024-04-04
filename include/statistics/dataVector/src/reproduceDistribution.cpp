#include "../dataVector.hpp"

bool DataVector::reproduceDistribution(
    DistributionReproducer::Distribution type) {
  if (csReady == false)
    return false;

  stat.pearConsentCriterion.second = false;
  stat.kolmConsentCriterion.second = false;

  switch (type) {
  case DistributionReproducer::NormalD: {
    rep.setDistribution(
        type,
        {mean(), (size() / (size() - 1.0)) *
                     std::sqrt(rawMoment(2) - std::pow(rawMoment(1), 2))},
        size());
    break;
  }
  case DistributionReproducer::ExponentialD: {
    rep.setDistribution(type, {1 / mean()}, size());
    break;
  }
  case DistributionReproducer::WeibullD: {
    double a11 = size() - 1;
    double a21 = 0, a22 = 0, b1 = 0, b2 = 0;
    for (auto it = dataVector.begin(); it != std::prev(dataVector.end(), 1);
         it++) {
      double tmp = log(*it);
      a21 += tmp;
      a22 += std::pow(tmp, 2);
      double lnValue = log(log(1 / (1 - cdf(*it))));
      b1 += lnValue;
      b2 += tmp * lnValue;
    }

    double beta = (a21 * b1 - a11 * b2) / (std::pow(a21, 2) - a11 * a22);
    // (a11b2-b1a21)/(a11a22-a21^2)

    double S = 0;
    for (auto it = dataVector.begin(); it != std::prev(dataVector.end(), 1);
         it++) {
      S += pow(log(log(1 / (1 - cdf(*it))) - skew(Measure::PopulationM) -
                   beta * log(*it)),
               2);
    }

    S /= size() - 3;

    rep.setDistribution(type,
                        {exp(-skew(Measure::PopulationM)), beta,
                         skew(Measure::PopulationM), S, a11, a21, a22},
                        size());
    break;
  }
  case DistributionReproducer::LogNormalD: {
    rep.setDistribution(type,
                        {2 * log(mean()) - log(rawMoment(2)) / 2,
                         sqrt(log(rawMoment(2)) - 2 * log(mean()))},
                        size());
    break;
  }
  case DistributionReproducer::UniformD: {
    double pm = std::sqrt(3 * (rawMoment(2) - std::pow(mean(), 2)));
    rep.setDistribution(type, {mean() - pm, mean() + pm}, size());
    break;
  }
  case DistributionReproducer::UnknownD: {
    rep.setDistribution(type, {}, size());
    break;
  }
  default:
    break;
  }

  return true;
}
