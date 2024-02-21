#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>
#include <QtCore/qnamespace.h>
#include <QtCore/qnumeric.h>

#include "classSeries.hpp"
#include "distributionChart.hpp"
#include "plotBase.hpp"

DistributionChart::DistributionChart(QWidget* parent) : PlotBase(parent) {
	title->setText("Розподіл");

	graph = new QCPGraph(this->xAxis, this->yAxis);
	graph->setName("F(x) (класи)");
	QPen graphPen;
	graphPen.setWidthF(1.2);
	graphPen.setColor("#2b8eff");
	graph->setPen(graphPen);

	enableMed();
	enableWalshMed();

	yRange = QCPRange(0,1);
	this->yAxis->setLabel("F(x)");
}

void DistributionChart::fill(ClassSeries* clSr) {
	cs = clSr;

	QVector<double> x, y;
	double cumSum = 0;
	for (size_t i = 0; i < cs->classCount(); i++) {
		x.push_back(cs->dataVector->min() + cs->step()*i);
		x.push_back(cs->dataVector->min() + cs->step()*(i+1));

		cumSum += cs->series()[i].second;

		y.push_back(cumSum);
		y.push_back(cumSum);

		x.push_back(qQNaN());
		x.push_back(qQNaN());
		y.push_back(qQNaN());
		y.push_back(qQNaN());
	}

	graph->setData(x, y, true);

	plotMed();
	plotWalshMed();

	this->yAxis->setRange(yRange);

	PlotBase::fill(cs);
}

