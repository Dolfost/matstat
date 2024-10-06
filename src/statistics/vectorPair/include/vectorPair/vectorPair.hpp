#ifndef _VECTOR_PAIR_HPP_
#define _VECTOR_PAIR_HPP_	

#include <vector.hpp>
#include <vector/utils.hpp>

#include <utility>
#include <cstddef>

#include <exprtk.hpp>


namespace ss {

#define WRAP_SINGLE(name) SS_WRAP_EXPRTK_SINGLE(name, VectorPair)
#define WRAP_PAIR(name) SS_WRAP_EXPRTK_PAIR(name, VectorPair)
#define WRAP_MAP(name) SS_WRAP_EXPRTK_MAP(name, VectorPair)
#define WRAP_PAIR_MAP(name) SS_WRAP_EXPRTK_PAIR_MAP(name, VectorPair)

class VectorPair {
public:
	class Correlation: public utils::StatisticSingle<double, VectorPair> {
	public:
		using StatisticSingle::StatisticSingle;
		virtual void adapt() override;
	} cor = Correlation(this);
	WRAP_SINGLE(cor)

	class CorrelationConfidence: public utils::Confidence<double, double, VectorPair> {
	public:
		using Confidence::Confidence;
		virtual void adapt(double) override;
	} corConfidence = CorrelationConfidence(this);

	class ProductRawMoment: public utils::StatisticMap<double, double, double, VectorPair> {
	public:
		using StatisticMap::StatisticMap;
		virtual void adapt(double) override;
	} pRawMoment = ProductRawMoment(this);
	WRAP_MAP(pRawMoment)

	class Min: public utils::StatisticSingle<double, VectorPair> {
	public:
		using StatisticSingle::StatisticSingle;
		virtual void adapt() override { s_value = std::min(s_vector->x.min(), s_vector->y.min()); }
	} min = Min(this);
	WRAP_SINGLE(min)

	class Max: public utils::StatisticSingle<double, VectorPair> {
	public:
		using StatisticSingle::StatisticSingle;
		virtual void adapt() override { s_value = std::max(s_vector->x.max(), s_vector->y.max()); }
	} max = Max(this);
	WRAP_SINGLE(max)

	class CorrelationRatio: public utils::StatisticSingle<double, VectorPair> {
	public:
		using StatisticSingle::StatisticSingle;
		virtual void adapt() override;
		std::size_t count() {
			if (!s_valid)
				adapt();
			return c_count;
		}
		std::size_t setCount(std::size_t d) {
			std::size_t old = c_count;
			c_count = d;
			invalidate();
			return old;
		}
		virtual void invalidate() override {
			s_vector->corRatioDeviation.invalidate();
			StatisticSingle::invalidate();
		}
	protected:
		std::size_t c_count = 0;
	} corRatio = CorrelationRatio(this);
	WRAP_SINGLE(corRatio)

	class CorrelationRatioDeviation: public utils::StatisticSingle<double, VectorPair> {
	public:
		using StatisticSingle::StatisticSingle;
		virtual void adapt() override;
	} corRatioDeviation = CorrelationRatioDeviation(this);

	class CorrelationRatioConfidence: public utils::Confidence<double, double, VectorPair> {
	public:
		using Confidence::Confidence;
		virtual void adapt(double) override;
	} corRatioConfidence = CorrelationRatioConfidence(this);

	class Ranks: public utils::StatisticContainer<std::list<double>, VectorPair> {
	public:
		using StatisticContainer::StatisticContainer;
	protected:
		virtual void adapt() override;
	} ranks = Ranks(this);
	
	class CorrelationSpearman: public utils::StatisticSingle<double, VectorPair> {
	public:
		using StatisticSingle::StatisticSingle;
		virtual void adapt() override;
	} corSpearman = CorrelationSpearman(this);
	WRAP_SINGLE(corSpearman)

	class CorrelationSpearmanDeviation: public utils::StatisticSingle<double, VectorPair> {
	public:
		using StatisticSingle::StatisticSingle;
		virtual void adapt() override;
	} corSpearmanDeviation = CorrelationSpearmanDeviation(this);

	class CorrelationSpearmanConfidence: public utils::Confidence<double, double, VectorPair> {
	public:
		using Confidence::Confidence;
		virtual void adapt(double) override;
	} corSpearmanConfidence = CorrelationSpearmanConfidence(this);
	
	class CorrelationKendall: public utils::StatisticSingle<double, VectorPair> {
	public:
		using StatisticSingle::StatisticSingle;
		virtual void adapt() override;
	} corKendall = CorrelationKendall(this);
	WRAP_SINGLE(corKendall)

	class CorrelationKendallDeviation: public utils::StatisticSingle<double, VectorPair> {
	public:
		using StatisticSingle::StatisticSingle;
		virtual void adapt() override;
	} corKendallDeviation = CorrelationKendallDeviation(this);

	class CorrelationKendallConfidence: public utils::Confidence<double, double, VectorPair> {
	public:
		using Confidence::Confidence;
		virtual void adapt(double) override;
	} corKendallConfidence = CorrelationKendallConfidence(this);

	std::size_t size() { return v_x.size(); };
	double pmean() { return pRawMoment(1); };
	WRAP_SINGLE(pmean)

public:
	class Distribution: public utils::StatisticSingle<std::function<double(double, double)>, VectorPair> {
	public:
		using StatisticSingle::StatisticSingle;
		void setParameters(std::vector<double>, size_t);
		virtual void adapt();
		static const std::vector<std::string> distributionName;
		static const std::vector<std::string> methodName;
		static const std::vector<std::vector<std::string>> parameterName;

		std::pair<std::list<double>, std::list<double>> generateSet(std::size_t = 0);

	public:
		double pdf(double, double);

		size_t parametersCount = 0;
		std::vector<std::string> paremeterNames;
		std::vector<double> parameters{0};

	private:
		std::function<double(double, double)> d_pdf;
	} dist = Distribution(this);

	using ClassSeriesT = std::vector<std::pair<std::size_t, double>>;
	class ClassSeries : public ss::ClassSeries<ClassSeriesT, VectorPair> {
	public:
		using ss::ClassSeries<ClassSeriesT, VectorPair>::ClassSeries;

		double pdf(double, double);
		double cdf(double, double);
		std::size_t countX() { 
			if (!s_valid)
				adapt();
			return c_countX; 
		};
		std::size_t countY() { 
			if (!s_valid)
				adapt();
			return c_countY; 
		};
		double stepX() { 
			if (!s_valid)
				adapt();
			return c_stepX; 
		};
		double stepY() { 
			if (!s_valid)
				adapt();
			return c_stepY; 
		};
		std::size_t setCountX(std::size_t c) { 
			std::size_t old = c_countX;
			c_countX = c;
			if (c != old)
				invalidate();
			return old; 
		};
		std::size_t setCountY(std::size_t c) { 
			std::size_t old = c_countY;
			c_countY = c;
			if (c != old)
				invalidate();
			return old; 
		};
	private:
		virtual void adapt() override;
		std::size_t c_countX = 0;
		std::size_t c_countY = 0;
		double c_stepX = 0;
		double c_stepY = 0;
	} cs = ClassSeries(this);

	class VarSeries: public ss::VarSeries<std::pair<double, double>, VectorPair> {
	public:
		using ss::VarSeries<std::pair<double, double>, VectorPair>::VarSeries;
		virtual void adapt() override;
	} vs = VarSeries(this);
	
	void reproduceDistribution();
	
	Vector& x = v_x;
	Vector& y = v_y;

	class ConnectionsTable: public utils::StatisticContainer<std::vector<std::vector<double>>, VectorPair> {
	public:
		using StatisticContainer::StatisticContainer;
		virtual void adapt() override;
		virtual void invalidate() override {
			c_rowCount.clear();
			c_columnCount.clear();
			StatisticContainer::invalidate();
		};

		const std::vector<double>& col() {
			if (!s_valid)
				adapt();
			return c_rowCount;
		}
		const std::vector<double>& row() {
			if (!s_valid)
				adapt();
			return c_columnCount;
		}

	protected:
		std::vector<double> c_rowCount, c_columnCount;
	};

public:
	VectorPair(const std::list<double> ft = {}, 
						const std::list<double> sd = {});
	VectorPair(const Vector&,
						const Vector&);
	VectorPair(const VectorPair&);
	VectorPair& operator=(const VectorPair&);
	void setX(const std::list<double>&);
	void setY(const std::list<double>&);

public:
	std::string transform(std::string, std::string);

public:
	void invalidate();

	static void setExprtkSymbolTable(::exprtk::symbol_table<double>&, VectorPair*, std::string = "");
	static const std::string exprtkFunctions;
protected:
	Vector v_x;
	Vector v_y;
	void checkSize();

	::exprtk::symbol_table<double> v_exprtkSymbolTable;
};

#undef WRAP_SINGLE
#undef WRAP_PAIR
#undef WRAP_MAP
#undef WRAP_PAIR_MAP

}

#endif // !_VECTOR_PAIR_HPP_
