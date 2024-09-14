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

	scatterStyle.setShape(QCPScatterStyle::ssCrossCircle);
	scatterStyle.setSize(15);
	scatterPen.setWidthF(0.8);

	mean = new QCPGraph(this->xAxis, this->yAxis);
	mean->setLayer(layer("stat"));
	mean->setName("Мат. спод.");
	mean->setLineStyle(QCPGraph::lsNone);
	scatterPen.setColor(Qt::blue);
	scatterStyle.setPen(scatterPen);
	mean->setScatterStyle(scatterStyle);

	med = new QCPGraph(this->xAxis, this->yAxis);
	med->setLayer(layer("stat"));
	med->setName("Медіана");
	med->setLineStyle(QCPGraph::lsNone);
	scatterPen.setColor(Qt::green);
	scatterStyle.setPen(scatterPen);
	med->setScatterStyle(scatterStyle);
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

	mean->setData({v_pair->x.mean()}, {v_pair->y.mean()});
	med->setData({v_pair->x.med()}, {v_pair->y.med()});

	PlotBase::fill();
}

void VectorPairPlotBase::toggleLog(bool state) {}
