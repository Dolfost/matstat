#ifndef _VARSERIES_HPP_
#define _VARSERIES_HPP_

#include <map>
#include <utility>

#include "dataseries.hpp"

class VarSeries {
public:
	VarSeries(DataSeries*);

	bool makeSeries();
	std::map<double, std::pair<int, double>>& series();
	size_t size(); // r 
	int seriesMin(); // x_min
	int seriesMax(); // x_max
	int count(); // N

	~VarSeries();
private:
	// has size of r; varSeries[x_i].first = n_i, varSeries[x_i].second = p_i
	std::map<double, std::pair<int, double>> varSeries; 
	double xMin; // x_min
	double xMax; // x_max
	int N;

	DataSeries* dataSeries = nullptr; // plain vector data
};

#endif // !_VARSERIES_HPP_
