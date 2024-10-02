#include <vectorPair.hpp>

namespace ss {

void VectorPair::Yranks::adapt() {
	std::list<double> yl = s_vector->y.sorted();
	std::list<double> ry = s_vector->y.ranks();

	std::list<double> yv = s_vector->y.list();
	std::list<double> xv = s_vector->x.list();

	for (auto x = s_vector->x.sorted().begin(); x != s_vector->x.sorted().end(); x++) {
		double y;
		for (auto yi = yv.begin(), xi = xv.begin(); yi != yv.end(); yi++, xi++)
			if (*xi == *x) {
				y = *yi;
				yi = yv.erase(yi);
				xi = xv.erase(xi);
				break;
			}

		for (auto yi = yl.begin(), r = ry.begin(); yi != yl.end(); yi++, r++)
			if (*yi == y) {
				s_value.push_back(*r);
				yi = yl.erase(yi);
				r = ry.erase(r);
			}
	}
}

}
