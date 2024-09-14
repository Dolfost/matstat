#include <vector.hpp>

namespace ss {

void Vector::Length::adapt() {
	s_value = std::abs(s_vector->max() - s_vector->min());
}

}
