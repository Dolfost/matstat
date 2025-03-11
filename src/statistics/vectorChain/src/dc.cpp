#include <vectorChain.hpp> 

namespace ss {

void VectorChain::DC::adapt() {
	ss::VectorChain& vc = *s_vector;
	s_value.resize(vc.size());

	for (std::size_t i = 0; i < vc.size(); i++) {
		s_value[i].resize(vc.size());
		for (std::size_t j = 0; j < vc.size(); j++)
			if (i == j)
				s_value[i][i] = vc[i].variance();
			else
				s_value[i][j] = vc[i].sd()*vc[j].sd()*vc.pcor({i, j});
	}
}

}
