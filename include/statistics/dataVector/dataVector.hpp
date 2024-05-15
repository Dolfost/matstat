#ifndef _DATA_VECTOR_HPP_
#define _DATA_VECTOR_HPP_

#include <QString>
#include <QDebug>
#include <QFile>

#include <cstddef>
#include <list>
#include <map>

#include "exprtk.hpp"

#include "distributionReproducer.hpp"

class DataVector {
public:
	struct Stats {
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
		std::pair<std::pair<double, double>, bool>
			reproductionDeviation{{0,0}, false};

		std::pair<double, bool> kolmConsentCriterion{0, false};
		std::pair<double, bool> pearConsentCriterion{0, false};

		std::map<double, std::pair<double, double>> meanConfidence;
		std::map<double, std::pair<double, double>> varianceConfidence;
		std::map<double, std::pair<double, double>> kurtosisConfidence;
		std::map<double, std::pair<double, double>> skewConfidence;

		std::pair<std::list<double>, bool> walshAverages{{}, false};

		std::pair<double, bool> min{0, false};
		std::pair<double, bool> max{0, false};
		std::pair<size_t, bool> size{0, false};
	};

	class ClassSeries;
	class VarSeries;

	enum Measure { // statistics measure
		UnknownM,
		PopulationM, // зсунута оцінка
		SampleM // не зсунута оцінка
	};
	enum Limit { // limits declaration
		UnknownL,
		LowerL,
		UpperL 
	};

public:
	DataVector(const std::list<double>& = {});
	DataVector(DataVector&);
	void setVector(const std::list<double>&);
	const std::list<double>& vector();
	const std::list<double>& timeVector();
	~DataVector();

public: // statistics
	size_t size();
	double min();
	double max();
	
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

	std::list<double>& walshAverages();

public: // vector operations
	void standardize();
	bool removeOutliers();
	size_t trim(double, double);
	QString transform(QString);

	bool writeToFile(QString);

public: // distribution recreation
	double cdf(double);

	DistributionReproducer rep;
	bool reproduceDistribution(DistributionReproducer::Distribution);
	double kolmConsentCriterion();
	double pearConsentCriterion();

	void makeClassSeries(unsigned short = 0);
	ClassSeries* classSeries();
	VarSeries* varSeries();

public: // general
	QString report();
	void clearStatistics();
	static const QString exprtkFuncitons;

private: // data
	std::list<double> dataVector;
	std::list<double> timeSeries;
	Stats stat;
	ClassSeries* cs;
	VarSeries* vs;
	bool csReady = false;
	bool vsReady = false;

	bool transformationSymbolTableReady = false;
	exprtk::symbol_table<double> transformationSymbolTable;
	void setTransformationSymbolTable();

private:
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

	void computeKolmConsentCriterion();
	void computePearConsentCriterion();
};

#endif // !_DATA_VECTOR_HPP_
