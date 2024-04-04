#include "../dataVector.hpp"

#include "classSeries.hpp"
#include "varSeries.hpp"

DataVector::DataVector(const std::list<double> &input) {
  setVector(input);
  cs = new ClassSeries(this);
  vs = new VarSeries(this);
}

DataVector::DataVector(DataVector &dv) {
  setVector(dv.vector());
  cs = new ClassSeries(this);
  vs = new VarSeries(this);
}

void DataVector::setVector(const std::list<double> &input) {
  dataVector = input;
  dataVector.sort();
  clearStatistics();
}

const std::list<double> &DataVector::vector() { return dataVector; }

void DataVector::clearStatistics() {
  stat.rawMoment.clear();
  stat.centralMoment.clear();
  stat.turncatedMean.clear();
  stat.walshAverages.first.clear();
  stat.walshAverages.second = false;

  stat.meanDeviation.second = false;
  stat.varianceDeviation.second = false;
  stat.skewDeiviation.second = false;
  stat.kurtosisDeviation.second = false;

  stat.meanConfidence.clear();
  stat.varianceConfidence.clear();
  stat.skewConfidence.clear();
  stat.kurtosisConfidence.clear();

  stat.beta.clear();

  stat.standardDeviation.second = false;
  stat.mad.second = false;
  stat.skew.second = false;
  stat.kurtosis.second = false;
  stat.variationCoef.second = false;
  stat.counterKurtosis.second = false;
  stat.nonparametricVariationCoef.second = false;
  stat.walshAverages.second = false;
  stat.walshAveragesMed.second = false;

  reproduceDistribution(DistributionReproducer::Distribution::UnknownD);
  stat.pearConsentCriterion.second = false;
  stat.kolmConsentCriterion.second = false;
  vsReady = false;
  csReady = false;

  stat.min.second = false;
  stat.max.second = false;
  stat.size.second = false;
}

QString DataVector::report() {
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
      .arg(turncatedMean(0.25))
      .arg(walshAveragesMed())
      .arg(standardDeviation())
      .arg(mad())
      .arg(skew())
      .arg(kurtosis())
      .arg(variationCoef());
}

DataVector::~DataVector() {
  delete cs;
  delete vs;
}
