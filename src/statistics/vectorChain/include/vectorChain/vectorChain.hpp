#ifndef _VECTOR_CHAIN_HPP_
#define _VECTOR_CHAIN_HPP_	

#include <iostream>
#include <vector.hpp>
#include <vector/quantile.hpp>
#include <vector/utils.hpp>

#include <iterator>

#include <exprtk.hpp>

namespace ss {

#define WRAP_SINGLE(name) SS_WRAP_EXPRTK_SINGLE(name, VectorSet)
#define WRAP_PAIR(name) SS_WRAP_EXPRTK_PAIR(name, VectorSet)
#define WRAP_MAP(name) SS_WRAP_EXPRTK_MAP(name, VectorSet)
#define WRAP_PAIR_MAP(name) SS_WRAP_EXPRTK_PAIR_MAP(name, VectorSet)

class VectorChain: public std::vector<Vector> {
public:
	class PairCorrelation: public utils::StatisticMap<std::pair<std::size_t, std::size_t>, double, std::pair<std::size_t, std::size_t>, VectorChain> {
	public:
		using StatisticMap::StatisticMap;
		virtual void adapt(std::pair<std::size_t, std::size_t>) override;
	} pcor = PairCorrelation(this);

	class DC: public utils::StatisticSingle<std::vector<std::vector<double>>, VectorChain> {
	public:
		using StatisticSingle::StatisticSingle;
		virtual void adapt() override;
	} dc = DC(this);

	class R: public utils::StatisticSingle<std::vector<std::vector<double>>, VectorChain> {
	public:
		using StatisticSingle::StatisticSingle;
		virtual void adapt() override;
	} r = R(this);
	
	VectorChain() {};
	template<class Iter, typename std::enable_if<std::is_same<typename
	std::iterator_traits<Iter>::iterator_category,
	std::random_access_iterator_tag>::value and std::is_same<typename
	std::iterator_traits<Iter>::value_type, ss::Vector*>::value, int>::type = 0>
	VectorChain(const Iter& begin, const Iter& end) {
		const std::size_t l = (*begin)->size();
		for (auto i = std::next(begin); i != end; i++) {
			if ((*i)->size() != l)
				throw std::logic_error("Вектори різного розміру");
		}
		for (auto i = begin; i != end; i++) {
			push_back(**i);
		}
	}

	template<class Iter, typename std::enable_if<std::is_same<typename
	std::iterator_traits<Iter>::iterator_category,
	std::random_access_iterator_tag>::value and std::is_same<typename
	std::iterator_traits<Iter>::value_type, ss::Vector>::value, int>::type = 0>
	VectorChain(const Iter& begin, const Iter& end) {
		const std::size_t l = (*begin).size();
		for (auto i = std::next(begin); i != end; i++) {
			if ((*i).size() != l)
				throw std::logic_error("Вектори різного розміру");
		}
		for (auto i = begin; i != end; i++) {
			push_back(*i);
		}
	}

	void writeToFile(std::string filename);

public:
	// std::string transform(std::string, std::string);

public:
	void invalidate();

	// static void setExprtkSymbolTable(::exprtk::symbol_table<double>&, VectorSet*, std::string = "");
	// static const std::string exprtkFunctions;
protected:
	void checkSize();

	// ::exprtk::symbol_table<double> v_exprtkSymbolTable;
};

#undef WRAP_SINGLE
#undef WRAP_PAIR
#undef WRAP_MAP
#undef WRAP_PAIR_MAP

}

#endif // !_VECTOR_CHAIN_HPP_
