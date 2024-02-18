#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QValueAxis>
#include <QtCore/qnamespace.h>

#include "classSeries.hpp"
#include "densityChart.hpp"
#include "plotBase.hpp"

DensityChart::DensityChart(QWidget* parent) : PlotBase(parent) {
	bars->setName("f(x) (class)");
	title->setText("Density");
	enableMean();
	enableStandartDeviation();
	enableMed();
	enableWalshMed();
}

void DensityChart::fill(ClassSeries* clSr) {
	cs = clSr;


	QVector<double> x, y;
	for (size_t i = 0; i < cs->classCount(); i++) {
		x.push_back(cs->dataVector->min() + cs->step()*(i+0.5));
		y.push_back(cs->series()[i].second);
	}

	bars->setData(x, y, true);

	yRange = QCPRange(0, cs->maxIntervalProbability()*1.01);

	plotMean();
	plotStandartDeviation();
	plotMed();
	plotWalshMed();

	PlotBase::fill(cs);
}

