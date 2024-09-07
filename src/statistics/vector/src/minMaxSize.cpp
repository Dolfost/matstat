#include "vector.hpp"

namespace ss {

void Min::adapt() {
	s_value = s_vector.sorted().front();
}

void Max::adapt() {
	s_value = s_vector.sorted().back();
}


}
