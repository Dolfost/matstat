#include "vector.hpp"

namespace ss {

void Sorted::adapt() {
	s_value = std::list<double>(s_vector.begin(), s_vector.end());
	s_value.sort();
}


}
