#ifndef _VARSERIES_HPP_
#define _VARSERIES_HPP_

#include <map>

#include "dataVector.hpp"

class DataVector::VarSeries {
public:
	VarSeries(DataVector*);

	bool makeSeries();
	std::map<double, std::pair<int, double>>& series();
	size_t variantsCount(); // r 

	DataVector* dataVector = nullptr; // plain vector data
private:
	// has size of r; varSeries[x_i].first = n_i, varSeries[x_i].second = p_i
	std::map<double, std::pair<int, double>> varSeries; 
	double seriesMin; // x_min
	double seriesMax; // x_max
	size_t seriesSize; // N
	size_t seriesVariants; // r

};

#endif // !_VARSERIES_HPP_
