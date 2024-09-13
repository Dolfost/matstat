#include <vectorPair.hpp>

namespace ss {

double VectorPair::ClassSeries::pdf(double x, double y) {
	return 0;
}

void VectorPair::ClassSeries::adapt() {
	s_value.clear();
	s_value = std::vector<std::vector<std::pair<std::size_t, double>>>(
		s_vector->x.cs.count(), 
		std::vector<std::pair<std::size_t, double>>(
			s_vector->y.cs.count(),
			{0, 0}
		)
	);

	std::size_t x_idx, y_idx;
	auto x_it = s_vector->x.begin();
	auto y_it = s_vector->y.begin();
	while (x_it != s_vector->x.end()) {
		x_idx = (*x_it - s_vector->x.min())/s_vector->x.cs.step();
		if (x_idx >= s_vector->x.cs.count())
			x_idx--;

		y_idx = (*y_it - s_vector->y.min())/s_vector->y.cs.step();
		if (y_idx >= s_vector->y.cs.count())
			y_idx--;

		s_value[x_idx][y_idx].first++;
		y_it++;
		x_it++;
	}

	c_maxCount = s_value[0][0].first;
	c_maxProb = s_value[0][0].second;
	for (auto& vv : s_value) {
		for (auto& v : vv) {
			v.second = double(v.first)/s_vector->x.size();
			if (v.first > c_maxCount)
				c_maxCount = v.first;
			if (v.second > c_maxProb)
				c_maxProb = v.second;
		}
	}

	c_cumSeries = std::vector<std::vector<std::pair<std::size_t, double>>>(
		s_vector->x.cs.count(), 
		std::vector<std::pair<std::size_t, double>>(
			s_vector->y.cs.count(),
			{0, 0}
		)
	);

	c_cumSeries[0][0] = s_value[0][0];
	for (int j = 1; j < s_vector->y.cs.count(); j++) {
		c_cumSeries[0][j].first = c_cumSeries[0][j-1].first + 
			s_value[0][j].first;
		c_cumSeries[0][j].second = c_cumSeries[0][j-1].second + 
			s_value[0][j].second;
	}
	for (int j = 1; j < s_vector->y.cs.count(); j++) {
		c_cumSeries[0][j].first = s_value[0][j].first + 
			c_cumSeries[0][j-1].first;
		c_cumSeries[0][j].second = s_value[0][j].second + 
			c_cumSeries[0][j-1].second;
	}
	for (int i = 1; i < s_vector->x.cs.count(); i++) {
		for (int j = 1; j < s_vector->y.cs.count(); j++) {
			c_cumSeries[i][j].first = c_cumSeries[i-1][j].first +
				c_cumSeries[i][j-1].first + s_value[i][j].first - 
				c_cumSeries[i-1][j-1].first;
			c_cumSeries[i][j].second = c_cumSeries[i-1][j].second +
				c_cumSeries[i][j-1].second + s_value[i][j].second - 
				c_cumSeries[i-1][j-1].second;
		}
	}
}

}
