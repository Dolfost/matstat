#include "vector.hpp"
#include "sstream"

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

std::string Vector::report() {
	std::stringstream s;
	s << "Мат. сподівння (v₁) " << mean() << "\n"
		<< "Варіабельність (u₂) " << variance() << "\n"
		<< "Медіана (MED) " << med() << "\n"
		<< "Усічене середнє (α=0.25) " << tmean(0.25) << "\n"
		<< "Медіана середніх Уолша (MED*) " << walshAveragesMed() << "\n"
		<< "CКВ (σ) " << sd() << "\n"
		<< "Абсолютне відхилення медіани (MAD) " << mad() << "\n"
		<< "Коеф. асиметрії (A) " << skew() << "\n"
		<< "Ексцесс " << kurtosis() << "\n"
		<< "Коефіцієнт варіації (Пірсона) (W) " << cv() << "\n";

	return s.str();
}

Vector::~Vector() {
}

}
