#ifndef _CLASSSERIES_HPP_
#define _CLASSSERIES_HPP_

#include "dataVector.hpp"

class DataVector::ClassSeries {
public:
	ClassSeries (DataVector*);
	bool makeSeries(unsigned short = 0);

	const std::vector<std::pair<int, double>>& series();
	const std::vector<std::pair<int, double>>& cumSeries();

	double eCdf(double);
	double ePdf(double);

public: // properties
	double step(); // h
	double maxIntervalProbability(); // max P_i
	size_t maxIntervalCount(); // max N_i
	size_t classCount(); // M
	size_t calculateClassCount();

private:
	// iterates as x = (h+0.5)i; i is the vector index
	// has size of M for O(n) access speed
	std::vector<std::pair<int, double>> classSeries; 
	std::vector<std::pair<int, double>> cumulativeSeries; 

	DataVector* dataVector = nullptr;

	size_t clsCnt; // M
	double maxIntProb; // max P_i
	size_t maxIntCnt; // max N_i
	double h; // h
};

#endif // !_CLASSSERIES_HPP_
