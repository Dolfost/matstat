#include<vectorPairPlotBase.hpp>

VectorPairPlotBase::VectorPairPlotBase(ss::VectorPair* v, QWidget* p): PlotBase(p) {
	v_pair = v;

	this->xAxis2->setTickLabels(false);
	this->yAxis2->setTickLabels(false);

	xFixedTicker->setTickStepStrategy(QCPAxisTicker::TickStepStrategy::tssMeetTickCount);
	this->xAxis->setTicker(xFixedTicker);
	this->xAxis2->setTicker(xFixedTicker);

	this->yAxis->setTicker(yFixedTicker);
	this->yAxis2->setTicker(yFixedTicker);

	// this->xAxis->setLabel("x (класи)");
	// this->yAxis->setLabel("y (класи)");

	QPen gpen = this->xAxis->grid()->pen();
	gpen.setWidthF(1.2);
	this->xAxis->grid()->setPen(gpen);
	this->yAxis->grid()->setPen(gpen);

	xFixedTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples);
	yFixedTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples);
	xFixedTicker->setTickStepStrategy(QCPAxisTicker::tssReadability);
	yFixedTicker->setTickStepStrategy(QCPAxisTicker::tssReadability);
}

void VectorPairPlotBase::fill() {
	xRange = QCPRange(v_pair->x.min(), v_pair->x.max());
	xRange2 = xRange;
	this->xAxis->setRange(xRange);
	this->xAxis2->setRange(xRange2);

	yRange = QCPRange(v_pair->y.min(), v_pair->y.max());
	yRange2 = yRange;
	this->yAxis->setRange(yRange);
	this->yAxis2->setRange(yRange2);

	xFixedTicker->setTickOrigin(v_pair->x.min());
	xFixedTicker->setTickStep(v_pair->cs.stepX());
	xFixedTicker->setTickCount(v_pair->cs.countX());

	yFixedTicker->setTickOrigin(v_pair->y.min());
	yFixedTicker->setTickStep(v_pair->cs.stepY());
	yFixedTicker->setTickCount(v_pair->cs.countY());

	PlotBase::fill();
}

void VectorPairPlotBase::toggleLog(bool state) {}
