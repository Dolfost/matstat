#include <QDebug>
#include <QtCore/qalgorithms.h>

#include "classSeries.hpp"

namespace ss {

Vector::ClassSeries::ClassSeries(Vector* vs) {
	vector = vs;
}

bool Vector::ClassSeries::makeSeries(unsigned short cc) {
	if (vector->size() == 0) {
		classSeries = {};
		return false;
	}

	if (cc == 0) {
		clsCnt = calculateClassCount();
	} else {
		clsCnt = cc;
	}
	
	double seriesMin = vector->min();
	double seriesMax = vector->max();
	double entryCount = vector->size();


	classSeries.clear();
	cumulativeSeries.clear();

	h = (vector->max()-vector->min())/double(clsCnt);

	classSeries.resize(clsCnt);
	cumulativeSeries.resize(clsCnt);

	int idx;
	for (auto const& i : vector->vector()) {
		idx = (i - vector->min())/h;
		if (idx >= clsCnt)
			idx--;
		classSeries[idx].first++;
	}

	for (auto& i : classSeries) {
		i.second = i.first/double(entryCount);
	}

	maxIntCnt = classSeries[0].first;
	maxIntProb = classSeries[0].second;
	cumulativeSeries[0] = classSeries[0];
	for (int i = 1; i < clsCnt; i++) {
		if (classSeries[i].first > maxIntCnt)
			maxIntCnt = classSeries[i].first;
		if (classSeries[i].second > maxIntProb)
			maxIntProb = classSeries[i].second;

		cumulativeSeries[i].first += cumulativeSeries[i-1].first +
			classSeries[i].first;
		cumulativeSeries[i].second += cumulativeSeries[i-1].second +
			classSeries[i].second;
	}

	return true;
}

size_t Vector::ClassSeries::calculateClassCount() {
	size_t cls = vector->size() >= 100 ?
			cbrt(vector->size()) : sqrt(vector->size());
	if (cls % 2 == 0)
		cls--;

	return cls;
}

double Vector::ClassSeries::eCdf(double x) {
	if (x < vector->min())
		return 0;
	if (x > vector->max())
		return 1;

	size_t idx = (x - vector->min())/h;
	if (idx >= clsCnt)
		idx--;

	return cumulativeSeries[idx].second;
}

double Vector::ClassSeries::ePdf(double x) {
	if (x < vector->min())
		return 0;
	if (x > vector->max())
		return 1;

	size_t idx = (x - vector->min())/h;
	if (idx >= clsCnt)
		idx--;

	return classSeries[idx].second;
}

const std::vector<std::pair<int, double>>& 
Vector::ClassSeries::series() {
	return classSeries;
}

const std::vector<std::pair<int, double>>& 
Vector::ClassSeries::cumSeries() {
	return cumulativeSeries;
}

double Vector::ClassSeries::step() {
	return h;
}

size_t Vector::ClassSeries::maxIntervalCount() {
	return maxIntCnt;
}

double Vector::ClassSeries::maxIntervalProbability() {
	return maxIntProb;
}

size_t Vector::ClassSeries::classCount() {
	return clsCnt;
}

}
