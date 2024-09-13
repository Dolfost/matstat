#ifndef _VECTOR_PAIR_HPP_
#define _VECTOR_PAIR_HPP_	

#include <vector.hpp>
#include <vector/utils.hpp>

#include <utility>
#include <cstddef>

namespace ss {

class VectorPair {
public:
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

public:
	using ClassSeriesT = std::vector<std::pair<std::size_t, double>>;
	class ClassSeries : public ss::ClassSeries<ClassSeriesT, VectorPair> {
	public:
		using ss::ClassSeries<ClassSeriesT, VectorPair>::ClassSeries;

		double pdf(double, double);
		double cdf(double, double);
	private:
		virtual void adapt() override;
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
	std::size_t size() { return v_x.size(); };

public:
	void invalidate();

private:
	Vector v_x;
	Vector v_y;
	void checkSize();
};

}

#endif // !_VECTOR_PAIR_HPP_
