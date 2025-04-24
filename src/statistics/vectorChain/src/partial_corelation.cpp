#include <vectorChain.hpp> 

#include <vectorChain/math.hpp> 

namespace ss {

inline double corr(double r_ij, double r_id, double r_jd){
	return (r_ij - r_id*r_jd)/std::sqrt((1-r_id*r_id)*(1 - r_jd*r_jd));
}

double rec(VectorChain* vc, std::size_t i, std::size_t j, std::vector<std::size_t> c, std::size_t d) {
	if (c.size() == 0)
		return corr((*vc).r()[i][j], (*vc).r()[i][d], (*vc).r()[j][d]);

	int d1 = c.back();
	c.pop_back();

	double first = rec(vc, i, j, c, d1);
	double second = rec(vc, i, d, c, d1);
	double third = rec(vc, j, d, c, d1);

	double numerator = first - second*third;
	double denominator = std::sqrt(std::abs((1 - std::pow(second, 2)) * (1 - std::pow(third, 2))));

	return numerator / denominator;
}

void VectorChain::PartialCorelationRatio::adapt(std::tuple<std::size_t, std::size_t, std::vector<std::size_t>> t) {
	auto t_orig = t;
	std::size_t& i = std::get<0>(t);
	std::size_t& j = std::get<1>(t);
	std::vector<std::size_t>& c = std::get<2>(t);

	if (c.size() == 0) {
		s_values[t] = s_vector->r()[i][j];
		return;
	}

	std::size_t d = c.back();
	c.pop_back();
	s_values[t_orig] = rec(s_vector, i, j, c, d);
}

}
