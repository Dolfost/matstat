#include "varSeries.hpp"

#include <cstddef>
#include <utility>

VarSeries::VarSeries(DataVector* ds) {
	dataVector = ds;
};

bool VarSeries::makeSeries() {
	std::list<double> vector = dataVector->vector();

	seriesSize = dataVector->size();
	seriesMin = dataVector->min();
	seriesMax = dataVector->max();

	for (auto const& i : vector) {
		varSeries[i].first++;
	}

	for (auto const& [key, val] : varSeries) {
		varSeries[key].second = varSeries[key].first/double(dataVector->size());
	}

	seriesVariants = varSeries.size();
	
	return true;
}

size_t VarSeries::variantsCount() {
	return seriesVariants;
}

std::map<double, std::pair<int, double>>& VarSeries::series() {
	return varSeries;
}
