#include <QDebug>

#include "classseries.hpp"


ClassSeries::ClassSeries(VarSeries* vs) {
	varSeries = vs;
}

bool ClassSeries::makeSeries(unsigned short cc) {
	if (cc == 0) {
		clsCnt = varSeries->count() >= 100 ?
				cbrt(varSeries->count()) : sqrt(varSeries->count());
		if (clsCnt % 2 == 0)
			clsCnt--;
	} else {
		clsCnt = cc;
	}

	xMin = varSeries->seriesMin();
	xMax = varSeries->seriesMax();

	classSeries.clear();

	h = (varSeries->seriesMax()-varSeries->seriesMin())/double(clsCnt);

	classSeries.resize(clsCnt);

	int idx;
	for (auto const& [key, val] : varSeries->series()) {
		idx = int(key - varSeries->seriesMin())/h;
		if (idx == clsCnt) {
			idx--;
		}
		classSeries[idx].first +=
			varSeries->series()[key].first;
		classSeries[idx].second +=
			varSeries->series()[key].second;
	}

	return true;
}

std::vector<std::pair<int, double>> ClassSeries::series() {
	return classSeries;
}

double ClassSeries::step() {
	return h;
}

int ClassSeries::seriesMin() {
	return xMin;
}

int ClassSeries::seriesMax() {
	return xMax;
}

unsigned short ClassSeries::classCount() {
	return clsCnt;
}
