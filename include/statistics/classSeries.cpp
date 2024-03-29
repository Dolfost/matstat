#include <QDebug>
#include <QtCore/qalgorithms.h>

#include "classSeries.hpp"
DataVector::ClassSeries::ClassSeries(DataVector* vs) {
	dataVector = vs;
}

bool DataVector::ClassSeries::makeSeries(unsigned short cc) {
	if (dataVector->size() == 0) {
		classSeries = {};
		return false;
	}

	if (cc == 0) {
		clsCnt = calculateClassCount();
	} else {
		clsCnt = cc;
	}
	
	double seriesMin = dataVector->min();
	double seriesMax = dataVector->max();
	double entryCount = dataVector->size();


	classSeries.clear();

	h = (dataVector->max()-dataVector->min())/double(clsCnt);

	classSeries.resize(clsCnt);
	cumulativeSeries.resize(clsCnt);

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
	for (int i = 1; i < clsCnt; i++) {
		if (classSeries[i].first > maxIntCnt)
			maxIntCnt = classSeries[i].first;
		if (classSeries[i].second > maxIntProb)
			maxIntProb = classSeries[i].second;

		cumulativeSeries[i].first += cumulativeSeries[i-1].first;
		cumulativeSeries[i].second += cumulativeSeries[i-1].second;
	}

	return true;
}

size_t DataVector::ClassSeries::calculateClassCount() {
	size_t cls = dataVector->size() >= 100 ?
			cbrt(dataVector->size()) : sqrt(dataVector->size());
	if (cls % 2 == 0)
		cls--;

	return cls;
}

double DataVector::ClassSeries::eCdf(double x) {
	if (x < dataVector->min())
		return 0;
	if (x > dataVector->max())
		return 1;

	size_t idx = (x - dataVector->min())/h;
	if (idx >= clsCnt)
		idx--;

	return cumulativeSeries[idx].second;
}

double DataVector::ClassSeries::ePdf(double x) {
	if (x < dataVector->min())
		return 0;
	if (x > dataVector->max())
		return 1;

	size_t idx = (x - dataVector->min())/h;
	if (idx >= clsCnt)
		idx--;

	return classSeries[idx].second;
}

const std::vector<std::pair<int, double>>& 
DataVector::ClassSeries::series() {
	return classSeries;
}

const std::vector<std::pair<int, double>>& 
DataVector::ClassSeries::cumSeries() {
	return cumulativeSeries;
}

double DataVector::ClassSeries::step() {
	return h;
}

size_t DataVector::ClassSeries::maxIntervalCount() {
	return maxIntCnt;
}

double DataVector::ClassSeries::maxIntervalProbability() {
	return maxIntProb;
}

size_t DataVector::ClassSeries::classCount() {
	return clsCnt;
}
