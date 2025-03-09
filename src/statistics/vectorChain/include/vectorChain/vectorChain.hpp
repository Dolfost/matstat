#ifndef _VECTOR_CHAIN_HPP_
#define _VECTOR_CHAIN_HPP_	

#include <vector.hpp>
#include <vector/quantile.hpp>
#include <vector/utils.hpp>

#include <utility>
#include <cstddef>

#include <exprtk.hpp>

namespace ss {

#define WRAP_SINGLE(name) SS_WRAP_EXPRTK_SINGLE(name, VectorSet)
#define WRAP_PAIR(name) SS_WRAP_EXPRTK_PAIR(name, VectorSet)
#define WRAP_MAP(name) SS_WRAP_EXPRTK_MAP(name, VectorSet)
#define WRAP_PAIR_MAP(name) SS_WRAP_EXPRTK_PAIR_MAP(name, VectorSet)

class VectorChain: public std::vector<Vector> {
public:
	// class Correlation: public utils::StatisticSingle<double, VectorChain> {
	// public:
	// 	using StatisticSingle::StatisticSingle;
	// 	virtual void adapt() override;
	// } cor = Correlation(this);

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
