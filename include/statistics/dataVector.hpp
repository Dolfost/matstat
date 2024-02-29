#ifndef _DATA_VECTOR_HPP_
#define _DATA_VECTOR_HPP_

#include <QtCore/qstring.h>
#include <cstddef>
#include <list>
#include <map>
#include <QDebug>
#include <cfloat>
#include "exprtk.hpp"

struct Statistics {
	std::map<double, double> rawMoment;
	std::map<double, double> centralMoment; // sample central moment
	std::map<size_t, double> turncatedMean;

	std::map<double, double> normQuantile;
	std::map<std::pair<double, int>, double> studQuantile;
	std::map<std::pair<double, int>, double> pearQuantile;
	std::map<std::tuple<double, int, int>, double> fishQuantile;

	std::map<int, double> beta; // used for statistics calculation Deviation

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
	double beta(int);

	double normQuantile(double);
	double studQuantile(double, int);
	double pearQuantile(double, int);
	double fishQuantile(double, int, int);

	std::list<double> walshAverages();

	void clearStatistics();

	QString report();
	
	// Vector operations
	void standardize();
	bool removeOutliers();
	QString transform(QString expression);

	static const QString exprtkFuncitons;

private:
	exprtk::symbol_table<double> transformationSymbolTable;
	std::list<double> dataVector;
	Statistics stat;

	bool transformationSymbolTableReady = false;
	void setTransformationSymbolTable();

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
	void computeBeta(int);

	void computeNormQuantile(double);
	void computeStudQuantile(double, int);
	void computePearQuantile(double, int);
	void computeFishQuantile(double, int, int);
};


// exprtk functions
struct exprtkMean final : public exprtk::ifunction<double> {
	exprtkMean(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->mean();
	}
};

struct exprtkMed final : public exprtk::ifunction<double> {
	exprtkMed(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->med();
	}
};

struct exprtkMad final : public exprtk::ifunction<double> {
	exprtkMad(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->mad();
	}
};

struct exprtkWalshAveragesMed final : public exprtk::ifunction<double> {
	exprtkWalshAveragesMed(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->walshAveragesMed();
	}
};

struct exprtkSize final : public exprtk::ifunction<double> {
	exprtkSize(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->size();
	}
};

struct exprtkVariationCoef final : public exprtk::ifunction<double> {
	exprtkVariationCoef(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->variationCoef();
	}
};

struct exprtkKurtosis final : public exprtk::ifunction<double> {
	 exprtkKurtosis(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->kurtosis();
	}
};

struct exprtkSkew final : public exprtk::ifunction<double> {
	 exprtkSkew(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->skew();
	}
};

struct exprtkVariance final : public exprtk::ifunction<double> {
	exprtkVariance(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->variance();
	}
};

struct exprtkXmin final : public exprtk::ifunction<double> {
	exprtkXmin(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->min();
	}
};

struct exprtkXmax final : public exprtk::ifunction<double> {
	exprtkXmax(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->max();
	}
};

struct exprtkStandartDeviation final : public exprtk::ifunction<double> {
	exprtkStandartDeviation(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->standardDeviation();
	}
};

struct exprtkRawMoment final : public exprtk::ifunction<double> {
	exprtkRawMoment(DataVector* vec) : exprtk::ifunction<double>(1)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(const double& degree) {
		return dv->rawMoment(degree);
	}
};

struct exprtkCentralMoment final : public exprtk::ifunction<double> {
	exprtkCentralMoment(DataVector* vec) : exprtk::ifunction<double>(1)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(const double& degree) {
		return dv->centralMoment(degree);
	}
};

struct exprtkTurncatedMean final : public exprtk::ifunction<double> {
	exprtkTurncatedMean(DataVector* vec) : exprtk::ifunction<double>(1)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(const double& k) {
		return dv->turncatedMean(k);
	}
};

struct exprtkNormQuantile final : public exprtk::ifunction<double> {
	exprtkNormQuantile(DataVector* vec) : exprtk::ifunction<double>(1)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(const double& alpha) {
		return dv->normQuantile(alpha);
	}
};

struct exprtkStudQuantile final : public exprtk::ifunction<double> {
	exprtkStudQuantile(DataVector* vec) : exprtk::ifunction<double>(2)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(const double& alpha, const double& v) {
		return dv->studQuantile(alpha, v);
	}
};

struct exprtkPearQuantile final : public exprtk::ifunction<double> {
	exprtkPearQuantile(DataVector* vec) : exprtk::ifunction<double>(2)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(const double& alpha, const double& v) {
		return dv->pearQuantile(alpha, v);
	}
};

struct exprtkFishQuantile final : public exprtk::ifunction<double> {
	exprtkFishQuantile(DataVector* vec) : exprtk::ifunction<double>(3)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(const double& alpha, const double& v1, const double& v2) {
		return dv->fishQuantile(alpha, v1, v2);
	}
};

struct exprtkBeta final : public exprtk::ifunction<double> {
	exprtkBeta(DataVector* vec) : exprtk::ifunction<double>(1)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(const double& k) {
		return dv->beta(k);
	}
};

#endif // !_DATA_VECTOR_HPP_
