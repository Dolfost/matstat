#include "../dataVector.hpp"
#include "classSeries.hpp"
#include <QtCore/qlogging.h>

double DataVector::kolmConsentCriterion() {
  if (rep.model == DistributionReproducer::Distribution::UnknownD)
    return qQNaN();

  if (stat.kolmConsentCriterion.second == false)
    computeKolmConsentCriterion();

  return stat.kolmConsentCriterion.first;
}

void DataVector::computeKolmConsentCriterion() {
  auto x1 = dataVector.begin(), x2 = ++dataVector.begin();

  double k;
  if (rep.domain.first != rep.domain.second)
	  k =  std::abs(rep.domain.first - rep.domain.second) /
		  std::abs(min() - max());
  else 
	  k = 1;

  double cdfv = cs->eCdf(*x2), 
		 Dp = std::abs(cdfv - rep.cdf(*x2*k)),
		 Dm = std::abs(cdfv - rep.cdf(*x1*k));

  x1++;
  x2++;

  while (x2 != dataVector.end()) {
	  cdfv = cs->eCdf(*x2);

	  double DpTmp = std::abs(cdfv - rep.cdf(*x2*k));
	  if (DpTmp > Dp)
		  Dp = DpTmp;

	  double DmTmp = std::abs(cdfv - rep.cdf(*x1*k));
	  if (DmTmp > Dm)
		  Dm = DmTmp;

	  qDebug() << cdfv;
	  qDebug() << *x1*k << *x2*k;
	  qDebug() << "";

	  x1++;
	  x2++;
  }

  double z = std::sqrt(size()) * std::max(Dp, Dm);

  double tmp = 0;
  for (int k = 1; k <= 4; k++) {
    double pm = (1 - (k & 2 ? -1 : +1)), f1 = std::pow(k, 2) - pm / 2,
           f2 = 5 * std::pow(k, 2) + 22 - pm * 7.5;

    tmp += (k % 2 ? -1 : 1) * std::exp(-2 * std::pow(k, 2) * std::pow(z, 2)) *
           (1 - (2 * std::pow(k, 2) * z) / (3 * sqrt(size())) -
            (1.0 / (18 * size())) *
                ((f1 - 4 * (f1 + 3)) * std::pow(k, 2) * std::pow(z, 2) +
                 8 * std::pow(k, 4) * std::pow(z, 4)) +
            ((std::pow(k, 2) * z) / (27 * std::pow(size(), 1.5))) *
                (std::pow(f2, 2) / 5 -
                 (4 * (f2 + 45) * std::pow(k, 2) * std::pow(z, 2)) / 15 +
                 8 * std::pow(k, 4) * std::pow(z, 4)));
  }

  stat.kolmConsentCriterion.first = 1 + 2 * tmp;
  stat.kolmConsentCriterion.second = true;
}
