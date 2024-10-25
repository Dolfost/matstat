#include <vectorPair.hpp>

namespace ss {

void VectorPair::reproduceRegression(Regression::Model m) {
	std::vector<double> p;
	switch (m) {
		case (Regression::Model::Linear): {
			double b = cor()*y.sd()/x.sd(), a = y.mean()-b*x.mean();
			p = {a, b};
			break;
		}
		case (Regression::Model::LinearThail): {
			std::list<double> lst;
			auto xi = x.begin(), yi = y.begin();
			while (xi != x.end()) {
			auto xj = std::next(xi), yj = std::next(yi);
				while (xj != x.end()) {
					if (*xi != *xj)
						lst.push_back((*yj - *yi)/(*xj - *xi));
					xj++, yj++;
				}
				xi++, yi++;
			}
			ss::Vector v(lst);
			double b = v.med();

			lst.clear();
			auto xj = x.begin(), yj = y.begin();
			while (xj != x.end()) {
				lst.push_back(*yj - b**xj);
				xj++, yj++;
			}
			v.setVector(lst);
			double a = v.med();
			p = {a, b};
			break;
		}
		case (Regression::Model::Parabolic): {
			double a = y.mean(), b = 0, c = 0, p1 = 0, p2 = 0;
			auto xl = x.begin(), yl = y.begin();
			while (xl != x.end()) {
				b += (*xl - x.mean())**yl;
				double j = x.p2(*xl);
				p1 += j**yl;
				p2 += std::pow(j, 2);
				xl++, yl++;
			}
			b /= (size()-2)*std::pow(x.sd(), 2);
			c = p1/p2;
			p = {a, b, c};
			break;
		}
		case (Regression::Model::QuaziLinear): {
		}
		case (Regression::Model::Unknown):
		case (Regression::Model::Count):
			break;
	};

	reg.setModel(m, p);
}

}
