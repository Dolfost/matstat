#include <vectorPair.hpp>
#include <vector/quantile.hpp>

namespace ss {

void VectorPair::Regression::setModel(Model m, std::vector<double> p) {
	paremeterNames.clear();
	parametersDeviationNames.clear();
	parametersDeviation.clear();

	parameters = p;
	model = m;
	ss::VectorPair* v = s_vector;

	switch (model) {
		case Model::LinearThail:
		case Model::Linear: {
			double a = p[0], b = p[1];
			r_regression = [a, b](double x) {
				return a + x*b;
			};

			if (!v)
				return;

			remDispersion = v->y.sd()*std::sqrt((1-std::pow(v->cor(), 2)))*(v->size()-1)/(v->size()-2);
			parametersDeviation.push_back(
				remDispersion*std::sqrt(1.0/v->size()+std::pow(v->x.mean(), 2)/(std::pow(v->x.sd(), 2)*(v->size() - 1)))
			);
			parametersDeviation.push_back(
				remDispersion/(v->x.sd()*std::sqrt(v->size() - 1))
			);
			r_Syx0 = [this](double x) {
				return std::sqrt(this->remDispersion*(1+1.0/this->s_vector->size()) + 
										 std::pow(this->parametersDeviation[1], 2)*std::pow(x - this->s_vector->x.mean(), 2));
			};
			r_Symx = [this](double x) {
				return std::sqrt(std::pow(this->remDispersion, 2)/this->s_vector->size() +
										 std::pow(this->parametersDeviation[1]*(x-this->s_vector->x.mean()), 2));
			};
			determination = std::pow(v->cor(), 2)*100;
			break;
		}
		case Model::Parabolic: {
			double a = p[0], b = p[1], c = p[2];
			if (!v) {
				r_regression = [a, b, c](double x) {
					return a + x*b + std::pow(x, 2)*c;
				};
				return;
			} else
				r_regression = [a, b, c, v](double x) {
					return a + v->x.p1(x)*b + v->x.p2(x)*c;
				};

			remDispersion = 0;
			double p2mean2 = 0;
			auto xl = v->x.begin(), yl = v->y.begin();
			while (xl != v->x.end()) {
				remDispersion += std::pow(*yl - a - b*v->x.p1(*xl) - c*v->x.p2(*xl), 2);
				p2mean2 += std::pow(v->x.p2(*xl), 2);
				xl++, yl++;
			}
			remDispersion /= v->size()-3;
			p2mean2 /= (v->size()-2);
			remDispersion = std::sqrt(remDispersion);
			
			parametersDeviation.push_back(
				remDispersion/std::sqrt(v->size())
			);
			parametersDeviation.push_back(
				remDispersion/(v->x.sd()*std::sqrt(v->size()))
			);
			parametersDeviation.push_back(
				remDispersion/std::sqrt(v->size()*p2mean2)
			);

			r_Syx0 = [v, this, p2mean2](double x) {
				return (this->remDispersion/std::sqrt(v->size())) * 
				std::sqrt(v->size() + 1 + std::pow(v->x.p1(x), 2)/v->x.sd() + 
							std::pow(v->x.p2(x), 2)/p2mean2);
			};
			r_Symx = [v, this, p2mean2](double x) {
				return (this->remDispersion/std::sqrt(v->size())) * 
				std::sqrt(1 + std::pow(v->x.p1(x), 2)/v->x.sd() + 
							std::pow(v->x.p2(x), 2)/p2mean2);
			};
			determination = std::pow(v->corRatio(), 2)*100;
			break;
		}
		case Model::QuaziLinear: {
			if (!v and p.size() != 0) {
				double a = p[0], b = p[1];
				r_regression = [a, b](double x) {
					return a*std::pow(x, b);
				};
				return;
			}

			ss::VectorPair trans(*s_vector);
			trans.transform(
				/* x = */ "log(x)", 
				/* y = */ "log(y)"
			);
			double phi = 0, psi = 0, phi2 = 0, phiPsi = 0, w = 0;

			for (auto xl = trans.x.begin(), yl = trans.y.begin(); xl != trans.x.end(); xl++, yl++) {
				double wl = std::pow(*yl / *xl, 2);
				w += wl;
				phi += *xl*wl;
				psi += *yl*wl;
				phi2 += std::pow(*xl, 2)*wl;
				phiPsi += *xl**yl*wl;
			}
			phi /= w, psi /= w, phi2 /= w, phiPsi /= w;
			double B = (phiPsi - phi*psi)/(phi2 - std::pow(phi, 2)), A = psi - B*phi, 
			b = trans.cor()*trans.y.sd()/trans.x.sd(), a = trans.y.mean() - b*trans.x.mean(); 

			double weightedS = 0, notWeightedS = 0;
			for (auto xl = trans.x.begin(), yl = trans.y.begin(); xl != trans.x.end(); xl++, yl++) {
				weightedS += std::pow(*yl - A - B**xl, 2);
				notWeightedS += std::pow(*yl - a - b**xl, 2);
			}

			if (weightedS > notWeightedS)
				a = A, b = B;

			parametersDeviation.push_back(
				remDispersion*std::sqrt(1.0/v->size() + std::pow(trans.x.mean(), 2)/(std::pow(trans.x.sd(), 2)*(v->size()-1)))
			);
			parametersDeviation.push_back(
				trans.x.mean()*std::sqrt(v->size()-1)/remDispersion
			);

			r_Syx0 = [](double x) {
				return -1000;
			};
			double tm = trans.x.mean();
			r_Symx = [v, this, tm](double x) {
				return std::sqrt(std::pow(remDispersion, 2)/v->size() + std::pow(this->parametersDeviation[2]*(x-tm), 2));
			};
			determination = std::pow(trans.corRatio(), 2)*100;

			b = trans.cor()*trans.y.sd()/trans.x.sd();
			a = std::pow(M_E, trans.y.mean() - b*trans.x.mean());
			parameters.push_back(a);
			parameters.push_back(b);
			r_regression = [a, b](double x) {
				return a*std::pow(x, b);
			};
		};
		case Model::Unknown:
		case Model::Count:
			break;
	}

	parametersCount = parameters.size();
	paremeterNames = parameterName[(int)model];
	parametersDeviationNames = parameterName[(int)model];
}

std::pair<std::vector<double>, std::vector<double>> VectorPair::Regression::generateSet(
	std::size_t n, double sigma
) {
	std::default_random_engine generator;
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	std::normal_distribution<double> normx(0, 1);
	std::normal_distribution<double> norm(0, sigma);

	std::vector<double> x, y;
	for (std::size_t i = 0; i < n; i++) {
		x.push_back(normx(generator));
		y.push_back(regression(x.back()) + norm(generator));
	}

	return {x, y};
};

const std::vector<std::string> VectorPair::Regression::regressionName = {
	"Невідома", "Лінійна (a+bx)", "Лінійна за Тейлом (a+bx)", "Параболічна (a+bx+cx²)", "Квазілінійна (axᵇ)",
};

const std::vector<std::vector<std::string>> VectorPair::Regression::parameterName = {
	{}, {"a", "b"}, {"a", "b"}, {"a", "b", "c"}, {"a", "b"},
};

}
