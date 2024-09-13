#include "vector.hpp"

namespace ss {

void Vector::ClassSeries::adapt() {
	if (c_count == 0)
		c_count = calculateCount();
	
	double seriesMin = s_vector->min();
	double seriesMax = s_vector->max();
	double entryCount = s_vector->size();

	c_h = (s_vector->max()-s_vector->min())/double(c_count);

	s_value.clear();
	c_cumSeries.clear();
	s_value.resize(c_count);
	c_cumSeries.resize(c_count);



	int idx;
	for (auto const& i : s_vector->sorted()) {
		idx = (i - s_vector->min())/c_h;
		if (idx >= c_count)
			idx--;
		s_value[idx].first++;
	}

	for (auto& i : s_value) {
		i.second = i.first/double(entryCount);
	}

	c_maxCount = s_value[0].first;
	c_maxProb = s_value[0].second;
	c_cumSeries[0] = s_value[0];
	for (int i = 1; i < c_count; i++) {
		if (s_value[i].first > c_maxCount)
			c_maxCount = s_value[i].first;
		if (s_value[i].second > c_maxProb)
			c_maxProb = s_value[i].second;

		c_cumSeries[i].first += c_cumSeries[i-1].first +
			s_value[i].first;
		c_cumSeries[i].second += c_cumSeries[i-1].second +
			s_value[i].second;
	}
}

std::size_t Vector::ClassSeries::calculateCount() {
	std::size_t cls = (s_vector->size() >= 100 ?
		std::cbrt(s_vector->size()) : std::sqrt(s_vector->size()));
	if (cls % 2 == 0)
		cls--;

	return cls;
}

double Vector::ClassSeries::cdf(double x) {
	auto cumS = cumSeries();
	if (x < s_vector->min())
		return 0;
	if (x > s_vector->max())
		return 1;

	std::size_t idx = (x - s_vector->min())/c_h;
	if (idx >= c_count)
		idx--;

	return cumS[idx].second;
}

double Vector::ClassSeries::pdf(double x) {
	auto s = series();
	if (x < s_vector->min())
		return 0;
	if (x > s_vector->max())
		return 1;

	std::size_t idx = (x - s_vector->min())/c_h;
	if (idx >= c_count)
		idx--;

	return s[idx].second;
}

std::size_t Vector::ClassSeries::setCount(std::size_t c) {
	std::size_t old = c_count;
	c_count = c;
	invalidate();
	return old;
}
double Vector::ClassSeries::step() {
	if (!s_valid)
		adapt();
	return c_h;
}

std::size_t Vector::ClassSeries::count() {
	if (!s_valid)
		adapt();
	return c_count;
}

}
