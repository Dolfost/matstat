#include <QDebug>

#include "classSeries.hpp"
ClassSeries::ClassSeries(DataVector* vs) {
	dataVector = vs;
}

bool ClassSeries::makeSeries(unsigned short cc) {
	if (dataVector->size() == 0) {
		classSeries = {};
		return false;
	}

	if (cc == 0) {
		clsCnt = dataVector->size() >= 100 ?
				cbrt(dataVector->size()) : sqrt(dataVector->size());
		if (clsCnt % 2 == 0)
			clsCnt--;
	} else {
		clsCnt = cc;
	}
	
	double seriesMin = dataVector->min();
	double seriesMax = dataVector->max();
	double entryCount = dataVector->size();


	classSeries.clear();

	h = (dataVector->max()-dataVector->min())/double(clsCnt);

	classSeries.resize(clsCnt);

	int idx;
	for (auto const& i : dataVector->vector()) {
		idx = (i - dataVector->min())/h;
		if (idx >= clsCnt)
			idx--;
		classSeries[idx].first++;
	}

	for (auto& i : classSeries) {
		i.second = i.first/double(entryCount);
	}


	maxIntCnt = classSeries[0].first;
	maxIntProb = classSeries[0].second;
	for (int i = 1; i < classSeries.size(); i++) {
		if (classSeries[i].first > maxIntCnt)
			maxIntCnt = classSeries[i].first;
		if (classSeries[i].second > maxIntProb)
			maxIntProb = classSeries[i].second;
	}

	return true;
}

const std::vector<std::pair<int, double>>& ClassSeries::series() {
	return classSeries;
}

double ClassSeries::step() {
	return h;
}

size_t ClassSeries::maxIntervalCount() {
	return maxIntCnt;
}

double ClassSeries::maxIntervalProbability() {
	return maxIntProb;
}

size_t ClassSeries::classCount() {
	return clsCnt;
}
