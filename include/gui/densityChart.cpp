#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>

#include <QDebug>

#include "densityChart.hpp"
#include "plotBase.hpp"

#include "statistics/classSeries.hpp"

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

	density = new QCPGraph(this->xAxis2, this->yAxis2);
	density->setName("f(x) (відтв.)");
	this->yAxis2->setLabel("f(x) (відтворена)");
	this->xAxis2->setLabel("x (відтворена)");
	QPen densityPen;
	densityPen.setWidthF(1.3);
	densityPen.setColor("#0313fc");
	density->setPen(densityPen);

	enableMean();
	enableStandartDeviation();
	enableMed();
	enableWalshMed();

	this->yAxis->setLabel("f(x) (класи)");
}

void DensityChart::fill(DataVector* dataVector) {
	dv = dataVector;
	DataVector::ClassSeries* cs = dataVector->classSeries();

	bars->setWidth(cs->step());

	QVector<double> x, y;
	for (size_t i = 0; i < cs->classCount(); i++) {
		x.push_back(dv->min() + cs->step()*(i+0.5));
		y.push_back(cs->series()[i].second);
	}

	bars->setData(x, y, true);

	x.clear(), y.clear();

	if (dataVector->rep.model != DistributionReproducer::Distribution::UnknownD) {
		if (dataVector->rep.domain.first == dataVector->rep.domain.second)
			coordinatesLabelString = "${X}\n${Y} ${Y2}";
		else
			coordinatesLabelString = "${X} ${X2}\n${Y} ${Y2}";

		this->yAxis2->setTickLabels(true);
		this->yRange2 = QCPRange(0, dataVector->rep.pdfMax);
		double a, b;
		if (dataVector->rep.domain.first != dataVector->rep.domain.second) {
			a = dataVector->rep.domain.first;
			b = dataVector->rep.domain.second;
		} else {
			a = dataVector->min();
			b = dataVector->max();
		}

		double interval = abs(a - b)/2;
		for (double arg = a;
				arg <= b;
				arg += interval/350) {
			x.push_back(arg);
			y.push_back(dataVector->rep.pdf(arg));
		}

		density->setData(x, y);
	} else {
		coordinatesLabelString = "${X}\n${Y}";
		this->yAxis2->setTickLabels(false);
		density->data()->clear();
	};

	yRange = QCPRange(0, cs->maxIntervalProbability());

	plotMean();
	plotStandartDeviation();
	plotMed();
	plotWalshMed();

	PlotBase::fill(dv);
}

