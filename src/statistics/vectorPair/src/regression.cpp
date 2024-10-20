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
		case Model::Unknown:
		case Model::Count:
			break;
	}

	parametersCount = p.size();
	paremeterNames = parameterName[(int)model];
	parametersDeviationNames = parameterName[(int)model];
}

std::pair<std::list<double>, std::list<double>> VectorPair::Regression::generateSet(
	std::size_t n, double a, double b, double sigma
) {
	std::default_random_engine generator;
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<double> uni(a, b);
	std::normal_distribution<double> norm(0, sigma);

	std::list<double> x, y;
	for (std::size_t i = 0; i < n; i++) {
		x.push_back(uni(generator));
		y.push_back(regression(x.back()) + norm(generator));
	}

	return {x, y};
};

const std::vector<std::string> VectorPair::Regression::regressionName = {
	"Невідома", "Лінійна", "Параболічна",
};

const std::vector<std::vector<std::string>> VectorPair::Regression::parameterName = {
	{}, {"a", "b"}, {"a", "b", "c"},
};

}
