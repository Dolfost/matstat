#include "vector.hpp"

namespace ss {

void Vector::Sorted::adapt() {
	s_value = std::vector<double>(s_vector->begin(), s_vector->end());
	std::sort(s_value.begin(), s_value.end());
}


}
