#include <vectorPair.hpp>
#include <vector/quantile.hpp>

namespace ss {

void VectorPair::Regression::setModel(Model m, std::vector<double> p) {
	paremeterNames.clear();
	parametersDeviationNames.clear();
	parameters.clear();
	parametersDeviation.clear();

	parameters = p;
	model = m;

	ss::VectorPair& v = *s_vector;

	switch (model) {
		case Model::Linear: {
			double a = p[0], b = p[1];
			remDispersion = v.y.sd()*std::sqrt((1-std::pow(v.cor(), 2)))*(v.size()-1)/(v.size()-2);
			parametersDeviation.push_back(
				remDispersion*std::sqrt(1.0/v.size()+std::pow(v.x.mean(), 2)/(std::pow(v.x.sd(), 2)*(v.size() - 1)))
			);
			parametersDeviation.push_back(
				remDispersion/(v.x.sd()*std::sqrt(v.size() - 1))
			);
			r_regression = [a, b](double x) {
				return a + x*b;
			};
			r_tolerance = [this](double x) -> std::pair<double, double> {
				double f = this->f(x), q = ss::studQuantile(1-this->d_confidence/2, this->s_vector->size()-2)*this->remDispersion;
				return {f - q, f + q};
			};
			r_Syx0 = [this](double x) {
				return std::sqrt(this->remDispersion*(1+1.0/this->s_vector->size()) + 
										 std::pow(this->parametersDeviation[1], 2)*std::pow(x - this->s_vector->x.mean(), 2));
			};
			r_forecast = [this](double x) -> std::pair<double, double> {
				double f = this->f(x), q = ss::studQuantile(1-this->d_confidence/2, this->s_vector->size()-2)*this->Syx0(x);
				return {f - q, f + q};
			};
			r_Symx = [this](double x) {
				return std::sqrt(std::pow(this->remDispersion, 2)/this->s_vector->size() +
										 std::pow(this->parametersDeviation[1]*(x-this->s_vector->x.mean()), 2));
			};
			r_confidence = [this](double x) -> std::pair<double, double> {
				double f = this->f(x), q = ss::studQuantile(1-this->d_confidence/2, this->s_vector->size()-2)*this->Symx(x);
				return {f - q, f + q};
			};
			determination = std::pow(v.cor(), 2)*100;
			break;
		}
		case Model::Parabolic: {

			break;
		}
		case Model::Unknown: {

			break;
		}
		case Model::Count:
			break;
	}

	parametersCount = p.size();
	paremeterNames = parameterName[(int)model];
	parametersDeviationNames = parameterName[(int)model];
}

const std::vector<std::string> VectorPair::Regression::regressionName = {
	"Невідома", "Лінійна", "Параболічна",
};

const std::vector<std::vector<std::string>> VectorPair::Regression::parameterName = {
	{}, {"a", "b"}, {"a", "b", "c"},
};

}
