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

class WalshAverages: public utils::StatisticList<std::list<double>> {
public:
	using StatisticList::StatisticList;
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

class Min: public utils::StatisticSingle<double> {
public:
	using StatisticSingle::StatisticSingle;
protected:
	virtual void adapt() override;
};

class Max: public utils::StatisticSingle<double> {
public:
	using StatisticSingle::StatisticSingle;
protected:
	virtual void adapt() override;
};

class Sorted: public utils::StatisticList<std::list<double>> {
public:
	using StatisticList::StatisticList;
protected:
	virtual void adapt() override;
};

class Vector: protected std::list<double> {
public:
	class ClassSeries;
	class VarSeries;

public:
	Vector(const std::list<double>& = {});
	Vector(Vector&);
	void setVector(const std::list<double>&);
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
	Sorted sorted = Sorted(this);
	Min min = Min(this);
	Max max = Max(this);

	using std::list<double>::size;

	using std::list<double>::front;
	using std::list<double>::back;
	using std::list<double>::begin;
	using std::list<double>::end;
	using std::list<double>::cbegin;
	using std::list<double>::cend;
	using std::list<double>::crbegin;
	using std::list<double>::crend;
	using std::list<double>::empty;
public: // binds
	double variance(Measure m = Measure::Sample) { return centralMoment(2, m); };
	double mean() { return rawMoment(1); };
	double med() { return tmean(0.5); };
	
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
	void invalidate();
	static const QString exprtkFuncitons;
	//  TODO: move from std::list to Vector insertion
	const std::list<double>& list() { 
		return static_cast<const std::list<double>&>(*this); 
	}

private: // data
	ClassSeries* cs;
	VarSeries* vs;
	bool csReady = false;
	bool vsReady = false;

	bool transformationSymbolTableReady = false;
	::exprtk::symbol_table<double> transformationSymbolTable;
	void setTransformationSymbolTable();
};


}

#endif // !_VECTOR_HPP_
