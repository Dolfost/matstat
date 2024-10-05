#include <vectorPair.hpp>
#include <vector.hpp>

namespace ss {

void VectorPair::setExprtkSymbolTable(::exprtk::symbol_table<double>& t, VectorPair* v, std::string p) {
	SS_ADD_FUNCTION(cor);
	SS_ADD_FUNCTION(pRawMoment);
	SS_ADD_FUNCTION_N(min, "first");
	SS_ADD_FUNCTION_N(max, "last");
	SS_ADD_FUNCTION(corRatio);
	SS_ADD_FUNCTION(corSpearman);
	SS_ADD_FUNCTION(corKendall);

	Vector::addStatisticsToSymbolTable(t, &v->x, "x");
	Vector::addStatisticsToSymbolTable(t, &v->y, "y");

	Vector::addGenericsToSymbolTable(t);
}

const std::string VectorPair::exprtkFunctions = 
	"cor() — кореляція\n"
	"pRawMoment(k) — почтковий момент x*y порядку k\n"
	"min() — найменше з xmin() та ymin()\n"
	"max() — найбільше з xmax() та ymax()\n"
	"corRatio() — кореляційне відношення\n"
	"corSpearman() — кореляційне відношення за Спірменом\n"
	"corKendall() — кореляційне відношення за Кендаллом";

}
