#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>
#include <QtCore/qnamespace.h>

#include "classSeries.hpp"
#include "relativeFrequencyChart.hpp"
#include "plotBase.hpp"

RelativeFrequencyChart::RelativeFrequencyChart(QWidget* parent) : PlotBase(parent) {
}

void RelativeFrequencyChart::fill(ClassSeries* clSr) {
	cs = clSr;


	QVector<double> x, y;
	for (size_t i = 0; i < cs->classCount(); i++) {
		x.push_back(cs->dataVector->min() + cs->step()*(i+0.5));
		y.push_back(cs->series()[i].second);
	}

	bars->setData(x, y);


	PlotBase::fill(cs);
}

