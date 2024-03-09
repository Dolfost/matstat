#include "dataVector.hpp"
#include <QtCore/qlogging.h>
#include <QtCore/qnumeric.h>
#include <cmath>

#include "dataVectorExprtk.hpp"
#include <cfloat>

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
	setDistribution(Distribution::ExponentialD);
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

double DataVector::normQuantile(double alpha) {
	double quantile = 0;

	const double 
		c0 = 2.515517,
		c1 = 0.802853,
		c2 = 0.010328,
		d1 = 1.432788,
		d2 = 0.1892659,
		d3 = 0.001308,
		t = sqrt(log(1/(alpha*alpha))),
		ea = 4.5e-4;

	quantile = t - (c0 + c1*t + c2*t*t) /
		(1 + d1*t+d2*t*t + d3*t*t*t) + ea;
	
	return quantile;
}

double DataVector::pearQuantile(double alpha, int v) {
	double quantile = 0;

	quantile = v*pow(1 - 2.0/(9*v) + normQuantile(alpha)*sqrt(2.0/(9*v)), 3);
	
	return quantile;
}

double DataVector::studQuantile(double alpha, int v) {
	double quantile = 0;

	const double
		nq = normQuantile(alpha),
		nq2 = nq*nq,
		nq3 = nq2*nq,
		nq5 = nq3*nq2,
		nq7 = nq5*nq2,
		nq9 = nq7*nq2,
		g1 = (nq3+ nq)/4,
		g2 = (5*nq5 + 16*nq3 + 3*nq)/96,
		g3 = (3*nq7 + 19*nq5 + 17*nq3 - 15*nq)/384,
		g4 = (79*nq9 + 779*nq7 + 1482*nq5 - 1920*nq3 - 945*nq)/92160;

	quantile = nq + g1/v + g2/pow(v, 2) + g3/pow(v, 3) + g4/pow(v, 4);

	return quantile;
}

double DataVector::fishQuantile(double alpha, int v1, int v2) {
	double quantile = 0;

	const double
		sigma = 1.0/v1 + 1.0/v2,
		delta = 1.0/v1 - 1.0/v2,
		sigmaSqrtBy2 = sqrt(sigma/2),
		nq = normQuantile(alpha),
		nq2 = nq*nq,
		nq3 = nq2*nq,
		nq4 = nq3*nq4,
		nq5 = nq4*nq,
		z = nq*sigmaSqrtBy2 - delta*(nq*nq+2)/6 + 
			sigmaSqrtBy2*((sigma*(nq2 + 3*nq)/24 + 
			(pow(delta, 2)*(nq3 +11*nq))/(72*sigma))) -
			(delta*sigma*(nq4+9*nq2+8))/120 +
			(pow(delta, 3)*(3*nq4 + 7*nq2 - 16))/(3240*sigma) +
			sigmaSqrtBy2*(pow(sigma, 2)*(nq5 + 20*nq3 +15*nq)/1920 + 
			pow(delta, 4)*(nq5 + 44*nq3 + 183*nq)/2880 + 
			pow(delta, 4)*(9*nq5 - 284*nq3 - 1513*nq)/(155520 * pow(sigma, 2)));

	quantile = exp(2*z);

	return quantile;
}

double DataVector::normalDistributionCdf(double u) {
	double x = abs(u);
	double 
		p = 0.2316419,
		b1 = 0.31938153,
		b2 = -0.356563782,
		b3 = 1.781477937,
		b4 = -1.821255978,
		b5 = 1.330274429,
		t1 = 1/(1+p*x),
		t2 = t1*t1,
		t3 = t2*t1,
		t4 = t3*t1,
		t5 = t4*t1;

	double f = 1-0.3989422804*std::exp(-(std::pow(x, 2))/2) * 
		(b1*t1 + b2*t2 + b3*t3 + b4*t4 + b5*t5);

	if (u < 0)
		f = 1 - f;

	return f;
}

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
	qDebug() << "WHY THIS HAPPENS" << 
		(1.0/(4*size())) *(4*beta(4) - 12*beta(3) -
			24*beta(2)+9*beta(2)*beta(1) + 35*beta(1) - 36);
	stat.skewDeiviation.first = sqrt(
			(4*beta(4) - 12*beta(3) -
			24*beta(2)+9*beta(2)*beta(1) + 35*beta(1) - 36) /
			 (4*size()));
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
	double* lower = &stat.meanConfidence[alpha].first;
	double* upper = &stat.meanConfidence[alpha].second;

	if (size() > 60) {
		double quantile = normQuantile(1-alpha/2);
		*lower = mean() - quantile *
			meanDeviation();
		*upper = mean() + quantile *
			meanDeviation();
	} else {
		double quantile = studQuantile(1-alpha/2, size()-1);
		*lower = mean() - quantile *
			meanDeviation();
		*upper = mean() + quantile *
			meanDeviation();
	}
}

void DataVector::computeVarianceConfidence(double alpha) {
	double* lower = &stat.varianceConfidence[alpha].first;
	double* upper = &stat.varianceConfidence[alpha].second;

	if (size() > 60) {
		double quantile = normQuantile(1-alpha/2);
		*lower = variance(Measure::PopulationM) -
			quantile*varianceDeviation();
		*upper = variance(Measure::PopulationM) +
			quantile*varianceDeviation();
	} else {
		double quantile = studQuantile(1-alpha/2, size()-1);
		*lower = variance(Measure::PopulationM) - 
			quantile *
			varianceDeviation();
		*upper = variance(Measure::PopulationM) +
			quantile *
			varianceDeviation();
	}
}

void DataVector::computeSkewConfidence(double alpha) {
	double* lower = &stat.skewConfidence[alpha].first;
	double* upper = &stat.skewConfidence[alpha].second;

	if (size() > 60) {
		double quantile = normQuantile(1-alpha/2);
		*lower = skew(Measure::PopulationM) -
			quantile*skewDeviation();
		*upper = skew(Measure::PopulationM) +
			quantile * skewDeviation();
	} else {
		double quantile = studQuantile(1-alpha/2, size()-1);
		*lower = skew(Measure::PopulationM) - 
			quantile * skewDeviation();
		*upper = skew(Measure::PopulationM) +
			quantile * skewDeviation();
	}
}

void DataVector::computeKurtosisConfidence(double alpha) {
	double* lower = &stat.kurtosisConfidence[alpha].first;
	double* upper = &stat.kurtosisConfidence[alpha].second;

	if (size() > 60) {
		double quantile = normQuantile(1-alpha/2);
		*lower = kurtosis(Measure::PopulationM) -
			quantile * meanDeviation();
		*upper = kurtosis(Measure::PopulationM) +
			quantile * meanDeviation();
	} else {
		double quantile = studQuantile(1-alpha/2, size()-1);
		*lower = kurtosis(Measure::PopulationM) - 
			quantile * kurtosisDeviation();
		*upper = kurtosis(Measure::PopulationM) +
			quantile * kurtosisDeviation();
	}
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

	if (a < dataVector.front() and b > dataVector.back()) 
		return false;

	while (a > dataVector.front()) {
		dataVector.pop_front();
		clearStatistics();

		if (skew(Measure::SampleM) < -0.2) {
			t2 = sqrt(19*sqrt(kurtosis(Measure::SampleM)+2)+1);
			a = mean() - t2*standardDeviation(Measure::SampleM);
		} else if (skew() <= 0.2) { // skew in [-0.2;0.2]
			t1 = 2+0.2*log10(0.04*size());
			a = mean() - t1*standardDeviation(Measure::SampleM);
		} else {
			t1 = 2+0.2*log10(0.04*size());
			a = mean() - t1*standardDeviation(Measure::SampleM);
		}
	}

	while (b < dataVector.back()) {
		dataVector.pop_back();
		clearStatistics();

		if (skew(Measure::SampleM) < -0.2) {
			t1 = 2+0.2*log10(0.04*size());
			b = mean() + t1*standardDeviation(Measure::SampleM);
		} else if (skew() <= 0.2) { // skew in [-0.2;0.2]
			t1 = 2+0.2*log10(0.04*size());
			b = mean() + t1*standardDeviation(Measure::SampleM);
		} else {
			t2 = sqrt(19*sqrt(kurtosis(Measure::SampleM)+2)+1);
			b = mean() + t2*standardDeviation(Measure::SampleM);
		}
	}

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

void DataVector::setDistribution(Distribution type) {
	distributionType = type;

	exprtk::parser<double> parser;
	distributionData.paremeterName.clear();
	distributionData.parameter.clear();
	distributionData.parameterDeviation.clear();

	switch (type) {
		case Distribution::NormalD:
			{
				distributionData.parameterCount = 2;
				distributionData.paremeterName = {
					"m", "σ"
				};
				distributionData.parameter = {
					mean(),
					standardDeviation(),
				};
				distributionData.pdfMax = 1/(standardDeviation()*2.5066282746);
				distributionData.parameterDeviation.push_back(
						std::pow(distributionData.parameter[1], 2)/size());
				distributionData.parameterDeviation.push_back(distributionData.parameter[0]/2);

				QString pdf = QString(
						"1/(%2*2.5066282746)*exp(-((x-%1)^2)/(2*(%2)^2))")
					.arg(distributionData.parameter[0])
					.arg(distributionData.parameter[1]);
				parser.compile(pdf.toStdString(), distributionData.pdfExpression);

				QString cdf = QString(
						"normCdf((x-(%1))/(%2))")
					.arg(distributionData.parameter[0])
					.arg(distributionData.parameter[1]);
				parser.compile(cdf.toStdString(), distributionData.cdfExpression);

				QString cdfDeviation = QString(
						"(%1)^2*(%3)+(%2)^2*(%4) + 2*(%1)(%2)(%5)")
					.arg(QString("-1/(%2*2.5066282746)*exp(-((x-%1)^2)/(2(%2)^2))")
							.arg(distributionData.parameter[0])
							.arg(distributionData.parameter[1])
						)
					.arg(QString("-(x-%1)/((%2)^2*2.5066282746)*exp(-((x-%1)^2)/(2(%2)^2))")
							.arg(distributionData.parameter[0])
							.arg(distributionData.parameter[1])
						)
					.arg(distributionData.parameter[0])
					.arg(distributionData.parameter[1])
					.arg(distributionData.parameterCv);
				distributionData.parameterCv = 0;
				break;
			}
		case Distribution::ExponentialD:
			{
				distributionData.parameterCount = 1;
				distributionData.paremeterName = {
					"λ",
				};
				distributionData.parameter = {
					1/mean(),
				};
				distributionData.pdfMax = distributionData.parameter[0];
				distributionData.parameterDeviation.push_back(
						std::pow(distributionData.parameter[0], 2)/2);

				QString pdf = QString(
						"(%1)(exp(-(%1)x))")
					.arg(distributionData.parameter[0], 0, 'f', 6);
				parser.compile(pdf.toStdString(), distributionData.pdfExpression);

				QString cdf = QString(
						"1-exp(-(%1)x)")
					.arg(distributionData.parameter[0]);
				parser.compile(cdf.toStdString(), distributionData.cdfExpression);

				QString cdfDeviation = QString(
						"x^2*exp(-2(%1)x)%2")
					.arg(distributionData.parameter[0])
					.arg(distributionData.parameterDeviation[0]);
				distributionData.parameterCv = 0;
				break;
			}
	}
}

DataVector::Distribution DataVector::distribution() {
	return distributionType;
}

Dist::Dist() {
	symbolTable.add_variable("x", x);
	auto* eNormalDistributionCdf = new exprtkNormalDistributionCdf();
	symbolTable.add_function("normCdf", *eNormalDistributionCdf);
	cdfExpression.register_symbol_table(symbolTable);
	pdfExpression.register_symbol_table(symbolTable);
	cdfDeviationExpression.register_symbol_table(symbolTable);
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

	exprtkNormQuantile* eNormQuantile = new exprtkNormQuantile(this);
	transformationSymbolTable
	.add_function("normQuantile", *eNormQuantile);

	exprtkStudQuantile* eStudQuantile = new exprtkStudQuantile(this);
	transformationSymbolTable
	.add_function("studQuantile", *eStudQuantile);

	exprtkPearQuantile* ePearQuantile = new exprtkPearQuantile(this);
	transformationSymbolTable
	.add_function("pearQuantile", *ePearQuantile);

	exprtkFishQuantile* eFishQuantile = new exprtkFishQuantile(this);
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
		"normQuantile(a) — квантиль нормального розподілу\n"
		"studQuantile(a,v) — квантиль розподілу Стьюдента\n"
		"pearQuantile(a,v) — квантиль розподілу Пірсона\n"
		"fishQuantile(a,v1,v2) — квантиль розподілу Фішера\n"
		"normCdf(u) — функція розподілу нормованого нормального розподілу\n"
		"beta(k) — бета–коефіцієнт";
