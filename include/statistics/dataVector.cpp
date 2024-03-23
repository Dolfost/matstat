#include "dataVector.hpp"

#include <QtCore/qalgorithms.h>
#include <QtCore/qlogging.h>
#include <QtCore/qnumeric.h>
#include <cmath>
#include <cfloat>
#include <iterator>

#include "dataVectorExprtk.hpp"

#include "statisticsExprtk.hpp"
#include "statistics.hpp"


DataVector::DataVector(const std::list<double>& input) {
	setVector(input);
}

DataVector::DataVector(DataVector& dv) {
	setVector(dv.vector());
}

void DataVector::setVector(const std::list<double>& input) {
	dataVector = input;
	dataVector.sort();
	clearStatistics();
}

const std::list<double>& DataVector::vector() {
	return dataVector;
}

////// Statistics ////// 
double DataVector::min() {
	if (!stat.min.second)
		computeMinMaxSize();
	return stat.min.first;
}

double DataVector::max() {
	if (!stat.max.second)
		computeMinMaxSize();
	return stat.max.first;
}

size_t DataVector::size() {
	if (!stat.size.second)
		computeMinMaxSize();
	return stat.size.first;
}

double DataVector::mean() {
	return rawMoment(1);
}

double DataVector::variance(Measure m) {
	return centralMoment(2, m);
}

double DataVector::standardDeviation(Measure m) {
	if (!stat.standardDeviation.second)
		computeStandardDeviation();

	if (m == Measure::PopulationM)
		return stat.standardDeviation.first.first;
	if (m == Measure::SampleM)
		return stat.standardDeviation.first.second;
	else
		return qQNaN();
}

double DataVector::rawMoment(double degree) {
	if (stat.rawMoment.count(degree) != 1)
		computeRawMoment(degree);

	return stat.rawMoment[degree];
}

double DataVector::centralMoment(double degree, Measure m) {
	if (stat.centralMoment.count(degree) != 1)
		computeCentralMoment(degree);

	if (m == Measure::PopulationM)
		return stat.centralMoment[degree].first;
	if (m == Measure::SampleM)
		return stat.centralMoment[degree].second;
	else
	 return qQNaN();
}

double DataVector::turncatedMean(double degree) {
	size_t k = degree*size() - (size()%2 ? 0 : 1);
	if (stat.turncatedMean.count(k) != 1)
		computeTurncatedMean(k);

	return stat.turncatedMean[k];
}

double DataVector::med() {
	return turncatedMean(0.5);
}

double DataVector::mad() {
	if (!stat.mad.second)
		computeMad();

	return stat.mad.first;
}

double DataVector::skew(Measure m) {
	if (!stat.skew.second)
		computeSkew();

	if (m == Measure::PopulationM)
		return stat.skew.first.first;
	if (m == Measure::SampleM)
		return stat.skew.first.second;
	else
	 return qQNaN();
}

double DataVector::kurtosis(Measure m) {
	if (!stat.kurtosis.second)
		computeKurtosis();

	if (m == Measure::PopulationM)
		return stat.kurtosis.first.first;
	if (m == Measure::SampleM)
		return stat.kurtosis.first.second;
	else
	 return qQNaN();
}

double DataVector::counterKurtosis(Measure m) {
	if (!stat.counterKurtosis.second)
		computeCounterKurtosis();

	if (m == Measure::PopulationM)
		return stat.counterKurtosis.first.first;
	if (m == Measure::SampleM)
		return stat.counterKurtosis.first.second;
	else
	 return qQNaN();
}

std::list<double> DataVector::walshAverages() {
	if (!stat.walshAverages.second)
		computeWalshAverages();

	return stat.walshAverages.first;
}

double DataVector::walshAveragesMed() {
	if (!stat.walshAveragesMed.second)
		computeWalshAveragesMed();

	return stat.walshAveragesMed.first;
}

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

double DataVector::beta(int k) {
	if (stat.beta.count(k) != 1)
		computeBeta(k);

	return stat.beta.count(k);
}

double DataVector::eCdf(double x) {
	if (x >= max())
		return 1.0;

	int n = 0;
	for (auto const& xl : dataVector) {
		if (xl <= x)
			n++;
		else
		 break;
	}

	return double(n)/size();
}

double DataVector::meanDeviation() {
	if (stat.meanDeviation.second == false)
		computeMeanDeviation();

	return stat.meanDeviation.first;
}

double DataVector::varianceDeviation() {
	if (stat.varianceDeviation.second == false)
		computeVarianceDeviation();

	return stat.varianceDeviation.first;
}

double DataVector::skewDeviation() {
	if (stat.skewDeiviation.second == false)
		computeSkewDeviation();

	return stat.skewDeiviation.first;
}

double DataVector::kurtosisDeviation() {
	if (stat.kurtosisDeviation.second == false)
		computeKurtosisDeviation();

	return stat.kurtosisDeviation.first;
}

double DataVector::meanConfidence(double alpha, Limit lim) {
	if (stat.meanConfidence.count(alpha) != 1)
		computeMeanConfidence(alpha);

	if (lim == Limit::LowerL)
		return stat.meanConfidence[alpha].first;
	else if (lim == Limit::UpperL)
		return stat.meanConfidence[alpha].second;
	else
		return qQNaN();
}

double DataVector::varianceConfidence(double alpha, Limit lim) {
	if (stat.varianceConfidence.count(alpha) != 1)
		computeVarianceConfidence(alpha);

	if (lim == Limit::LowerL)
		return stat.varianceConfidence[alpha].first;
	else if (lim == Limit::UpperL)
		return stat.varianceConfidence[alpha].second;
	else
		return qQNaN();
};
double DataVector::skewConfidence(double alpha, Limit lim) {
	if (stat.skewConfidence.count(alpha) != 1)
		computeSkewConfidence(alpha);

	if (lim == Limit::LowerL)
		return stat.skewConfidence[alpha].first;
	else if (lim == Limit::UpperL)
		return stat.skewConfidence[alpha].second;
	else
		return qQNaN();
};

double DataVector::kurtosisConfidence(double alpha, Limit lim) {
	if (stat.kurtosisConfidence.count(alpha) != 1)
		computeKurtosisConfidence(alpha);

	if (lim == Limit::LowerL)
		return stat.kurtosisConfidence[alpha].first;
	else if (lim == Limit::UpperL)
		return stat.kurtosisConfidence[alpha].second;
	else
		return qQNaN();
};

// statistic computers //
void DataVector::computeMinMaxSize() {
	stat.min.first = dataVector.front();
	stat.max.first = dataVector.back();
	stat.size.first = dataVector.size();

	stat.min.second = true;
	stat.max.second = true;
	stat.size.second = true;
}

void DataVector::computeRawMoment(double degree) {
	double* moment = &stat.rawMoment[degree];

	for (auto const& i : dataVector) {
		*moment += std::pow(i, degree);
	}

	*moment /= size();
}

void DataVector::computeCentralMoment(double degree) {
	double* populationMoment = &stat.centralMoment[degree].first;
	double* sampleMoment = &stat.centralMoment[degree].second;
	double meanValue = mean();
	double moment = 0;

	for (auto const& i : dataVector) {
		moment += std::pow(i - meanValue, degree);
	}

	*populationMoment = moment/size();
	*sampleMoment = moment/(size()-1);
}

void DataVector::computeStandardDeviation() {
	stat.standardDeviation.first.first = 
		std::sqrt(centralMoment(2, Measure::PopulationM));
	stat.standardDeviation.first.second = 
		std::sqrt(centralMoment(2, Measure::SampleM));

	stat.standardDeviation.second = true;
}

void DataVector::computeTurncatedMean(size_t k) {
	double* turncatedMean = &stat.turncatedMean[k];

	auto front = dataVector.begin();
	auto back = dataVector.end();
	std::advance(front, k);
	std::advance(back, -k);

	while (front != back) {
		*turncatedMean += *front;
		front++;
	}

	*turncatedMean /= (size() - 2*k);
}

void DataVector::computeMad() {
	std::list<double> madVector;
	double medValue = med();

	for (auto const& i : dataVector) {
		madVector.push_back(abs(i - medValue));
	}

	DataVector madDataVector(madVector);

	stat.mad.first = 1.483*madDataVector.med();

	stat.mad.second = true;
}

void DataVector::computeSkew() {
	double N = size();
	stat.skew.first.first = 
		centralMoment(3, Measure::PopulationM) /
		pow(standardDeviation(Measure::PopulationM), 3);
	stat.skew.first.second = (std::sqrt(N*(N-1))/(N-2)) * 
		stat.skew.first.first;

	stat.skew.second = true;
}

void DataVector::computeKurtosis() {
	double N = size();

	stat.kurtosis.first.first = centralMoment(4, Measure::PopulationM) / 
		pow(standardDeviation(Measure::PopulationM), 4);
	stat.kurtosis.first.second = ((std::pow(N, 2)-1)/((N-2)*(N-3))) * 
		((stat.kurtosis.first.first - 3) + 6/(N+1));

	stat.kurtosis.second = true;
}

void DataVector::computeCounterKurtosis() {
	stat.counterKurtosis.first.first = 1.0/sqrt(
			abs(kurtosis(Measure::SampleM)));
	stat.counterKurtosis.first.second = 1.0/sqrt(
			abs(kurtosis(Measure::PopulationM)));

	stat.counterKurtosis.second = true;
}

void DataVector::computeWalshAverages() {
	for (auto const& i : dataVector) {
		for (auto const& j : dataVector) {
			stat.walshAverages.first.push_back((i+j)*0.5);
		}
	}

	stat.walshAverages.second = true;
}

void DataVector::computeWalshAveragesMed() {
	DataVector walshAveragesVector(walshAverages());
	stat.walshAveragesMed.first = walshAveragesVector.med();

	stat.walshAveragesMed.second = true;
}

void DataVector::computeVariationCoef() {
	if (mean() == 0) {
		stat.variationCoef.first.first = DBL_MAX;
		stat.variationCoef.first.second = DBL_MAX;
	} else {
		stat.variationCoef.first.first = variance(Measure::PopulationM)/mean();
		stat.variationCoef.first.second = variance(Measure::SampleM)/mean();
	}

	stat.variationCoef.second = true;
}

void DataVector::computeNonparametricVariationCoef() {
	stat.nonparametricVariationCoef.first = mad()/med();
	stat.nonparametricVariationCoef.second = true;
}

void DataVector::reproduceDistribution(DistributionReproducer::Distribution type) {
	switch (type) {
		case DistributionReproducer::NormalD:
			{
				reproduction.setDistribution(type, {mean(),
						(size()/(size()-1.0))*std::sqrt(rawMoment(2) - std::pow(rawMoment(1), 2))},
						size());
				break;
			}
		case DistributionReproducer::ExponentialD:
			{
				reproduction.setDistribution(type, {1/mean()}, size());
				break;
			}
		case DistributionReproducer::WeibullD:
			{
				double a11 = size()-1;
				double a21 = 0, a22 = 0, b1 = 0, b2 = 0;
				for (auto it = dataVector.begin(); it != std::prev(dataVector.end(), 1); it++) {
					double tmp = log(*it);
					a21 += tmp;
					a22 += std::pow(tmp, 2);
					double lnValue = log(log(1/(1-eCdf(*it))));
					b1 += lnValue;
					b2 += tmp*lnValue;
				}

				double beta = (a21*b1-a11*b2)/(std::pow(a21, 2)-a11*a22);
				// (a11b2-b1a21)/(a11a22-a21^2)

				double S = 0;
				for (auto it = dataVector.begin(); it != std::prev(dataVector.end(), 1); it++) {
					S += pow(log(log(1/(1-eCdf(*it))) - skew(Measure::PopulationM)-beta*log(*it)), 2);
				}

				S /= size() - 3;

				reproduction.setDistribution(type, {exp(-skew(Measure::PopulationM)), beta,
						skew(Measure::PopulationM), S, a11, a21, a22}, size());
				break;
			}
		case DistributionReproducer::LogNormalD:
			{
				reproduction.setDistribution(type, {
					2*log(mean())-log(rawMoment(2))/2,
					sqrt(log(rawMoment(2))-2*log(mean()))
					}, size());
				break;
			}
		case DistributionReproducer::UniformD:
			{
				double pm = std::sqrt(3*(rawMoment(2) - std::pow(mean(), 2)));
				reproduction.setDistribution(type, {
						mean() - pm,
						mean() + pm
					}, size());
				break;
			}
		case DistributionReproducer::UnknownD:
			{
				reproduction.setDistribution(type, {}, size());
				break;
			}
		default:
			break;
	}
}


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

	stat.min.second = false;
	stat.max.second = false;
	stat.size.second = false;
}

QString DataVector::report() {
	return QString(
			"Мат. сподівння (v₁) %1\n"
			"Варіабельність (u₂) %2\n"
			"Медіана (MED) %3\n"
			"Усічене середнє (α=0.25) %4\n"
			"Медіана середніх Уолша (MED*) %5\n"
			"CКВ (σ) %6\n"
			"Абсолютне відхилення медіани (MAD) %7\n"
			"Коеф. асиметрії (A) %8\n"
			"Ексцесс %9\n"
			"Коефіцієнт варіації (Пірсона) (W) %10\n"
			).arg(mean())
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

void DataVector::computeBeta(int k) {
	double* betaValue = &stat.beta[k];

	if (k%2) {
		k /= 2; 
		*betaValue = (centralMoment(3, Measure::PopulationM) * 
			centralMoment(2*k+3, Measure::PopulationM)) /
			pow(centralMoment(2, Measure::PopulationM), k+3);
	} else {
		k /= 2; 
		*betaValue = centralMoment(2*k+2, Measure::PopulationM) /
			pow(centralMoment(2, Measure::PopulationM), k+1);
	}
}

void DataVector::computeMeanDeviation() {
	stat.meanDeviation.first = standardDeviation()/sqrt(size());
	stat.standardDeviation.second = true;
}

void DataVector::computeVarianceDeviation() {
	stat.varianceDeviation.first = sqrt((1.0/size()) *
			(centralMoment(4) - (size() - 3.0)/(size() - 1.0) * 
			 pow(standardDeviation(), 4)));
	stat.varianceDeviation.second = true;
}

void DataVector::computeSkewDeviation() {
	// there is no way this would ever worked
	// stat.skewDeiviation.first = sqrt(
	// 		(4*beta(4) - 12*beta(3) -
	// 		24*beta(2)+9*beta(2)*beta(1) + 35*beta(1) - 36) /
	// 		 (4*size()));
	
	stat.skewDeiviation.first = std::sqrt((6*(size()-2))/((size()+1)*(size()+3)));
	stat.skewDeiviation.second = true;
}

void DataVector::computeKurtosisDeviation() {
	stat.kurtosisDeviation.first = sqrt(
			(1.0/size())*(beta(6) - 4*beta(4)*beta(2)-8*beta(3) +
			4*pow(beta(2), 3) - pow(beta(2), 2) +
			16*beta(2)*beta(1) + 16*beta(1)));
	stat.kurtosisDeviation.second = true;
}

void DataVector::computeMeanConfidence(double alpha) {
	stat.meanConfidence[alpha] =
		Statistics::thetaDeviation(
				mean(),
				meanDeviation(),
				alpha,
				size()
			);
}

void DataVector::computeVarianceConfidence(double alpha) {
	stat.varianceConfidence[alpha] =
		Statistics::thetaDeviation(
				variance(Measure::PopulationM),
				varianceDeviation(),
				alpha,
				size()
			);
}

void DataVector::computeSkewConfidence(double alpha) {
	stat.skewConfidence[alpha] = 
		Statistics::thetaDeviation(
				skew(Measure::PopulationM),
				skewDeviation(),
				alpha,
				size()
			);
}

void DataVector::computeKurtosisConfidence(double alpha) {
	stat.kurtosisConfidence[alpha] =
		Statistics::thetaDeviation(
				kurtosis(Measure::PopulationM),
				kurtosisDeviation(),
				alpha,
				size()
			);
}

// Vector operations
void DataVector::standardize() {
	double meanValue = mean();
	double standardDeviationValue = standardDeviation(Measure::SampleM);

	for (auto& x : dataVector) {
		x = (x - meanValue)/standardDeviationValue;
	}

	clearStatistics();
}

bool DataVector::removeOutliers() {
	int popCount = 0;

	while (true) {
		double a, b,
			   t1 = 2+0.2*log10(0.04*size()),
			   t2 = sqrt(19*sqrt(kurtosis(Measure::SampleM)+2)+1);

		if (skew(Measure::SampleM) < -0.2) {
			a = mean() - t2*standardDeviation(Measure::SampleM);
			b = mean() + t1*standardDeviation(Measure::SampleM);
		} else if (skew() <= 0.2) { // skew in [-0.2;0.2]
			a = mean() - t1*standardDeviation(Measure::SampleM);
			b = mean() + t1*standardDeviation(Measure::SampleM);
		} else {
			a = mean() - t1*standardDeviation(Measure::SampleM);
			b = mean() + t2*standardDeviation(Measure::SampleM);
		}

		if (a > dataVector.front()) {
			dataVector.pop_front();
			clearStatistics();
			popCount++;
			continue;
		}

		if (b < dataVector.back()) {
			dataVector.pop_back();
			clearStatistics();
			popCount++;
			continue;
		}

		break;
	}

	if (popCount == 0) 
		return false;

	return true;
}

size_t DataVector::trim(double from, double to) {
	std::list<double> newVector;

	auto it = dataVector.begin();
	while (it != dataVector.end()) {
		if (*it >= from)
			break;
		it++;
	}

	while (it != dataVector.end()) {
		if (*it <= to)
			newVector.push_back(*(it++));
		else
			break;
	}

	size_t res = dataVector.size() - newVector.size();
	dataVector = newVector;

	clearStatistics();

	return res;
}

QString DataVector::transform(QString expression) {
	QString msg;

	exprtk::expression<double> expr;
	exprtk::parser<double> parser;
	setTransformationSymbolTable();

	double x;
	transformationSymbolTable.remove_variable("x");
	transformationSymbolTable.add_variable("x", x);

	expr.register_symbol_table(transformationSymbolTable);

	if (!parser.compile(expression.toStdString(), expr)) {
		msg.append(
				"Error computing xₙ: " + QString(parser.error().c_str()) +
				"\nExpression: '" + QString(expression.toStdString().c_str()) + "'\n");
		return msg;
	}

	for (auto& vectorValue : dataVector) {
		x = vectorValue;
		vectorValue = expr.value();
	}

	clearStatistics();

	return msg;
}

bool DataVector::writeToFile(QString filename) {
	QFile file(filename);

	if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return false;
	QTextStream stream(&file);

	for (auto const& x : dataVector) {
		stream << x << "\n";
	}

	file.close();

	return true;
}

void DataVector::setTransformationSymbolTable() {
	if (transformationSymbolTableReady)
		return;

	transformationSymbolTable.add_constant("e", M_E);
	transformationSymbolTable.add_constant("pi", M_PI);

	exprtkMean* eMean = new exprtkMean(this);
	transformationSymbolTable
		.add_function("mean", *eMean);

	exprtkMed* eMed = new exprtkMed(this);
	transformationSymbolTable
	.add_function("med", *eMed);

	exprtkMad* eMad = new exprtkMad(this);
	transformationSymbolTable
	.add_function("mad", *eMad);

	exprtkKurtosis* eKurtosis = new exprtkKurtosis(this);
	transformationSymbolTable
	.add_function("kurtosis", *eKurtosis);

	exprtkSkew* eSkew = new exprtkSkew(this);
	transformationSymbolTable
	.add_function("skew", *eSkew);

	exprtkWalshAveragesMed* eWalshAveragesMed = new exprtkWalshAveragesMed(this);
	transformationSymbolTable
	.add_function("wam", *eWalshAveragesMed);

	exprtkVariance* eVariance = new exprtkVariance(this);
	transformationSymbolTable
	.add_function("variance", *eVariance);

	exprtkXmin* eXmin = new exprtkXmin(this);
	transformationSymbolTable
	.add_function("xmin", *eXmin);

	exprtkXmax* eXmax = new exprtkXmax(this);
	transformationSymbolTable
	.add_function("xmax", *eXmax);

	exprtkVariationCoef* eVariationCoef = new exprtkVariationCoef(this);
	transformationSymbolTable
	.add_function("cv", *eVariationCoef);

	exprtkSize* eSize = new exprtkSize(this);
	transformationSymbolTable
	.add_function("size", *eSize);

	exprtkStandartDeviation* eStandartDeviation = new exprtkStandartDeviation(this);
	transformationSymbolTable
	.add_function("standartDeviation", *eStandartDeviation);

	exprtkRawMoment* eRawMoment = new exprtkRawMoment(this);
	transformationSymbolTable
	.add_function("rawMoment", *eRawMoment);

	exprtkCentralMoment* eCentralMoment = new exprtkCentralMoment(this);
	transformationSymbolTable
	.add_function("centralMoment", *eCentralMoment);

	exprtkTurncatedMean* eTurncatedMean = new exprtkTurncatedMean(this);
	transformationSymbolTable
	.add_function("turncatedMean", *eTurncatedMean);

	exprtkNormQuantile* eNormQuantile = new exprtkNormQuantile;
	transformationSymbolTable
	.add_function("normQuantile", *eNormQuantile);

	exprtkStudQuantile* eStudQuantile = new exprtkStudQuantile;
	transformationSymbolTable
	.add_function("studQuantile", *eStudQuantile);

	exprtkPearQuantile* ePearQuantile = new exprtkPearQuantile;
	transformationSymbolTable
	.add_function("pearQuantile", *ePearQuantile);

	exprtkFishQuantile* eFishQuantile = new exprtkFishQuantile;
	transformationSymbolTable
	.add_function("fishQuantile", *eFishQuantile);

	exprtkBeta* eBeta = new exprtkBeta(this);
	transformationSymbolTable
	.add_function("beta", *eBeta);

	exprtkCounterKurtosis* eCounterKurtosis = new exprtkCounterKurtosis(this);
	transformationSymbolTable
	.add_function("counterKurtosis", *eCounterKurtosis);

	exprtkNonparametricVariationCoef* eNonparametricVariationCoef =
		new exprtkNonparametricVariationCoef(this);
	transformationSymbolTable
	.add_function("nonparametricCv", *eNonparametricVariationCoef);

	exprtkNormalDistributionCdf* eNormalDistribtuionCdf =
		new exprtkNormalDistributionCdf();

	transformationSymbolTable
	.add_function("normCfd", *eNormalDistribtuionCdf);

	transformationSymbolTableReady = true;
}

const QString DataVector::exprtkFuncitons = 
		"Аргументи:\n "
		"m — тип оцінки. 'pop' – зсунена, 'spl' – не зсунена\n"
		"Функції:\n"
		"med() — медіана\n"
		"xmin() — наймешний xᵢ\n"
		"xmax() — найбільший xᵢ\n"
		"size() — розмір вектора\n"
		"variance(m) — варіабельніть\n"
		"skew(m) — коефіцієнт асиметрії\n"
		"wam() — медіана середніх Уолша\n"
		"kurtosis(m) —  коеіцієнт ексцесу\n"
		"counterKurtosis(m) —  коеіцієнт контрексцесу\n"
		"mean() — математичне сподівання\n"
		"mad() — абсолютне відхилення медіани\n"
		"cv(m) — коефіцієнт варіації (Пірсона)\n"
		"counterCv(m) — непараметричний коефіцієнт варіації\n"
		"standartDeviation(m) — середньоквадратичне відхилення\n"
		"turncatedMean(k) — усічене середнє (k ∈ (0;0.5])\n"
		"rawMoment(n) — початковий момент n-го порядку (n ∈ R)\n"
		"centralMoment(n, m) — центральний момент n-го порядку (n ∈ R)\n"
		"beta(k) — бета–коефіцієнт";
