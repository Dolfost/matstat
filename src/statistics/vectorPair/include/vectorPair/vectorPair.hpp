#ifndef _VECTOR_PAIR_HPP_
#define _VECTOR_PAIR_HPP_	

#include <vector.hpp>
#include <vector/utils.hpp>

#include <utility>
#include <cstddef>

namespace ss {

class VectorPair {
public:
	class Corelation: public utils::StatisticSingle<double, VectorPair> {
	public:
		using StatisticSingle::StatisticSingle;
		virtual void adapt() override;
	} cor = Corelation(this);

	class CorelationConfidence: public utils::Confidence<double, double, VectorPair> {
	public:
		using Confidence::Confidence;
		virtual void adapt(double) override;
	} corConfidence = CorelationConfidence(this);

	class ProductRawMoment: public utils::StatisticMap<double, double, double, VectorPair> {
	public:
		using StatisticMap::StatisticMap;
		virtual void adapt(double) override;
	} pRawMoment = ProductRawMoment(this);

	class Min: public utils::StatisticSingle<double, VectorPair> {
	public:
		using StatisticSingle::StatisticSingle;
		virtual void adapt() override { s_value = std::min(s_vector->x.min(), s_vector->y.min()); }
	} min = Min(this);

	class Max: public utils::StatisticSingle<double, VectorPair> {
	public:
		using StatisticSingle::StatisticSingle;
		virtual void adapt() override { s_value = std::max(s_vector->x.max(), s_vector->y.max()); }
	} max = Max(this);

	std::size_t size() { return v_x.size(); };
	double pmean() { return pRawMoment(1); };

public:
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
	// has size of r; varSeries[x_i].first = n_i, varSeries[x_i].second = p_i
	
	Vector& x = v_x;
	Vector& y = v_y;

public:
	VectorPair(const std::list<double> ft = {}, 
						const std::list<double> sd = {});
	VectorPair(const Vector&,
						const Vector&);
	VectorPair(const VectorPair&);
	VectorPair& operator=(const VectorPair&);

public:
	void invalidate();

private:
	Vector v_x;
	Vector v_y;
	void checkSize();
};

}

#endif // !_VECTOR_PAIR_HPP_
