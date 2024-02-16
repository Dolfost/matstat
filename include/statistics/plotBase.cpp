#include <QGraphicsSceneMouseEvent>
#include <QtCore/qnamespace.h>
#include <QtCore/qobject.h>
#include <QtWidgets/qboxlayout.h>

#include "plotBase.hpp"

PlotBase::PlotBase(QWidget* parent) : QCustomPlot(parent) {
	this->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));

	xFixedTicker = QSharedPointer<QCPAxisTickerFixed>(new QCPAxisTickerFixed);
	xFixedTicker->setTickStepStrategy(QCPAxisTicker::TickStepStrategy::tssMeetTickCount);
	this->xAxis->setTicker(xFixedTicker);
	this->xAxis->setScaleType(QCPAxis::stLinear);
	this->xAxis2->setTicker(xFixedTicker);

	yTicker = QSharedPointer<QCPAxisTicker>(new QCPAxisTicker);
	yTicker->setTickStepStrategy(QCPAxisTicker::TickStepStrategy::tssMeetTickCount);
	yTicker->setTickCount(11);
	this->yAxis->setTicker(yTicker);
	this->yAxis->setScaleType(QCPAxis::stLinear);
	this->yAxis2->setTicker(yTicker);

	yLogTicker = QSharedPointer<QCPAxisTickerLog>(new QCPAxisTickerLog);
	yLogTicker->setTickStepStrategy(QCPAxisTicker::TickStepStrategy::tssMeetTickCount);


	bars = new QCPBars(this->xAxis, this->yAxis);
	bars->setWidthType(QCPBars::WidthType::wtPlotCoords);

	this->yAxis->setTickLength(0, 5);
	this->yAxis->setSubTickLength(0, 3);
	this->xAxis->setTickLength(0, 5);
	this->xAxis->setSubTickLength(0, 3);

	this->xAxis2->setVisible(true);
	this->xAxis2->setTickLabels(false);
	this->yAxis2->setVisible(true);
	this->yAxis2->setTickLabels(false);

	connect(this->xAxis, SIGNAL(rangeChanged(QCPRange)), this->xAxis2, SLOT(setRange(QCPRange)));
	connect(this->yAxis, SIGNAL(rangeChanged(QCPRange)), this->yAxis2, SLOT(setRange(QCPRange)));

	connect(this->xAxis, SIGNAL(rangeChanged(QCPRange)), SLOT(handleZoomX(QCPRange)));
	connect(this->yAxis, SIGNAL(rangeChanged(QCPRange)), SLOT(handleZoomY(QCPRange)));

	this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);


}

void PlotBase::fill(ClassSeries* cs) {
	bars->setWidth(cs->step());

	this->xAxis->setRange(cs->dataVector->min(),cs->dataVector->max());
	xFixedTicker->setTickStep(cs->step());
	xFixedTicker->setTickOrigin(cs->dataVector->min()+cs->step()/2);
	xFixedTicker->setTickCount(cs->classCount());


	this->yAxis->setRange(0, cs->maxIntervalProbability());

	this->replot();
}

void PlotBase::mouseMoveEvent(QMouseEvent *event) {

}

ClassSeries* PlotBase::classSeries() {
	return cs;
}

void PlotBase::handleZoomX(const QCPRange& newRange) {
	if (newRange.minRange < cs->dataVector->min()-100 ||
			newRange.maxRange > cs->dataVector->max()+100) {
		this->xAxis->setRange(newRange.bounded(cs->dataVector->min(), cs->dataVector->max()));
	}
}

void PlotBase::handleZoomY(const QCPRange& newRange) {
	if (newRange.minRange < 0-1 ||
			newRange.maxRange > cs->maxIntervalProbability()+1) {
		this->yAxis->setRange(newRange.bounded(0, cs->maxIntervalProbability()));
	}
}
