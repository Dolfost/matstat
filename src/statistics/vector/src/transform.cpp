#include "vector.hpp"

#include "exprtk.hpp"

namespace ss {

QString Vector::transform(QString expression) {
  QString msg;

  ::exprtk::expression<double> expr;
  ::exprtk::parser<double> parser;
  setTransformationSymbolTable();

  double x;
  transformationSymbolTable.remove_variable("x");
  transformationSymbolTable.add_variable("x", x);

  expr.register_symbol_table(transformationSymbolTable);

  if (!parser.compile(expression.toStdString(), expr)) {
    msg.append("Error computing xₙ: " + QString(parser.error().c_str()) +
               "\nExpression: '" + QString(expression.toStdString().c_str()) +
               "'\n");
    return msg;
  }

  for (auto &timeSeriesValue : *this) {
    x = timeSeriesValue;
		timeSeriesValue = expr.value();
  }

  invalidate();

  return msg;
}

}
