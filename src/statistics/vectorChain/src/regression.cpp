#include <vectorChain.hpp>

namespace ss {

void VectorChain::Regression::setModel(std::vector<double> p) {
	if (s_vector->size() != p.size())
		throw std::logic_error("Кількість параметрів не відповідає кількості векторів");

	parameters = p;
}
double VectorChain::Regression::regression(std::vector<double> x) {
	if (x.size() - 1 != parameters.size())
		throw std::logic_error("Кількість параметрів не рівна кількості аргументів (регресія)");
}

}
