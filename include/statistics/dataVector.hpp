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
	// population/sample statistics map has the format
	// std::map<degree, std::pair<population, sample>>

	std::map<double, double> rawMoment; 
	// population/sample central moment
	std::map<double, std::pair<double, double>> centralMoment;
	std::map<size_t, double> turncatedMean;

	std::map<double, double> normQuantile;
	std::map<std::pair<double, int>, double> studQuantile;
	std::map<std::pair<double, int>, double> pearQuantile;
	std::map<std::tuple<double, int, int>, double> fishQuantile;

	std::map<int, double> beta; // used for statistics Deviation calculation 

	std::pair<std::pair<double, double>, bool> 
		standardDeviation{{0, 0}, false}; // population/sample variance
	std::pair<double, bool>
		mad{0, false}; // median absolute deviation
	std::pair<std::pair<double, double>, bool>
		skew{{0,0}, false}; // population/sample asymetry coef
	std::pair<std::pair<double, double>, bool>
		kurtosis{{0,0}, false}; // population/sample kurtosis excess coef
	std::pair<double, bool>
		walshAveragesMed{0, false}; // Walsh averages median
	std::pair<std::pair<double, double>, bool> 
		variationCoef{{0,0}, false}; // (Pearson) coefficient of variation

	std::pair<double, bool> meanDeviation{0, false};
	std::pair<double, bool> varianceDeviation{0, false};
	std::pair<double, bool> kurtosisDeviation{0, false};
	std::pair<double, bool> skewDeiviation{0, false};

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

	// Statistics measures
	enum Measure {
		Unknown,
		Population,
		Sample
	};
	double mean();
	double variance(Measure = Sample);
	double med();
	double mad();
	double skew(Measure = Sample);
	double kurtosis(Measure = Sample);
	double walshAveragesMed();
	double variationCoef(Measure = Sample);

	double meanDeviation();
	double varianceDeviation();
	double skewDeviation();
	double kurtosisDeviation();

	double rawMoment(double degree);
	double centralMoment(double degree, Measure = Sample);
	double standardDeviation(Measure = Sample);
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
	void computeBeta(int k);

	void computeMeanDeviation();
	void computeVarianceDeviation();
	void computeSkewDeviation();
	void computeKurtosisDeviation();

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

struct exprtkVariationCoef final : public exprtk::igeneric_function<double> {
	exprtkVariationCoef(DataVector* vec) : exprtk::igeneric_function<double>("S")  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[0]);
		std::string mstr = m.begin();
		DataVector::Measure measure;
		if (mstr == "pop")
			measure = DataVector::Measure::Population;
		else if (mstr == "spl")
			measure = DataVector::Measure::Sample;
		else 
			measure = DataVector::Measure::Unknown;
return dv->variationCoef(measure);
	}
};

struct exprtkKurtosis final : public exprtk::igeneric_function<double> {
	exprtkKurtosis(DataVector* vec) : exprtk::igeneric_function<double>("S")  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[0]);
		std::string mstr = m.begin();
		DataVector::Measure measure;
		if (mstr == "pop")
			measure = DataVector::Measure::Population;
		else if (mstr == "spl")
			measure = DataVector::Measure::Sample;
		else 
			measure = DataVector::Measure::Unknown;

		return dv->kurtosis(measure);
	}
};

struct exprtkSkew final : public exprtk::igeneric_function<double> {
	exprtkSkew(DataVector* vec) : exprtk::igeneric_function<double>("S")  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[0]);
		std::string mstr = m.begin();
		DataVector::Measure measure;
		if (mstr == "pop")
			measure = DataVector::Measure::Population;
		else if (mstr == "spl")
			measure = DataVector::Measure::Sample;
		else 
			measure = DataVector::Measure::Unknown;

		return dv->skew(measure);
	}
};

struct exprtkVariance final : public exprtk::igeneric_function<double> {
	exprtkVariance(DataVector* vec) : exprtk::igeneric_function<double>("S")  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[0]);
		std::string mstr = m.begin();
		DataVector::Measure measure;
		if (mstr == "pop")
			measure = DataVector::Measure::Population;
		else if (mstr == "spl")
			measure = DataVector::Measure::Sample;
		else 
			measure = DataVector::Measure::Unknown;

		return dv->variance(measure);
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

struct exprtkStandartDeviation final : public exprtk::igeneric_function<double> {
	exprtkStandartDeviation(DataVector* vec) : exprtk::igeneric_function<double>("S")  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[0]);
		std::string mstr = m.begin();
		DataVector::Measure measure;
		if (mstr == "pop")
			measure = DataVector::Measure::Population;
		else if (mstr == "spl")
			measure = DataVector::Measure::Sample;
		else 
			measure = DataVector::Measure::Unknown;

		return dv->standardDeviation(measure);
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

struct exprtkCentralMoment final : public exprtk::igeneric_function<double> {
	exprtkCentralMoment(DataVector* vec) : exprtk::igeneric_function<double>("TS")  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::scalar_view scalar_t;
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[1]);
		std::string mstr = m.begin();
		DataVector::Measure measure;
		if (mstr == "pop")
			measure = DataVector::Measure::Population;
		else if (mstr == "spl")
			measure = DataVector::Measure::Sample;
		else 
			measure = DataVector::Measure::Unknown;

		return dv->centralMoment(scalar_t(parameters[0]), measure);
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
