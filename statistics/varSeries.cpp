#include "varseries.hpp"

#include "dataseries.hpp"
#include <cstddef>
#include <utility>
#include <vector>

VarSeries::VarSeries(DataSeries* ds) {
	dataSeries = ds;
};

bool VarSeries::makeSeries() {
	std::vector<std::vector<double>> data = dataSeries->series();
	double min, max;

	N = dataSeries->size();

	varSeries.clear();

	min = data[0][0];
	max = data[0][0];
	varSeries[data[0][0]].first++;
	for (size_t i = 1; i < data.size(); i++) {
		varSeries[data[i][0]].first++;
		if (data[i][0] < min)
			min = data[i][0];
		else if (data[i][0] > max)
			max = data[i][0];
	}

	xMin = min;
	xMax = max;

	for (auto const& [key, val] : varSeries) {
		varSeries[key].second = varSeries[key].first/double(dataSeries->size());
	}
	
	return true;
}

size_t VarSeries::size() {
	return varSeries.size();
}

int VarSeries::seriesMin() {
	return xMin;
}

int VarSeries::seriesMax() {
	return xMax;
}

int VarSeries::count() {
	return N;
}

std::map<double, std::pair<int, double>>& VarSeries::series() {
	return varSeries;
}
