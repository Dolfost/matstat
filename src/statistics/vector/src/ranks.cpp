#include <vector.hpp>

#include <numeric>

namespace ss {

void Vector::Ranks::adapt() {
	std::size_t idx = 1;
	for (auto x = s_vector->sorted().begin(); x != s_vector->sorted().end(); x++) {
		std::list<std::size_t> idxList = {idx};
		std::size_t rep = 1;
		while (std::next(x) != s_vector->sorted().end() and *std::next(x) == *x) {
			idxList.push_back(++idx);
			x++; rep++;
		}

		if (rep > 1)
			r_links.push_back(rep);

		double rank = std::accumulate(idxList.begin(), idxList.end(), 0.0) / idxList.size();
		for (int i = 0; i < rep; i++)
			s_value.push_back(rank);
		
		idx++;
	}
}

}
