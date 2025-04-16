#include <vectorChain.hpp> 

#include <vectorChain/math.hpp> 

namespace ss {

void VectorChain::PluralCorelationRatio::adapt(std::size_t k) {
	ss::VectorChain& vc = *s_vector;

	if (k >= vc.size())
		throw std::logic_error("Індекс поза межами (множинна кореляція)");

	s_values[k] = std::sqrt(1 - determinant(vc.r())/determinant(minor(vc.r(), k)));
}

}
