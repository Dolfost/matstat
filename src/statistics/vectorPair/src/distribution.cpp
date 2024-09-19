#include <vectorPair.hpp>

#include <random>

namespace ss {
const std::vector<std::vector<std::string>> VectorPair::Distribution::parameterName = {
	{"mₓ", "mᵧ", "σₓ", "σᵧ", "rₓᵧ"},
};

void VectorPair::Distribution::setDistribution(std::vector<double> p, size_t s) {
	size = s;

	paremeterNames.clear();
	parameters.clear();

	parametersCount = 5;
	paremeterNames = {"mₓ", "mᵧ", "σₓ", "σᵧ" "rₓᵧ"};
	parameters = p;

	double mx = parameters[0], my = parameters[1],
		ox = parameters[2], oy = parameters[3],
		r = parameters[4];

	d_pdf = [mx, my, ox, oy, r](double x, double y) { 
		return (1/(6.2831853072*ox*oy*std::sqrt(1-std::pow(r, 2)))) * 
			std::exp(-(1/(2*(1-std::pow(r, 2))))*(std::pow((x - mx)/ox, 2) - 2*r*((x-mx)/ox)*((y-my)/oy) + std::pow((y-my)/oy, 2)));
	};
}

double VectorPair::Distribution::pdf(double x, double y) {
	return d_pdf(x, y);
}

std::pair<std::list<double>, std::list<double>> VectorPair::Distribution::generateSet(std::size_t size) {
  std::default_random_engine generator;
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
  std::normal_distribution<double> distribution(0, 1);

	double number = distribution(generator);

	double mx = parameters[0], my = parameters[1],
		ox = parameters[2], oy = parameters[3],
		r = parameters[4];
	std::list<double> xl, yl;

	for (std::size_t i = 0; i < size; i++) {
		double z1 = distribution(generator),
			z2 = distribution(generator);
		xl.push_back(mx + ox*z1);
		yl.push_back(my + oy*(z2*std::sqrt(1-std::pow(r, 2)) + z1*r));
	}

	return {std::move(xl), std::move(yl)};
};

};
