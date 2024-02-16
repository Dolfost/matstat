#ifndef _CLASSSERIES_HPP_
#define _CLASSSERIES_HPP_

#include "dataVector.hpp"

class ClassSeries {
public:
	ClassSeries (DataVector*);

	bool makeSeries(unsigned short = 0);
	std::vector<std::pair<int, double>> series();

	DataVector* dataVector = nullptr;

	// properties
	double step(); // h
	double maxIntervalProbability(); // max P_i
	size_t maxIntervalCount(); // max N_i
	size_t classCount(); // M
	
	
	~ClassSeries();
private:
	// iterates as x = (h+0.5)i; i is the vector index
	// has size of M for O(n) access speed
	std::vector<std::pair<int, double>> classSeries; 

	size_t clsCnt; // M
	double maxIntProb; // max P_i
	size_t maxIntCnt; // max N_i
	double h; // h
};

#endif // !_CLASSSERIES_HPP_
