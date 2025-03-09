#include <vectorPair.hpp>
#include <iostream>

namespace ss {

void VectorPair::Ranks::adapt() {
	std::vector<double> yl = s_vector->y.sorted();
	std::vector<double> ry = s_vector->y.ranks();

	std::vector<double> yv = s_vector->y.list();
	std::vector<double> xv = s_vector->x.list();

	for (auto x = s_vector->x.sorted().begin(); x != s_vector->x.sorted().end(); x++) {
		double y;

		auto yi = yv.begin(), xi = xv.begin();
		while (yi != yv.end() && xi != xv.end()) {
			if (*xi == *x) {
				y = *yi;
				yi = yv.erase(yi);
				xi = xv.erase(xi);
				break;
			} else {
				++yi;
				++xi;
			}
		}

		auto r = ry.begin();
		yi = yl.begin();
		while (yi != yl.end() && r != ry.end()) {
			if (*yi == y) {
				s_value.push_back(*r);
				yi = yl.erase(yi);
				r = ry.erase(r);
			} else {
				++yi;
				++r;
			}
		}
	}
}

}
