#include "vector.hpp"
#include "sstream"

namespace ss {

Vector::Vector() {
	setExprtkSymbolTable();
}

Vector::Vector(const std::list<double> &input): Vector() {
  setVector(input);
}

Vector::Vector(const Vector &other): Vector() {
	static_cast<std::list<double>&>(*this) = std::list<double>(other);

	// rawMoment = other.rawMoment;
	// meanDeviation = other.meanDeviation;
	// meanConfidence = other.meanConfidence;
	// centralMoment = other.centralMoment;
	// varianceDeviation = other.varianceDeviation;
	// varianceConfidence = other.varianceConfidence;
	// skew = other.skew;
	// skewDeviation = other.skewDeviation;
	// skewConfidence = other.skewConfidence;
	// kurtosis = other.kurtosis;
	// kurtosisDeviation = other.kurtosisDeviation;
	// kurtosisConfidence = other.kurtosisConfidence;
	// mad = other.mad;
	// tmean = other.tmean;
	// counterKurtosis = other.counterKurtosis;
	// sd = other.sd;
	// beta = other.beta;
	// walshAverages = other.walshAverages;
	// walshAveragesMed = other.walshAveragesMed;
	// kolmConsentCriterion = other.kolmConsentCriterion;
	// pearConsentCriterion = other.pearConsentCriterion;
	// cv = other.cv;
	// ncv = other.ncv;
	// min = other.min;
	// max = other.max;
	// len = other.len;
	// sorted = other.sorted;
	//
	// cs = other.cs;
	// vs = other.vs;
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

	vs.invalidate();
	cs.invalidate();

	ranks.invalidate();

	v_invalidateCallback();
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
