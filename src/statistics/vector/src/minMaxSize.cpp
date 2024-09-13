#include "vector.hpp"

namespace ss {

void Vector::Min::adapt() {
	s_value = s_vector->sorted().front();
}

void Vector::Max::adapt() {
	s_value = s_vector->sorted().back();
}


}
