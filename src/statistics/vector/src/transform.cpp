#include "vector.hpp"

#include "exprtk.hpp"

namespace ss {

std::string Vector::transform(std::string expression) {
	std::string msg;

  ::exprtk::expression<double> expr;
  ::exprtk::parser<double> parser;

  double x, xr;

  v_exprtkSymbolTable.remove_variable("x");
  v_exprtkSymbolTable.remove_variable("xr");

  v_exprtkSymbolTable.add_variable("x", x);
  v_exprtkSymbolTable.add_variable("xr", xr);

  expr.register_symbol_table(v_exprtkSymbolTable);

  if (!parser.compile(expression, expr)) {
    msg.append("Error computing xₙ: " + std::string(parser.error().c_str()) +
               "\nExpression: '" + std::string(expression.c_str()) +
               "'\n");
    return msg;
  }

	auto rit = ranks().begin();
  for (auto& timeSeriesValue : static_cast<std::list<double>&>(*this)) {
    x = timeSeriesValue, xr = *rit;
		timeSeriesValue = expr.value();
		rit++;
  }

  invalidate();


  return msg;
}

}
