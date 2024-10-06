#include <vectorPair.hpp>

namespace ss {

void VectorPair::ConnectionsTable::adapt() {
	ss::VectorPair& v = *s_vector;
	std::size_t h = v.y.len(), w = v.x.len();

	s_value.resize(w, std::vector<double>(h, 0));
	c_rowCount.resize(w, 0);
	c_columnCount.resize(h, 0);

	for (long long i = v.x.min(); i <= v.x.max(); i++) {
		for (long long j = v.y.min(); j <= v.y.max(); j++) {
			std::size_t val = v.vs[{i, j}].first;
			s_value[i][j] = val;
			c_rowCount[i] += val;
			c_columnCount[j] += val;
		}
	}
}

}
