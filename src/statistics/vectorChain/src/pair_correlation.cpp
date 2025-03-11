#include <vectorChain.hpp> 
#include <vectorPair.hpp> 

namespace ss {

void VectorChain::PairCorrelation::adapt(std::pair<std::size_t, std::size_t> idx) {
	if (idx.first == idx.second) {
		s_values[idx] = 1;
		return;
	}

	ss::VectorChain& vc = *s_vector;

	if (idx.first >= vc.size() or idx.second >= vc.size())
		throw std::logic_error("Індекс поза межами (парна кореляція)");

	ss::VectorPair p(vc[idx.first], vc[idx.second]);
	s_values[idx] = p.cor();
}

}
