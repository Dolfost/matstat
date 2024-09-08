#include "vector.hpp"

#include "exprtk.hpp"

namespace ss {

std::string Vector::transform(std::string expression) {
	std::string msg;

  ::exprtk::expression<double> expr;
  ::exprtk::parser<double> parser;
  setExprtkSymbolTable();

  double x;
  transformationSymbolTable.remove_variable("x");
  transformationSymbolTable.add_variable("x", x);

  expr.register_symbol_table(transformationSymbolTable);

  if (!parser.compile(expression, expr)) {
    msg.append("Error computing xₙ: " + std::string(parser.error().c_str()) +
               "\nExpression: '" + std::string(expression.c_str()) +
               "'\n");
    return msg;
  }

  for (auto &timeSeriesValue : static_cast<std::list<double>&>(*this)) {
    x = timeSeriesValue;
		timeSeriesValue = expr.value();
  }

  invalidate();

  return msg;
}

}
