#ifndef _DATA_VECTOR_HPP_
#define _DATA_VECTOR_HPP_

#include <QtCore/qstring.h>
#include <cstddef>
#include <list>
#include <map>

struct Statistics {
	std::map<double, double> rawMoment;
	std::map<double, double> centralMoment; // sample central moment
	std::map<size_t, double> turncatedMean;

	std::pair<double, bool> standardDeviation{0, false}; // sample variance
	std::pair<double, bool> mad{0, false}; // median absolute deviation
	std::pair<double, bool> skew{0, false}; // sample asymetry coef
	std::pair<double, bool> kurtosis{0, false}; // sample excess kurtosis
	std::pair<double, bool> walshAveragesMed{0, false};
	std::pair<double, bool> variationCoef{0, false}; // (Pearson) coefficient of variation
	std::pair<std::list<double>, bool> walshAverages{{}, false};

	std::pair<double, bool> min{0, false};
	std::pair<double, bool> max{0, false};
	std::pair<size_t, bool> size{0, false};
};

class DataVector {
public:
	DataVector(const std::list<double>& = {});
	DataVector(DataVector&);
	void setVector(const std::list<double>&);

	const std::list<double>& vector();

	size_t size();
	double min();
	double max();

	// Statistics
	double mean();
	double variance();
	double med();
	double mad();
	double skew();
	double kurtosis();
	double walshAveragesMed();
	double variationCoef();

	double rawMoment(double degree);
	double centralMoment(double degree);
	double standardDeviation();
	double turncatedMean(double degree);

	std::list<double> walshAverages();

	void clearStatistics();

	QString report();
	
	// Vector operations
	void standardize();
	void transform(QString expression);

private:
	std::list<double> dataVector;
	Statistics stat;

	// Statistics computers
	void computeMinMaxSize();

	void computeRawMoment(double degree);
	void computeCentralMoment(double degree);
	void computeStandardDeviation();
	void computeTurncatedMean(size_t k);
	void computeWalshAverages();
	void computeWalshAveragesMed();
	void computeMad();
	void computeSkew();
	void computeKurtosis();
	void computeVariationCoef();
};

#endif // !_DATA_VECTOR_HPP_
