#include "vector.hpp"

namespace ss {

void Vector::VarSeries::adapt() {
	for (auto const& i : *s_vector) {
		s_value[i].first++;
	}

	for (auto const& [key, val] : *this) {
		s_value[key].second = s_value[key].first/double(s_vector->size());
	}
}

}
