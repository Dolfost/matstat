#include <QGraphicsSceneMouseEvent>
#include <QtCore/qlogging.h>
#include <QtCore/qnamespace.h>
#include <QtCore/qobject.h>
#include <QtWidgets/qboxlayout.h>

#include "vectorPlotBase.hpp"

VectorPlotBase::VectorPlotBase(ss::Vector* v, QWidget* parent) : Plot2dBase(parent) {
	v_vector = v;

	xFixedTicker = QSharedPointer<QCPAxisTickerFixed>(new QCPAxisTickerFixed);
	xFixedTicker->setTickStepStrategy(QCPAxisTicker::TickStepStrategy::tssMeetTickCount);
	this->xAxis->setTicker(xFixedTicker);

	xTicker = QSharedPointer<QCPAxisTicker>(new QCPAxisTicker);
	xTicker->setTickCount(7);
	this->xAxis2->setTicker(xTicker);

	yTicker = QSharedPointer<QCPAxisTicker>(new QCPAxisTicker);
	yTicker->setTickStepStrategy(QCPAxisTicker::TickStepStrategy::tssMeetTickCount);
	yTicker->setTickCount(11);

	yLogTicker = QSharedPointer<QCPAxisTickerLog>(new QCPAxisTickerLog);
	yLogTicker->setTickStepStrategy(QCPAxisTicker::TickStepStrategy::tssMeetTickCount);
	yLogTicker->setTickCount(6);
	yLogTicker->setLogBase(10);

	toggleLog(Qt::Unchecked);

	mean = new QCPGraph(this->xAxis, this->yAxis);
	mean->setLayer(layer("stat"));
	mean->setName("Мат. спод.");
	statScatterPen.setColor("#FF0000");
	statScatter.setPen(statScatterPen);
	mean->setScatterStyle(statScatter);
	mean->setLineStyle(QCPGraph::lsNone);

	standatrDeviation = new QCPGraph(this->xAxis, this->yAxis);
	standatrDeviation->setLayer(layer("stat"));
	standatrDeviation->setName("Ск. відх.");
	standatrDeviation->setLineStyle(QCPGraph::lsNone);
	statScatterPen.setColor(Qt::magenta);
	statScatter.setPen(statScatterPen);
	standatrDeviation->setScatterStyle(statScatter);

	walshMed = new QCPGraph(this->xAxis, this->yAxis);
	walshMed->setLayer(layer("stat"));
	walshMed->setName("Мед. сер. Уолша");
	walshMed->setLineStyle(QCPGraph::lsNone);
	statScatterPen.setColor(Qt::darkMagenta);
	statScatter.setPen(statScatterPen);
	walshMed->setScatterStyle(statScatter);

	med = new QCPGraph(this->xAxis, this->yAxis);
	med->setLayer(layer("stat"));
	med->setName("Мед.");
	med->setLineStyle(QCPGraph::lsNone);
	statScatterPen.setColor(Qt::green);
	statScatter.setPen(statScatterPen);
	med->setScatterStyle(statScatter);


	this->xAxis->setLabel("x (класи)");
}

void VectorPlotBase::fill() {
	ss::Vector::ClassSeries& cs = v_vector->cs;

	xRange = QCPRange(v_vector->min(), v_vector->max());
	if (v_vector->dist.model != ss::Vector::Distribution::Model::Unknown) {
		xRange2 = QCPRange(v_vector->dist.domain.first,
				v_vector->dist.domain.second);
		this->xAxis2->setTickLabels(true);
	}

	if (v_vector->dist.domain.first == v_vector->dist.domain.second) {
		this->xAxis2->setTickLabels(false);
		xRange2 = xRange;
	} 

	this->xAxis2->setRange(xRange2);

	this->xAxis->setRange(xRange);
	xFixedTicker->setTickStep(cs.step());
	xFixedTicker->setTickOrigin(v_vector->min()+cs.step()/2);
	xFixedTicker->setTickCount(cs.count());

	this->yAxis->setRange(yRange);
	this->yAxis2->setRange(yRange2);

	QVector<double> x{v_vector->mean()}, y{yRange.lower};
	mean->setData(x, y);

	double meanValue = v_vector->mean();
	double standatrDeviationValue = v_vector->sd();
	x = {meanValue - standatrDeviationValue,
		meanValue + standatrDeviationValue},
	y = {yRange.lower, yRange.lower};
	standatrDeviation->setData(x, y);

	x = {v_vector->walshAveragesMed()},
	y = {yRange.lower};
	walshMed->setData(x, y);

	x = {v_vector->med()},
	y = {yRange.lower};
	med->setData(x, y);

	Plot2dBase::fill();
}

void VectorPlotBase::toggleLog(bool state) {
	if (state == true) {
		this->yAxis->setTicker(yLogTicker);
		this->yAxis->setScaleType(QCPAxis::stLogarithmic);
		this->yAxis2->setTicker(yLogTicker);
		this->yAxis2->setScaleType(QCPAxis::stLogarithmic);
		this->yAxis->setNumberFormat("eb");
		this->yAxis->setNumberPrecision(0);
		this->yAxis2->setNumberFormat("eb");
		this->yAxis2->setNumberPrecision(0);
	} else {
		this->yAxis->setTicker(yTicker);
		this->yAxis->setScaleType(QCPAxis::stLinear);
		this->yAxis2->setTicker(yTicker);
		this->yAxis2->setScaleType(QCPAxis::stLinear);
		this->yAxis->setNumberFormat("f");
		this->yAxis->setNumberPrecision(3);
		this->yAxis2->setNumberFormat("f");
		this->yAxis2->setNumberPrecision(3);
	}

	this->replot();
}
