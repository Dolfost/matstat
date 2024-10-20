#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include <exprtk.hpp>

#include <cstddef>
#include <list>
#include <string>

#include <random>

#include"utils.hpp"

namespace ss {

template<class Cont, class B=Vector>
class ClassSeries
: public utils::StatisticContainer<std::vector<Cont>, B> {
public:
	using utils::StatisticContainer<std::vector<Cont>, B>::StatisticContainer;
	ClassSeries(const ClassSeries& other): utils::StatisticContainer<std::vector<Cont>, B>(other) {
		c_maxProb = other.c_maxProb;
		c_maxCount = other.c_maxCount;
		c_cumSeries = other.c_cumSeries;
	}
	const std::vector<Cont>&
	series() {
		return this->value();
	};
	virtual void invalidate() override {
		c_cumSeries.clear();
		utils::StatisticContainer<std::vector<Cont>, B>::invalidate();
	}

	const std::vector<Cont>& 
	cumSeries() {
		if (!this->s_valid)
			this->adapt();
		return c_cumSeries;
	}

public: // properties
	std::size_t maxN() {
		if (!this->s_valid)
			this->adapt();
		return c_maxCount;
	}

	double maxProb() {
		if (!this->s_valid)
			this->adapt();
		return c_maxProb;
	}
protected:
	double c_maxProb; // max P_i
	std::size_t c_maxCount; // max N_i
	std::vector<Cont> c_cumSeries; 
};

template<class From, class B=Vector>
class VarSeries: public utils::StatisticContainer<std::map<From, std::pair<std::size_t, double>>, B> {
public:
	using utils::StatisticContainer<std::map<From, std::pair<std::size_t, double>>, B>::StatisticContainer;
	typename std::map<From, std::pair<std::size_t, double>>::const_iterator begin() { return this->s_value.cbegin(); };
	typename std::map<From, std::pair<std::size_t, double>>::const_iterator end() { return this->s_value.cend(); };
	typename std::map<From, std::pair<std::size_t, double>>::const_iterator cbegin() { return this->s_value.cbegin(); };
	typename std::map<From, std::pair<std::size_t, double>>::const_iterator cend() { return this->s_value.cend(); };
	void clear() { return this->s_value.clear(); };
	std::pair<std::size_t, double> operator[](From at) {
		if (!this->s_valid)
			this->adapt();
		return this->s_value[at];
	}
	std::size_t count() { // r 
		if (!this->s_valid)
			this->adapt();
		return this->s_value.size();
	};
};

#define WRAP_SINGLE(name) SS_WRAP_EXPRTK_SINGLE(name, Vector)
#define WRAP_PAIR(name) SS_WRAP_EXPRTK_PAIR(name, Vector)
#define WRAP_MAP(name) SS_WRAP_EXPRTK_MAP(name, Vector)
#define WRAP_PAIR_MAP(name) SS_WRAP_EXPRTK_PAIR_MAP(name, Vector)

class Vector: protected std::list<double> {
public: // statistics
	class RawMoment: public utils::StatisticMap<double, double> {
	public:
		using StatisticMap::StatisticMap;
	protected:
		virtual void adapt(double degree) override;
	} rawMoment = RawMoment(this);
	WRAP_MAP(rawMoment);

	class MeanDeviation: public utils::StatisticSingle<double> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} meanDeviation = MeanDeviation(this);
	WRAP_SINGLE(meanDeviation);

	class MeanConfidence: public utils::Confidence<double, double> {
	public:
		using Confidence::Confidence;
	protected:
		virtual void adapt(double) override;
	} meanConfidence = MeanConfidence(this);

	class CentralMoment: public utils::StatisticPairMap<double, double, Measure> {
	public:
		using StatisticPairMap::StatisticPairMap;
	protected:
		virtual void adapt(double degre) override;
	} centralMoment = CentralMoment(this);
	WRAP_PAIR_MAP(centralMoment);

	class VarianceDeviation: public utils::StatisticSingle<double> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} varianceDeviation = VarianceDeviation(this);
	WRAP_SINGLE(varianceDeviation);

	class VarianceConfidence: public utils::Confidence<double, double> {
	public:
		using Confidence::Confidence;
	protected:
		virtual void adapt(double) override;
	} varianceConfidence = VarianceConfidence(this);

	class Skew: public utils::StatisticPair<double, Measure> {
	public:
		using StatisticPair::StatisticPair;
	protected:
		virtual void adapt() override;
	} skew = Skew(this);
	WRAP_PAIR(skew);

	class SkewDeviation: public utils::StatisticSingle<double> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} skewDeviation = SkewDeviation(this);

	class SkewConfidence: public utils::Confidence<double, double> {
	public:
		using Confidence::Confidence;
	protected:
		virtual void adapt(double) override;
	} skewConfidence = SkewConfidence(this);

	class Kurtosis: public utils::StatisticPair<double, Measure> {
	public:
		using StatisticPair::StatisticPair;
	protected:
		virtual void adapt() override;
	} kurtosis = Kurtosis(this);
	WRAP_PAIR(kurtosis);

	class KurtosisDeviation: public utils::StatisticSingle<double> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} kurtosisDeviation = KurtosisDeviation(this);

	class KurtosisConfidence: public utils::Confidence<double, double> {
	public:
		using Confidence::Confidence;
	protected:
		virtual void adapt(double) override;
	} kurtosisConfidence = KurtosisConfidence(this);

	class MeanAbsoluteDeviation: public utils::StatisticSingle<double> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} mad = MeanAbsoluteDeviation(this);
	WRAP_SINGLE(mad);

	class TurncatedMean: public utils::StatisticMap<double, double, std::size_t> {
	public:
		using StatisticMap::StatisticMap;
		virtual double value(double) override;
	protected:
		virtual void adapt(std::size_t) override;
	} tmean = TurncatedMean(this);
	WRAP_MAP(tmean);

	class CounterKurtosis: public utils::StatisticPair<double, Measure> {
	public:
		using StatisticPair::StatisticPair;
	protected:
		virtual void adapt() override;
	} counterKurtosis = CounterKurtosis(this);
	WRAP_PAIR(counterKurtosis);

	class StandardDeviation: public utils::StatisticPair<double, Measure> {
	public:
		using StatisticPair::StatisticPair;
	protected:
		virtual void adapt() override;
	} sd = StandardDeviation(this);
	WRAP_PAIR(sd);

	class Beta: public utils::StatisticMap<std::size_t, double> {
	public:
		using StatisticMap::StatisticMap;
	protected:
		virtual void adapt(std::size_t) override;
	} beta = Beta(this);
	WRAP_MAP(beta);

	class WalshAverages: public utils::StatisticContainer<std::list<double>> {
	public:
		using StatisticContainer::StatisticContainer;
	protected:
		virtual void adapt() override;
	} walshAverages = WalshAverages(this);

	class WalshAveragesMedian: public utils::StatisticSingle<double> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} wam = WalshAveragesMedian(this);
	WRAP_SINGLE(wam);

	class CoefficientOfVariation: public utils::StatisticPair<double, Measure> {
	public:
		using StatisticPair::StatisticPair;
	protected:
		virtual void adapt() override;
	} cv = CoefficientOfVariation(this);
	WRAP_PAIR(cv);

	class NonparametricCoefficientOfVariation: public utils::StatisticSingle<double> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} ncv = NonparametricCoefficientOfVariation(this);
	WRAP_SINGLE(ncv);

	class Min: public utils::StatisticSingle<double> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} min = Min(this);
	WRAP_SINGLE(min);

	class Max: public utils::StatisticSingle<double> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} max = Max(this);
	WRAP_SINGLE(max);

	class Length: public utils::StatisticSingle<double> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} len = Length(this);
	WRAP_SINGLE(len);

	class Sorted: public utils::StatisticContainer<std::list<double>> {
	public:
		using StatisticContainer::StatisticContainer;
	protected:
		virtual void adapt() override;
	} sorted = Sorted(this);

	class Ranks: public utils::StatisticContainer<std::list<double>> {
	public:
		using StatisticContainer::StatisticContainer;
		const std::list<std::size_t>& links() {
			if (!s_valid)
				adapt();
			return r_links;
		}
		virtual void invalidate() override {
			r_links.clear();
			StatisticContainer::invalidate();
		}
	protected:
		virtual void adapt() override;
		std::list<std::size_t> r_links;
	} ranks = Ranks(this);

public:
	class ClassSeries: public ss::ClassSeries<std::pair<std::size_t, double>> {
	// iterates as x = (h+0.5)i; i is the vector index
	// has size of M for O(n) access speed
	public:
		using ss::ClassSeries<std::pair<std::size_t, double>>::ClassSeries;

		double cdf(double);
		double pdf(double);

	public: // properties
		double step(); // h
		std::size_t setCount(std::size_t);
		std::size_t count(); // M
		std::size_t calculateCount();

	private:
		virtual void adapt() override;
		std::size_t c_count = 0; // M
		double c_h; // h
	} cs = ClassSeries(this);

	class VarSeries: public ss::VarSeries<double> {
	public:
		using ss::VarSeries<double>::VarSeries;
		virtual void adapt() override;
	} vs = VarSeries(this);
		
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
		static const std::vector<std::string> distributionName;
		static const std::vector<std::string> methodName;
		static const std::vector<std::vector<std::string>> parameterName;

		std::list<double> generateSet(Method, size_t = 0, double = 0, double = 1);

	public:
		std::pair<double, double> cdfConfidence(double x1);
		double confidence() { return d_confidence; };
		void setConfidence(double c) { d_confidence = c; };

		double pdf(double);
		double cdf(double);
		double cdfDev(double);
		double invCdf(double);

		std::pair<double, double> domain = {1, 1};	

		size_t size = 0;
		size_t parametersCount = 0;
		std::vector<std::string> paremeterNames;
		std::vector<std::string> parametersDeviationNames;
		std::vector<double> parameters{0};
		std::vector<double> parametersDeviation{0};
		double parametersCv = 0;
		double pdfMax = 0;

	private:
		std::function<double(double)> d_pdf;
		std::function<double(double)> d_cdf;
		std::function<double(double)> d_invCdf;
		std::function<double(double)> d_cdfDev;
		double d_confidence = 0.95;
	};

public:
	Vector();
	Vector(const std::list<double>&);
	Vector(const Vector&);
	void setVector(const std::list<double>&);
	~Vector();

public:
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
	WRAP_PAIR(variance);
	double mean() { return rawMoment(1); };
	WRAP_SINGLE(mean);
	double med() { return tmean(0.5); };
	WRAP_SINGLE(med);

	WRAP_SINGLE(size);
	
public: // vector operations
	void standardize();
	bool removeOutliers();
	size_t trim(double, double);
	std::string transform(std::string);

	bool writeToFile(std::string);

public: // distribution recreation
	double cdf(double);

	Distribution dist;
	bool reproduceDistribution(Distribution::Model);

public: // general
	std::string report();
	void invalidate();
	std::function<void(void)>& invalidateCallback() {
		return v_invalidateCallback;
	};
	void setInvalidateCallback(std::function<void(void)> fc) {
		v_invalidateCallback = fc;
	};
	static const std::string exprtkFuncitons;
	//  TODO: move from std::list to Vector insertion
	const std::list<double>& list() const { 
		return static_cast<const std::list<double>&>(*this); 
	}
	Vector& operator=(const Vector&);

	static void addStatisticsToSymbolTable(::exprtk::symbol_table<double>&, Vector*, std::string = "");
	static void addGenericsToSymbolTable(::exprtk::symbol_table<double>&, std::string = "");

protected: // data
	std::function<void(void)> v_invalidateCallback = [](){};
	::exprtk::symbol_table<double> v_exprtkSymbolTable;
};

#undef WRAP_SINGLE
#undef WRAP_PAIR
#undef WRAP_MAP
#undef WRAP_PAIR_MAP

}

#endif // !_VECTOR_HPP_
