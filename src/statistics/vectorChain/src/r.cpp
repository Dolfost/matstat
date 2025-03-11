#include <vectorChain.hpp> 

namespace ss {

void VectorChain::R::adapt() {
	ss::VectorChain& vc = *s_vector;
	s_value.resize(vc.size());

	for (std::size_t i = 0; i < vc.size(); i++) {
		s_value[i].resize(vc.size());
		for (std::size_t j = 0; j < vc.size(); j++)
			s_value[i][j] = vc.pcor({i, j});
	}
}

}
