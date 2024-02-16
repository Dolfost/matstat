#ifndef _CLASSSERIES_HPP_
#define _CLASSSERIES_HPP_

#include "varseries.hpp"

class ClassSeries {
public:
	ClassSeries (VarSeries*);

	bool makeSeries(unsigned short = 0);
	std::vector<std::pair<int, double>> series();
	unsigned short classCount();
	double step();
	int seriesMin(); // x_min
	int seriesMax(); // x_max

	~ClassSeries();
private:
	// iterates as x = (h+0.5)i; i is the vector index
	std::vector<std::pair<int, double>> classSeries; 

	VarSeries* varSeries = nullptr;
	unsigned short clsCnt = 0; // M
	double xMin; // x_min
	double xMax; // x_max
	double h = 0; // h
};

#endif // !_CLASSSERIES_HPP_
