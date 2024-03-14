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
	graphPen.setWidthF(1.3);
	graphPen.setColor("#2b8eff");
	graph->setPen(graphPen);

	distribution = new QCPGraph(this->xAxis, this->yAxis2);
	distribution->setName("F(x) (відтв.)");
	QPen distributionPen;
	distributionPen.setWidthF(1.3);
	distributionPen.setColor("#0313fc");
	distribution->setPen(distributionPen);

	distributionDeviation = new QCPGraph(this->xAxis, this->yAxis2);
	distributionDeviation->setName("СКВ F(x)");
	QPen distributionDeviationPen;
	distributionDeviationPen.setWidthF(1.2);
	distributionDeviationPen.setColor("#fc0303");
	distributionDeviationPen.setDashPattern({5, 3});
	distributionDeviation->setPen(distributionDeviationPen);

	this->yAxis2->setTickLabels(false);

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

	if (cs->dataVector->reproduction.model != DistributionReproducer::Distribution::UnknownD) {
		x.clear(), y.clear();
		QList<double> yDev1, yDev2;

		double interval = abs(cs->dataVector->max() - cs->dataVector->min())/2;
		for (cs->dataVector->reproduction.x = cs->dataVector->min();
				cs->dataVector->reproduction.x <= cs->dataVector->max(); 
				cs->dataVector->reproduction.x += interval/350) {
			x.push_back(cs->dataVector->reproduction.x);
			y.push_back(cs->dataVector->reproduction.cdfExpression.value());
			std::pair<double, double> dev =
				cs->dataVector->reproduction.cdfDeviation(0.2);
			yDev1.push_back(dev.first);
			yDev2.push_back(dev.second);
		}
		
		distribution->setData(x, y, true);

		yDev1.push_back(qQNaN());
		x.push_back(qQNaN());
		x.append(x);
		x.pop_back();
		yDev1.append(yDev2);

		distributionDeviation->setData(x, yDev1, true);
	} else {
		distribution->data()->clear();
	}


	plotMed();
	plotWalshMed();

	this->yAxis->setRange(yRange);

	PlotBase::fill(cs);
}

