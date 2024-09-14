#include <vectorPair.hpp>

namespace ss {

double VectorPair::ClassSeries::pdf(double x, double y) {
	return 0;
}

void VectorPair::ClassSeries::adapt() {
	s_value.clear();

	if (!c_countX)
		c_countX = 2*s_vector->x.cs.calculateCount();
	if (!c_countY)
		c_countY = 2*s_vector->y.cs.calculateCount();

	c_stepX = s_vector->x.len()/c_countX;
	c_stepY = s_vector->y.len()/c_countY;

	s_value = std::vector<std::vector<std::pair<std::size_t, double>>>(
		c_countX, 
		std::vector<std::pair<std::size_t, double>>(
			c_countY,
			{0, 0}
		)
	);

	long int x_idx, y_idx;
	auto x_it = s_vector->x.begin();
	auto y_it = s_vector->y.begin();

	while (x_it != s_vector->x.end()) {
		x_idx = (*x_it - s_vector->x.min())/c_stepX;
		if (x_idx >= c_countX)
			x_idx--;

		y_idx = (*y_it - s_vector->y.min())/c_stepY;
		if (y_idx >= c_countY)
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


	c_cumSeries.clear();
	c_cumSeries = std::vector<std::vector<std::pair<std::size_t, double>>>(
		c_countX,
		std::vector<std::pair<std::size_t, double>>(
			c_countY,
			{0, 0}
		)
	);

	c_cumSeries[0][0] = s_value[0][0];
	for (int j = 1; j < c_countY; j++) {
		c_cumSeries[0][j].first = c_cumSeries[0][j-1].first + 
			s_value[0][j].first;
		c_cumSeries[0][j].second = c_cumSeries[0][j-1].second + 
			s_value[0][j].second;
	}
	for (int j = 1; j < c_countX; j++) {
		c_cumSeries[j][0].first = s_value[j][0].first + 
			c_cumSeries[j-1][0].first;
		c_cumSeries[j][0].second = s_value[j][0].second + 
			c_cumSeries[j-1][0].second;
	}
	for (int i = 1; i < c_countX; i++) {
		for (int j = 1; j < c_countY; j++) {
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
