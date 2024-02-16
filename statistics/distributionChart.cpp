
#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>

#include "classSeries.hpp"
#include "distributionChart.hpp"
#include "chartViewBase.hpp"

DistributionChart::DistributionChart(QWidget* parent) : ChartViewBase(parent) {
	chart->setTitle("Distribution chart");

	barAreaSeries->setName("Imp. dist.");
	continiousSplineSeries->setName("Cum. dist.");

	chart->removeSeries(meanLineSeries);
	chart->removeSeries(standatrDeviationLineSeries);
	chart->removeSeries(walshMedLineSeries);
	
}

void DistributionChart::fill(ClassSeries* clSr) {
	cs = clSr;

	double cumSum = 0;

	upperBarAreaSeries->clear();
	for (size_t i = 0; i < cs->classCount(); i++) {
		cumSum += cs->series()[i].second;
		upperBarAreaSeries->append(cs->dataVector->min() + i*cs->step(), cumSum);
		upperBarAreaSeries->append(cs->dataVector->min() + (i+1)*cs->step(), cumSum);
	}

	continiousSplineSeries->clear();
	cumSum = 0;
	double delta = 1.0/cs->dataVector->size();
	for (auto const& i : cs->dataVector->vector()) {
		continiousSplineSeries->append(i, cumSum);
		cumSum += delta;
	}

	ChartViewBase::fill(cs);

	chart->axes(Qt::Vertical)[0]->setRange(0, 1);
}
