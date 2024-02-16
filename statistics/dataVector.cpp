#include "dataVector.hpp"
#include <QDebug>
#include <cfloat>
#include <cmath>
#include <iterator>

DataVector::DataVector(std::list<double> input) {
	dataVector = input;
	dataVector.sort();
}

std::list<double> DataVector::vector() {
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

double DataVector::variance() {
	return centralMoment(2);
}

double DataVector::standardDeviation() {
	if (!stat.standardDeviation.second)
		computeStandardDeviation();
	return stat.standardDeviation.first;
}

double DataVector::rawMoment(double degree) {
	if (stat.rawMoment.count(degree) != 1)
		computeRawMoment(degree);

	return stat.rawMoment[degree];
}

double DataVector::centralMoment(double degree) {
	if (stat.centralMoment.count(degree) != 1)
		computeCentralMoment(degree);

	return stat.centralMoment[degree];
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

double DataVector::skew() {
	if (!stat.skew.second)
		computeSkew();

	return stat.skew.first;
}

double DataVector::kurtosis() {
	if (!stat.kurtosis.second)
		computeKurtosis();

	return stat.kurtosis.first;
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

double DataVector::variationCoef() {
	if (!stat.variationCoef.second)
		computeVariationCoef();

	return stat.variationCoef.first;
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
	double* moment = &stat.centralMoment[degree];
	double meanValue = mean();

	for (auto const& i : dataVector) {
		*moment += std::pow(i - meanValue, degree);
	}

	*moment /= (size() - 1);
}

void DataVector::computeStandardDeviation() {
	stat.standardDeviation.first = std::sqrt(centralMoment(2));
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
		madVector.push_back(i - medValue);
	}

	DataVector madDataVector(madVector);

	stat.mad.first = madDataVector.med();
	stat.mad.second = true;
}

void DataVector::computeSkew() {
	double N = size();

	stat.skew.first = (std::sqrt(N*(N-1))*centralMoment(3)) / 
		(rawMoment(3)*(N-2));
	stat.skew.second = true;
}

void DataVector::computeKurtosis() {
	double N = size();

	stat.kurtosis.first = ((std::pow(N, 2)-1)/((N-2)*(N-3))) * 
		((centralMoment(4)/rawMoment(4) - 3) + 6/(N+1));
	stat.kurtosis.second = true;
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
	if (mean() == 0)
		stat.variationCoef.first = DBL_MAX;
	else
		stat.variationCoef.first = variance()/mean();

	stat.variationCoef.second = true;
}

void DataVector::clearStatistics() {
	stat.rawMoment.clear();
	stat.centralMoment.clear();
	stat.turncatedMean.clear();
	stat.walshAverages.first.clear();

	stat.standardDeviation.second = false;
	stat.mad.second = false;
	stat.skew.second = false;
	stat.kurtosis.second = false;
	stat.variationCoef.second = false;
	stat.walshAverages.second = false;
	stat.walshAveragesMed.second = false;

	stat.min.second = false;
	stat.max.second = false;
	stat.size.second = false;
}


// Vector operations
void DataVector::standardize() {
	double meanValue = mean();
	double standardDeviationValue = standardDeviation();

	for (auto& x : dataVector) {
		x = (x - meanValue)/standardDeviationValue;
	}

	clearStatistics();
}

void DataVector::transform(QString expression) {

}
