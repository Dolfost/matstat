#include <vectorPair.hpp>

namespace ss {

void VectorPair::VarSeries::adapt() {
	for (auto x = s_vector->x.begin(), y = s_vector->y.begin(); x != s_vector->x.end(); x++, y++) {
		s_value[{*x, *y}].first++;
	}

	for (auto const& [key, val] : *this) {
		s_value[key].second = s_value[key].first/double(s_vector->size());
	}
}

}
