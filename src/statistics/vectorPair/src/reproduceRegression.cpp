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
		case (Regression::Model::Parabolic): {

			break;
		}
		case (Regression::Model::Unknown): {
			break;
		}
		case (Regression::Model::Count):
			break;
	};

	reg.setModel(m, p);
}

}
