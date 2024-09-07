#include "vector.hpp"

namespace ss {

Vector::Vector(const std::list<double> &input) {
  setVector(input);
}

Vector::Vector(Vector &dv) {
  setVector(dv);
}

void Vector::setVector(const std::list<double> &input) {
  static_cast<std::list<double>&>(*this) = input;
  invalidate();
}

void Vector::invalidate() {
  rawMoment.invalidate();
	centralMoment.invalidate();
  tmean.invalidate();

  meanDeviation.invalidate();
  varianceDeviation.invalidate();
  skewDeviation.invalidate();
  kurtosisDeviation.invalidate();

  meanConfidence.invalidate();
  varianceConfidence.invalidate();
  skewConfidence.invalidate();
  kurtosisConfidence.invalidate();

  beta.invalidate();

  sd.invalidate();
  mad.invalidate();
  skew.invalidate();
  kurtosis.invalidate();
  counterKurtosis.invalidate();
  cv.invalidate();
	ncv.invalidate();
  walshAverages.invalidate();
  walshAveragesMed.invalidate();

	sorted.invalidate();

  reproduceDistribution(Distribution::Model::Unknown);
	pearConsentCriterion.invalidate();
	kolmConsentCriterion.invalidate();

	varSeries.invalidate();
	classSeries.invalidate();
}

QString Vector::report() {
  return QString("Мат. сподівння (v₁) %1\n"
                 "Варіабельність (u₂) %2\n"
                 "Медіана (MED) %3\n"
                 "Усічене середнє (α=0.25) %4\n"
                 "Медіана середніх Уолша (MED*) %5\n"
                 "CКВ (σ) %6\n"
                 "Абсолютне відхилення медіани (MAD) %7\n"
                 "Коеф. асиметрії (A) %8\n"
                 "Ексцесс %9\n"
                 "Коефіцієнт варіації (Пірсона) (W) %10\n")
      .arg(mean())
      .arg(variance())
      .arg(med())
      .arg(tmean(0.25))
      .arg(walshAveragesMed())
      .arg(sd())
      .arg(mad())
      .arg(skew())
      .arg(kurtosis())
      .arg(cv());
}

Vector::~Vector() {
}

}
