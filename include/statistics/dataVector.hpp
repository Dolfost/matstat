#ifndef _DATA_VECTOR_HPP_
#define _DATA_VECTOR_HPP_

#include <QString>
#include <map>
#include <list>

#include <cstddef>
#include <list>
#include <map>
#include <QDebug>
#include <QFile>
#include "exprtk.hpp"

struct Statistics {
	// population/sample statistics map has the format
	// std::map<degree, std::pair<population, sample>>

	std::map<double, double> rawMoment; 
	// population/sample central moment
	std::map<double, std::pair<double, double>> centralMoment;
	std::map<size_t, double> turncatedMean;

	std::map<int, double> beta; // used for statistics Deviation calculation 

	std::pair<std::pair<double, double>, bool> 
		standardDeviation{{0, 0}, false}; // population/sample variance
	std::pair<double, bool>
		mad{0, false}; // median absolute deviation
	std::pair<std::pair<double, double>, bool>
		skew{{0,0}, false}; // population/sample asymetry coef
	std::pair<std::pair<double, double>, bool>
		kurtosis{{0,0}, false}; // population/sample kurtosis excess coef
	std::pair<std::pair<double, double>, bool>
		counterKurtosis{{0,0}, false};
	std::pair<double, bool>
		walshAveragesMed{0, false}; // Walsh averages median
	std::pair<std::pair<double, double>, bool> 
		variationCoef{{0,0}, false}; // (Pearson) coefficient of variation
	std::pair<double, bool> 
		nonparametricVariationCoef{0, false};

	std::pair<double, bool> meanDeviation{0, false};
	std::pair<double, bool> varianceDeviation{0, false};
	std::pair<double, bool> kurtosisDeviation{0, false};
	std::pair<double, bool> skewDeiviation{0, false};

	std::map<double, std::pair<double, double>> meanConfidence;
	std::map<double, std::pair<double, double>> varianceConfidence;
	std::map<double, std::pair<double, double>> kurtosisConfidence;
	std::map<double, std::pair<double, double>> skewConfidence;

	std::pair<std::list<double>, bool> walshAverages{{}, false};

	std::pair<double, bool> min{0, false};
	std::pair<double, bool> max{0, false};
	std::pair<size_t, bool> size{0, false};
};

struct Dist {
	Dist();

	double x = 0;
	exprtk::symbol_table<double> symbolTable;
	exprtk::expression<double> pdfExpression; // probability density function
	exprtk::expression<double> cdfExpression; // cummulative density function
	exprtk::expression<double> cdfDeviationExpression;
	
	size_t parameterCount = 0;
	std::vector<QString> paremeterName;
	std::vector<double> parameter{0};
	std::vector<double> parameterDeviation{0};
	double parameterCv = 0;
	double pdfMax = 0;
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
		UnknownM,
		PopulationM,
		SampleM
	};
	enum Limit {
		UnknownL,
		LowerL,
		UpperL 
	};
	double mean();
	double variance(Measure = SampleM);
	double med();
	double mad();
	double skew(Measure = SampleM);
	double kurtosis(Measure = SampleM);
	double counterKurtosis(Measure = SampleM);
	double walshAveragesMed();
	double variationCoef(Measure = SampleM);
	double nonparametricVariationCoef();

	double meanDeviation();
	double varianceDeviation();
	double skewDeviation();
	double kurtosisDeviation();

	double meanConfidence(double, Limit);
	double varianceConfidence(double, Limit);
	double skewConfidence(double, Limit);
	double kurtosisConfidence(double, Limit);

	double rawMoment(double degree);
	double centralMoment(double degree, Measure = SampleM);
	double standardDeviation(Measure = SampleM);
	double turncatedMean(double degree);
	double beta(int);

	static double normQuantile(double);
	static double studQuantile(double, int);
	static double pearQuantile(double, int);
	static double fishQuantile(double, int, int);

	static double normalDistributionCdf(double);

	std::list<double> walshAverages();

	void clearStatistics();

	QString report();
	
	// Vector operations
	void standardize();
	bool removeOutliers();
	size_t trim(double, double);
	QString transform(QString);

	bool writeToFile(QString);

	static const QString exprtkFuncitons;

	// distribution recreation
	enum Distribution {
		UnknownD,
		NormalD,
		ExponentialD,
		WeibullD,
		LogNormalD,
	};

	Dist distributionData;
	void setDistribution(Distribution);
	Distribution distribution();


private:
	exprtk::symbol_table<double> transformationSymbolTable;
	std::list<double> dataVector;
	Statistics stat;

	bool transformationSymbolTableReady = false;
	void setTransformationSymbolTable();

	Distribution distributionType = UnknownD;

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
	void computeCounterKurtosis();
	void computeVariationCoef();
	void computeNonparametricVariationCoef();
	void computeBeta(int k);

	void computeMeanDeviation();
	void computeVarianceDeviation();
	void computeSkewDeviation();
	void computeKurtosisDeviation();

	void computeMeanConfidence(double);
	void computeVarianceConfidence(double);
	void computeSkewConfidence(double);
	void computeKurtosisConfidence(double);
};



#endif // !_DATA_VECTOR_HPP_
