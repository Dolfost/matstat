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
			ss::VectorPair* goodPair;

			ss::VectorPair weighted(*s_vector), notWeighted(*s_vector);
			weighted.transform(
				/* x = */ "log(x)*x^2/y^2", 
				/* y = */ "log(y)*x^2/y^2"
			);
			notWeighted.transform(
				/* x = */ "log(x)", 
				/* y = */ "log(y)"
			);
			double weightedS = 0, notWeightedS = 0;
			auto wy = weighted.y.begin(), nwy = notWeighted.y.begin();
			while (wy != weighted.y.end()) {
				weightedS += std::pow(*wy - weighted.x.mean(), 2); 
				notWeightedS += std::pow(*nwy - notWeighted.x.mean(), 2); 
				wy++, nwy++;
			}
			weightedS = std::sqrt(weightedS/(v->size()-2));
			notWeightedS = std::sqrt(notWeightedS/(v->size()-2));

			if (weightedS > notWeightedS) {
				goodPair = &notWeighted;
				remDispersion = notWeightedS;
			} else {
				goodPair = &weighted;
				remDispersion = weightedS;
			}

			parametersDeviation.push_back(
				remDispersion*std::sqrt(1.0/v->size() + std::pow(goodPair->x.mean(), 2)/(std::pow(goodPair->x.sd(), 2)*(v->size()-1)))
			);
			parametersDeviation.push_back(
				goodPair->x.mean()*std::sqrt(v->size()-1)/remDispersion
			);

			r_Syx0 = [](double x) {
				return -1000;
			};
			double tm = goodPair->x.mean();
			r_Symx = [v, this, tm](double x) {
				return std::sqrt(std::pow(remDispersion, 2)/v->size() + std::pow(this->parametersDeviation[2]*(x-tm), 2));
			};
			determination = std::pow(goodPair->corRatio(), 2)*100;

			double b = goodPair->cor()*goodPair->y.sd()/goodPair->x.sd();
			double a = std::pow(M_E, goodPair->y.mean() - b*goodPair->x.mean());
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

std::pair<std::list<double>, std::list<double>> VectorPair::Regression::generateSet(
	std::size_t n, double sigma
) {
	std::default_random_engine generator;
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	std::normal_distribution<double> normx(0, 1);
	std::normal_distribution<double> norm(0, sigma);

	std::list<double> x, y;
	for (std::size_t i = 0; i < n; i++) {
		x.push_back(normx(generator));
		y.push_back(regression(x.back()) + norm(generator));
	}

	return {x, y};
};

const std::vector<std::string> VectorPair::Regression::regressionName = {
	"Невідома", "Лінійна (a+bx)", "Параболічна (a+bx+cx²)", "Квазілінійна (axᵇ)",
};

const std::vector<std::vector<std::string>> VectorPair::Regression::parameterName = {
	{}, {"a", "b"}, {"a", "b", "c"}, {"a", "b"},
};

}
