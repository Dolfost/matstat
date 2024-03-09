#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>
#include <algorithm>

#include <QDebug>

#include "classSeries.hpp"
#include "densityChart.hpp"
#include "plotBase.hpp"

DensityChart::DensityChart(QWidget* parent) : PlotBase(parent) {
	title->setText("Щільність");

	bars = new QCPBars(this->xAxis, this->yAxis);
	bars->setName("f(x) (класи)");
	bars->setWidthType(QCPBars::WidthType::wtPlotCoords);

	QPen barsPen;
	barsPen.setWidth(0);
	bars->setPen(Qt::NoPen);
	QBrush barsBrush;
	barsBrush.setStyle(Qt::SolidPattern);
	barsBrush.setColor("#2b8eff");
	bars->setBrush(barsBrush);

	density = new QCPGraph(this->xAxis, this->yAxis);
	density->setName("f(x) (відтв.)");

	enableMean();
	enableStandartDeviation();
	enableMed();
	enableWalshMed();

	this->yAxis->setLabel("f(x)");
}

void DensityChart::fill(ClassSeries* clSr) {
	cs = clSr;

	bars->setWidth(cs->step());

	QVector<double> x, y;
	for (size_t i = 0; i < cs->classCount(); i++) {
		x.push_back(cs->dataVector->min() + cs->step()*(i+0.5));
		y.push_back(cs->series()[i].second);
	}

	bars->setData(x, y, true);

	x.clear(), y.clear();

	if (cs->dataVector->distribution() != DataVector::Distribution::UnknownD) {
		double interval = abs(cs->dataVector->max() - cs->dataVector->min())/2;
		for (cs->dataVector->distributionData.x = cs->dataVector->min();
				cs->dataVector->distributionData.x <= cs->dataVector->max(); 
				cs->dataVector->distributionData.x += interval/350) {
			x.push_back(cs->dataVector->distributionData.x);
			y.push_back(cs->dataVector->distributionData.pdfExpression.value());
		}

		density->setData(x, y);
	}

	yRange = QCPRange(0, cs->maxIntervalProbability());

	plotMean();
	plotStandartDeviation();
	plotMed();
	plotWalshMed();

	PlotBase::fill(cs);
}

