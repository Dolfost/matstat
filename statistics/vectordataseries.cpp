#include "vectordataseries.hpp"

VectorDataSeries::VectorDataSeries(std::vector<double>& input) {
	vectorDataSeries = input;
}

size_t VectorDataSeries::size() {
	return vectorDataSeries.size();
}
