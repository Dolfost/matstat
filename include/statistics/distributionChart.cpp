#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>
#include <QtCore/qnamespace.h>

#include "classSeries.hpp"
#include "distributionChart.hpp"
#include "plotBase.hpp"

DistributionChart::DistributionChart(QWidget* parent) : PlotBase(parent) {
	bars->setName("F(x) (class)");
	title->setText("Distribution");
	enableMed();
	enableWalshMed();

	yRange = QCPRange(0,1.01);
}

void DistributionChart::fill(ClassSeries* clSr) {
	cs = clSr;

	QVector<double> x, y;
	double cumSum = 0;
	for (size_t i = 0; i < cs->classCount(); i++) {
		x.push_back(cs->dataVector->min() + cs->step()*(i+0.5));
		cumSum += cs->series()[i].second;
		y.push_back(cumSum);
	}

	bars->setData(x, y, true);

	plotMed();
	plotWalshMed();

	this->yAxis->setRange(yRange);

	PlotBase::fill(cs);
}

