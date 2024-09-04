#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <QString>
#include <QDebug>
#include <QFile>

#include <QtPrintSupport/qprinter.h>
#include <cstddef>
#include <list>

#include "distributionReproducer.hpp"

#include"utils.hpp"

namespace ss {

class RawMoment: public utils::StatisticMap<double, double> {
public:
	using StatisticMap::StatisticMap;
protected:
	virtual void adapt(double degree) override;
};

class MeanDeviation: public utils::StatisticSingle<double> {
public:
	using StatisticSingle::StatisticSingle;
protected:
	virtual void adapt() override;
};

class MeanConfidence: public utils::Confidence<double, double> {
public:
	using Confidence::Confidence;
protected:
	virtual void adapt(double) override;
};

class CentralMoment: public utils::StatisticPairMap<double, double, Measure> {
public:
	using StatisticPairMap::StatisticPairMap;
protected:
	virtual void adapt(double degre) override;
};

class VarianceDeviation: public utils::StatisticSingle<double> {
public:
	using StatisticSingle::StatisticSingle;
protected:
	virtual void adapt() override;
};

class VarianceConfidence: public utils::Confidence<double, double> {
public:
	using Confidence::Confidence;
protected:
	virtual void adapt(double) override;
};

class Skew: public utils::StatisticPair<double, Measure> {
public:
	using StatisticPair::StatisticPair;
protected:
	virtual void adapt() override;
};

class SkewDeviation: public utils::StatisticSingle<double> {
public:
	using StatisticSingle::StatisticSingle;
protected:
	virtual void adapt() override;
};

class SkewConfidence: public utils::Confidence<double, double> {
public:
	using Confidence::Confidence;
protected:
	virtual void adapt(double) override;
};

class Kurtosis: public utils::StatisticPair<double, Measure> {
public:
	using StatisticPair::StatisticPair;
protected:
	virtual void adapt() override;
};

class KurtosisDeviation: public utils::StatisticSingle<double> {
public:
	using StatisticSingle::StatisticSingle;
protected:
	virtual void adapt() override;
};

class KurtosisConfidence: public utils::Confidence<double, double> {
public:
	using Confidence::Confidence;
protected:
	virtual void adapt(double) override;
};

class MeanAbsoluteDeviation: public utils::StatisticSingle<double> {
public:
	using StatisticSingle::StatisticSingle;
protected:
	virtual void adapt() override;
};

class TurncatedMean: public utils::StatisticMap<double, double, std::size_t> {
public:
	using StatisticMap::StatisticMap;
	virtual double value(double) override;
protected:
	virtual void adapt(std::size_t) override;
};

class CounterKurtosis: public utils::StatisticPair<double, Measure> {
public:
	using StatisticPair::StatisticPair;
protected:
	virtual void adapt() override;
};

class StandardDeviation: public utils::StatisticPair<double, Measure> {
public:
	using StatisticPair::StatisticPair;
protected:
	virtual void adapt() override;
};

class Beta: public utils::StatisticMap<std::size_t, double> {
public:
	using StatisticMap::StatisticMap;
protected:
	virtual void adapt(std::size_t) override;
};

class WalshAverages: public utils::StatisticSingle<std::vector<double>> {
public:
	using StatisticSingle::StatisticSingle;
	virtual void invalidate() override;
protected:
	virtual void adapt() override;
};

class WalshAveragesMedian: public utils::StatisticSingle<double> {
public:
	using StatisticSingle::StatisticSingle;
protected:
	virtual void adapt() override;
};

class KolmConsentCriterion: public utils::StatisticSingle<double> {
public:
	using StatisticSingle::StatisticSingle;
protected:
	virtual void adapt() override;
};

class PearConsentCriterion: public utils::StatisticSingle<double> {
public:
	using StatisticSingle::StatisticSingle;
protected:
	virtual void adapt() override;
};

class CoefficientOfVariation: public utils::StatisticPair<double, Measure> {
public:
	using StatisticPair::StatisticPair;
protected:
	virtual void adapt() override;
};

class NonparametricCoefficientOfVariation: public utils::StatisticSingle<double> {
public:
	using StatisticSingle::StatisticSingle;
protected:
	virtual void adapt() override;
};


class Vector {
public:
	struct Stats {
		std::pair<std::pair<double, double>, bool>
			reproductionDeviation{{0,0}, false};

		std::pair<double, bool> min{0, false};
		std::pair<double, bool> max{0, false};
		std::pair<size_t, bool> size{0, false};
	};

	class ClassSeries;
	class VarSeries;

public:
	Vector(const std::list<double>& = {});
	Vector(Vector&);
	void setVector(const std::list<double>&);
	const std::list<double>& vector();
	const std::list<double>& timeVector();
	~Vector();

public: // new statistics
	RawMoment rawMoment = RawMoment(this);
	MeanDeviation meanDeviation = MeanDeviation(this);
	MeanConfidence meanConfidence = MeanConfidence(this);
	CentralMoment centralMoment = CentralMoment(this);
	VarianceDeviation varianceDeviation = VarianceDeviation(this);
	VarianceConfidence varianceConfidence = VarianceConfidence(this);
	Skew skew = Skew(this);
	SkewDeviation skewDeviation = SkewDeviation(this);
	SkewConfidence skewConfidence = SkewConfidence(this);
	Kurtosis kurtosis = Kurtosis(this);
	KurtosisDeviation kurtosisDeviation = KurtosisDeviation(this);
	KurtosisConfidence kurtosisConfidence = KurtosisConfidence(this);
	MeanAbsoluteDeviation mad = MeanAbsoluteDeviation(this);
	TurncatedMean tmean = TurncatedMean(this);
	CounterKurtosis counterKurtosis = CounterKurtosis(this);
	StandardDeviation sd = StandardDeviation(this);
	Beta beta = Beta(this);
	WalshAverages walshAverages = WalshAverages(this);
	WalshAveragesMedian walshAveragesMed = WalshAveragesMedian(this);
	KolmConsentCriterion kolmConsentCriterion = KolmConsentCriterion(this);
	PearConsentCriterion pearConsentCriterion = PearConsentCriterion(this);
	CoefficientOfVariation cv = CoefficientOfVariation(this);
	NonparametricCoefficientOfVariation ncv = NonparametricCoefficientOfVariation(this);

public: // binds
	double variance(Measure m = Measure::Sample) { return centralMoment(2, m); };
	double mean() { return rawMoment(1); };
	double med() { return tmean(0.5); };
	
public: // statistics
	size_t size();
	double min();
	double max();
	
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
	::exprtk::symbol_table<double> transformationSymbolTable;
	void setTransformationSymbolTable();

private:
	void computeMinMaxSize();
};


}

#endif // !_VECTOR_HPP_
