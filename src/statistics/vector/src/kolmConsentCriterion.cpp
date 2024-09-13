#include "vector.hpp"

namespace ss {

void Vector::KolmConsentCriterion::adapt() {
  auto x1 = s_vector->cbegin(), x2 = ++s_vector->cbegin();

  double k;
  if (s_vector->dist.domain.first != s_vector->dist.domain.second)
	  k =  std::abs(s_vector->dist.domain.first - s_vector->dist.domain.second) /
		  std::abs(s_vector->min() - s_vector->max());
  else 
	  k = 1;

  double cdfv = s_vector->cs.cdf(*x2), 
		 Dp = std::abs(cdfv - s_vector->dist.cdf(*x2*k)),
		 Dm = std::abs(cdfv - s_vector->dist.cdf(*x1*k));

  x1++;
  x2++;

  while (x2 != s_vector->cend()) {
	  cdfv = s_vector->cs.cdf(*x2);

	  double DpTmp = std::abs(cdfv - s_vector->dist.cdf(*x2*k));
	  if (DpTmp > Dp)
		  Dp = DpTmp;

	  double DmTmp = std::abs(cdfv - s_vector->dist.cdf(*x1*k));
	  if (DmTmp > Dm)
		  Dm = DmTmp;

	  // qDebug() << cdfv;
	  // qDebug() << *x1*k << *x2*k;
	  // qDebug() << "";

	  x1++;
	  x2++;
  }

  double z = std::sqrt(s_vector->size()) * std::max(Dp, Dm);

  double tmp = 0;
  for (int k = 1; k <= 4; k++) {
    double pm = (1 - (k & 2 ? -1 : +1)), f1 = std::pow(k, 2) - pm / 2,
           f2 = 5 * std::pow(k, 2) + 22 - pm * 7.5;

    tmp += (k % 2 ? -1 : 1) * std::exp(-2 * std::pow(k, 2) * std::pow(z, 2)) *
           (1 - (2 * std::pow(k, 2) * z) / (3 * sqrt(s_vector->size())) -
            (1.0 / (18 * s_vector->size())) *
                ((f1 - 4 * (f1 + 3)) * std::pow(k, 2) * std::pow(z, 2) +
                 8 * std::pow(k, 4) * std::pow(z, 4)) +
            ((std::pow(k, 2) * z) / (27 * std::pow(s_vector->size(), 1.5))) *
                (std::pow(f2, 2) / 5 -
                 (4 * (f2 + 45) * std::pow(k, 2) * std::pow(z, 2)) / 15 +
                 8 * std::pow(k, 4) * std::pow(z, 4)));
  }

  s_value = 1 + 2 * tmp;
}

}
