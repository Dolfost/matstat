#include "varSeries.hpp"

namespace ss {

Vector::VarSeries::VarSeries(Vector* ds) {
	dataVector = ds;
};

bool Vector::VarSeries::makeSeries() {
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

size_t Vector::VarSeries::variantsCount() {
	return seriesVariants;
}

std::map<double, std::pair<int, double>>&
Vector::VarSeries::series() {
	return varSeries;
}

}
