#include <vectorChain.hpp> 

#include <vectorChain/math.hpp> 

namespace ss {

inline double partialCorelationRatio(double r_i_j, double r_i_d, double r_j_d){
	return (r_i_j - r_i_d*r_j_d)/std::sqrt((1-r_i_d*r_i_d)*(1 - r_j_d*r_j_d));
}

double rec(VectorChain* vc, std::size_t i, std::size_t j, std::vector<std::size_t> c, std::size_t d) {
    if (c.size() == 0) {
        return partialCorelationRatio((*vc)[i][j], (*vc)[i][d], (*vc)[j][d]);
    }

    int newD = c.back();
    c.pop_back();

    double first = rec(vc, i, j, c, newD);
    double second = rec(vc, i, d, c, newD);
    double third = rec(vc, j, d, c, newD);

    double numerator = first - second*third;
    double denominator = std::sqrt(std::abs((1 - std::pow(second, 2)) * (1 - std::pow(third, 2))));

    return numerator / denominator;
}

void VectorChain::PartialCorelationRatio::adapt(std::tuple<std::size_t, std::size_t, std::vector<std::size_t>, std::size_t> t) {
	s_values[t] = rec(s_vector, std::get<0>(t), std::get<1>(t), std::get<2>(t), std::get<3>(t));
}

}
