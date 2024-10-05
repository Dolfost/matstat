#include <vectorPair.hpp>

namespace ss {

std::string VectorPair::transform(std::string xExpr, std::string yExpr) {
	std::string msg;

  ::exprtk::expression<double> xexpr;
  ::exprtk::expression<double> yexpr;
  ::exprtk::parser<double> parser;

  double x, y, xr, yr, r;

  v_exprtkSymbolTable.remove_variable("xr");
  v_exprtkSymbolTable.remove_variable("yr");
  v_exprtkSymbolTable.remove_variable("r");
  v_exprtkSymbolTable.remove_variable("x");
  v_exprtkSymbolTable.remove_variable("y");

  v_exprtkSymbolTable.add_variable("x", x);
  v_exprtkSymbolTable.add_variable("y", y);
  v_exprtkSymbolTable.add_variable("r", r);
  v_exprtkSymbolTable.add_variable("xr", xr);
  v_exprtkSymbolTable.add_variable("yr", yr);

  xexpr.register_symbol_table(v_exprtkSymbolTable);
  yexpr.register_symbol_table(v_exprtkSymbolTable);

  if (!parser.compile(xExpr, xexpr)) {
    msg.append("Error computing xₙ: " + std::string(parser.error().c_str()) +
               "\nExpression: '" + std::string(xExpr.c_str()) +
               "'\n");
    return msg;
  }

  if (!parser.compile(yExpr, yexpr)) {
    msg.append("Error computing xₙ: " + std::string(parser.error().c_str()) +
               "\nExpression: '" + std::string(yExpr.c_str()) +
               "'\n");
    return msg;
  }

	std::list<double> xl = this->x.list();
	std::list<double> yl = this->y.list();

	auto xrit = this->x.ranks().begin(), yrit = this->y.ranks().begin();
	auto rit = this->ranks().begin();
  for (auto xit = xl.begin(), yit = yl.begin(); xit != xl.end(); xit++, yit++, xrit++, yrit++, rit++) {
		x = *xit, y = *yit, yr = *yrit, xr = *xrit, r = *rit;
		*xit = xexpr.value();
		*yit = yexpr.value();
  }

	setX(xl);
	setY(yl);

  return msg;
}

}
