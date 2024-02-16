#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>
#include <QtCore/qnamespace.h>

#include "classSeries.hpp"
#include "relativeFrequencyChart.hpp"
#include "chartViewBase.hpp"

RelativeFrequencyChart::RelativeFrequencyChart(QWidget* parent) : ChartViewBase(parent) {
	chart->setTitle("Relative frequency chart");

	barAreaSeries->setName("Rel. freq.");

	chart->removeSeries(continiousSplineSeries);
	chart->removeSeries(medLineSeries);
}

void RelativeFrequencyChart::fill(ClassSeries* clSr) {
	cs = clSr;

	upperBarAreaSeries->clear();
	for (size_t i = 0; i < cs->classCount(); i++) {
		upperBarAreaSeries->append(cs->dataVector->min() + i*cs->step(), cs->series()[i].second);
		upperBarAreaSeries->append(cs->dataVector->min() + (i+1)*cs->step(), cs->series()[i].second);
	}

	ChartViewBase::fill(cs);

	chart->axes(Qt::Vertical)[0]->setRange(0, cs->maxIntervalProbability());
}

