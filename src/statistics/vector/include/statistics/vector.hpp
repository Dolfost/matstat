#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <QString>
#include <QDebug>
#include <QFile>
#include <exprtk.hpp>

#include <cstddef>
#include <list>

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

class WalshAverages: public utils::StatisticContainer<std::list<double>> {
public:
	using StatisticContainer::StatisticContainer;
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

class Sorted: public utils::StatisticContainer<std::list<double>> {
public:
	using StatisticContainer::StatisticContainer;
protected:
	virtual void adapt() override;
};

class Vector: protected std::list<double> {
public:
		// iterates as x = (h+0.5)i; i is the vector index
		// has size of M for O(n) access speed
	class ClassSeries
	: public utils::StatisticContainer<std::vector<std::pair<std::size_t, double>>> {
	public:
		using StatisticContainer::StatisticContainer;
		bool makeSeries(std::size_t = 0);

		const std::vector<std::pair<std::size_t, double>>&
		series() {
			return value();
		};
		const std::vector<std::pair<int, double>>& 
		cumSeries() {
			if (!s_valid)
				adapt();
			return c_cumSeries;
		}

		double cdf(double);
		double pdf(double);

		virtual void invalidate() override {
			c_cumSeries.clear();
			StatisticContainer::invalidate();
		}
	public: // properties
		double step(); // h
		double maxProb(); // max P_i
		std::size_t maxN(); // max N_i
		std::size_t setCount(std::size_t);
		std::size_t count(); // M
		std::size_t calculateCount();

	private:
		virtual void adapt() override;
		std::vector<std::pair<int, double>> c_cumSeries; 
		std::size_t c_count; // M
		double c_maxProb; // max P_i
		std::size_t c_maxCount; // max N_i
		double c_h; // h
	} classSeries = ClassSeries(this);
	// has size of r; varSeries[x_i].first = n_i, varSeries[x_i].second = p_i
	class VarSeries: public utils::StatisticContainer<std::map<double, std::pair<std::size_t, double>>> {
	public:
		using StatisticContainer::StatisticContainer;
		std::map<double, std::pair<std::size_t, double>>::const_iterator begin() { return s_value.cbegin(); };
		std::map<double, std::pair<std::size_t, double>>::const_iterator end() { return s_value.cend(); };
		std::map<double, std::pair<std::size_t, double>>::const_iterator cbegin() { return s_value.cbegin(); };
		std::map<double, std::pair<std::size_t, double>>::const_iterator cend() { return s_value.cend(); };
		void clear() { return s_value.clear(); };
		std::pair<std::size_t, double> operator[](double at) {
			return s_value[at];
		}

		virtual void adapt() override;
		std::size_t count() { // r 
			return value().size();
		};
	} varSeries = VarSeries(this);
		
	class Distribution {
	public:
		Distribution();
		~Distribution();

		enum class Model {
			Unknown,
			Normal,
			Exponential,
			Weibull,
			LogNormal,
			Uniform,
			Count,
		} model = Model::Unknown;

		enum class Method {
			Inverse,
			Plane,
			Count,
		};

		void setDistribution(Model, std::vector<double>, size_t);
		static const QStringList distributionName;
		static const QStringList methodName;
		static const QList<QStringList> parameterName;

		std::list<double> generateSet(Method, size_t = 0, double = 0, double = 1);

	public:
		double confidence = 0.95;

		std::pair<double, double> cdfConfidence(double x1, double = 0.95);

		QString cdfString;
		QString pdfString;
		QString invCdfString;

		double pdf(double);
		double cdf(double);
		double cdfDev(double);
		double invCdf(double);

		std::pair<double, double> domain = {1, 1};	

		size_t size = 0;
		size_t parametersCount = 0;
		std::vector<QString> paremeterNames;
		std::vector<QString> parametersDeviationNames;
		std::vector<double> parameters{0};
		std::vector<double> parametersDeviation{0};
		double parametersCv = 0;
		double pdfMax = 0;

	private:
		std::function<double(double)> d_pdf;
		std::function<double(double)> d_cdf;
		std::function<double(double)> d_invCdf;
		std::function<double(double)> d_cdfDev;
	};

public:
	Vector(const std::list<double>& = {});
	Vector(Vector&);
	void setVector(const std::list<double>&);
	~Vector();

public:
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
	const_iterator begin() {
		return cbegin();
	}
	const_iterator end() {
		return cend();
	}
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

	Distribution dist;
	bool reproduceDistribution(Distribution::Model);

public: // general
	QString report();
	void invalidate();
	static const QString exprtkFuncitons;
	//  TODO: move from std::list to Vector insertion
	const std::list<double>& list() { 
		return static_cast<const std::list<double>&>(*this); 
	}

private: // data
	bool transformationSymbolTableReady = false;
	::exprtk::symbol_table<double> transformationSymbolTable;
	void setTransformationSymbolTable();
};


}

#endif // !_VECTOR_HPP_
