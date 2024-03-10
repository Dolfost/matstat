#include <QGraphicsSceneMouseEvent>
#include <QtCore/qlogging.h>
#include <QtCore/qnamespace.h>
#include <QtCore/qobject.h>
#include <QtWidgets/qboxlayout.h>

#include "plotBase.hpp"

PlotBase::PlotBase(QWidget* parent) : QCustomPlot(parent) {
	this->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
	this->legend->setVisible(true);
	this->setAutoAddPlottableToLegend(true);
	this->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft|Qt::AlignTop);
	this->setAntialiasedElements(QCP::AntialiasedElement::aeAll);
	this->plotLayout()->setMargins(QMargins(5, 5, 5, 5));

	QCPLayoutGrid *subLayout = new QCPLayoutGrid;
	this->plotLayout()->addElement(1, 0, subLayout);
	subLayout->setMargins(QMargins(5, 0, 5, 5));
	subLayout->addElement(0, 0, this->legend);
	this->legend->setFillOrder(QCPLegend::foColumnsFirst);
	this->plotLayout()->setRowStretchFactor(1, 0.001);

	this->plotLayout()->insertRow(0);
	title = new QCPTextElement(this, "Title");
	this->plotLayout()->addElement(0, 0, title);

	// axes setup
	xFixedTicker = QSharedPointer<QCPAxisTickerFixed>(new QCPAxisTickerFixed);
	xFixedTicker->setTickStepStrategy(QCPAxisTicker::TickStepStrategy::tssMeetTickCount);
	this->xAxis->setTicker(xFixedTicker);
	this->xAxis->setTickLabelRotation(90);
	this->xAxis->setNumberFormat("f");
	this->xAxis->setNumberPrecision(3);
	this->xAxis->setScaleType(QCPAxis::stLinear);
	this->xAxis->setLabel("x");
	this->xAxis2->setTicker(xFixedTicker);

	yTicker = QSharedPointer<QCPAxisTicker>(new QCPAxisTicker);
	yTicker->setTickStepStrategy(QCPAxisTicker::TickStepStrategy::tssMeetTickCount);
	yTicker->setTickCount(11);

	yLogTicker = QSharedPointer<QCPAxisTickerLog>(new QCPAxisTickerLog);
	yLogTicker->setTickStepStrategy(QCPAxisTicker::TickStepStrategy::tssMeetTickCount);
	yLogTicker->setTickCount(6);
	yLogTicker->setLogBase(10);

	toggleLog(Qt::Unchecked);

	this->yAxis->setTickLength(0, 5);
	this->yAxis->setSubTickLength(0, 3);
	this->xAxis->setTickLength(0, 5);
	this->xAxis->setSubTickLength(0, 3);
	this->yAxis2->setTickLength(0, 5);
	this->yAxis2->setSubTickLength(0, 3);
	this->xAxis2->setTickLength(0, 5);
	this->xAxis2->setSubTickLength(0, 3);

	this->xAxis2->setVisible(true);
	this->xAxis2->setTickLabels(false);
	this->yAxis2->setVisible(true);
	this->yAxis2->setTickLabels(true);

	connect(this->xAxis, SIGNAL(rangeChanged(QCPRange)),
			this->xAxis2, SLOT(setRange(QCPRange)));

	//  TODO:
	//  make the yAxis2 for the density chart to be from the 0 to the distribution->cfmMax

	connect(this->xAxis, SIGNAL(rangeChanged(QCPRange)),
			SLOT(handleZoomX(QCPRange)));
	connect(this->yAxis, SIGNAL(rangeChanged(QCPRange)),
			SLOT(handleZoomY(QCPRange)));
	connect(this->yAxis2, SIGNAL(rangeChanged(QCPRange)),
			SLOT(handleZoomY2(QCPRange)));

	this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

	this->axisRect()->setRangeDragAxes({
			this->xAxis,
			this->yAxis,
			this->yAxis2,
			});
	this->axisRect()->setRangeZoomAxes({
			this->xAxis,
			this->yAxis,
			this->yAxis2,
			});


	xRange = QCPRange(-5, 5);
	yRange = QCPRange(0, 1);
	yRange2 = QCPRange(0, 1);
	this->xAxis->setRange(xRange);
	this->yAxis->setRange(yRange);
	this->yAxis2->setRange(yRange);
	this->replot();

	// coordinatesLabel setup
	coordinatesLabel = new QLabel("", this);
	coordinatesLabel->setAlignment(Qt::AlignCenter);
	coordinatesLabel->setStyleSheet("color: black; font-size: 11px;");
	coordinatesLabel->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
	coordinatesTimer = new QTimer();
	coordinatesTimer->setSingleShot(true);
	connect(coordinatesTimer, &QTimer::timeout, this, [this]{coordinatesLabel->hide();});
}

void PlotBase::fill(ClassSeries* cs) {

	xRange = QCPRange(cs->dataVector->min(), cs->dataVector->max());

	this->xAxis->setRange(xRange);
	xFixedTicker->setTickStep(cs->step());
	xFixedTicker->setTickOrigin(cs->dataVector->min()+cs->step()/2);
	xFixedTicker->setTickCount(cs->classCount());

	this->yAxis->setRange(yRange);
	this->yAxis2->setRange(yRange2);

	this->replot();
}

void PlotBase::clear() {
	for (int i = 0; i < this->plottableCount(); i++) {
		QCPAbstractPlottable* plottable = this->plottable(i);

		QCPGraph* graph;
		QCPBars* bars;

		if ((graph = qobject_cast<QCPGraph*>(plottable))) {
			graph->data().data()->clear();
		} else if ((bars = qobject_cast<QCPBars*>(plottable))) {
			bars->data().data()->clear();
		};
	}

	this->replot();
}

void PlotBase::enableMean() {
	mean = new QCPGraph(this->xAxis, this->yAxis);
	mean->setName("Мат. спод.");
	mean->setLineStyle(QCPGraph::lsLine);
	QPen pen;
	pen.setColor(Qt::red);
	pen.setDashPattern({5, 10});
	pen.setWidthF(1.2);
	mean->setPen(pen);
}

void PlotBase::plotMean() {
	QVector<double> x{cs->dataVector->mean(), cs->dataVector->mean()}, y{yRange.lower, yRange.upper};
	mean->setData(x, y);
}

void PlotBase::enableStandartDeviation() {
	standatrDeviation = new QCPGraph(this->xAxis, this->yAxis);
	standatrDeviation->setName("Ск. відх.");
	standatrDeviation->setLineStyle(QCPGraph::lsLine);
	QPen pen;
	pen.setColor(Qt::magenta);
	pen.setWidthF(1.2);
	standatrDeviation->setPen(pen);
}

void PlotBase::plotStandartDeviation() {
	double meanValue = cs->dataVector->mean();
	double standatrDeviationValue = cs->dataVector->standardDeviation();
	QVector<double>
		x{meanValue - standatrDeviationValue, meanValue - standatrDeviationValue,
			qQNaN(),
			meanValue + standatrDeviationValue, meanValue + standatrDeviationValue},
		y{yRange.lower, yRange.upper, qQNaN(), yRange.upper, yRange.lower};

	standatrDeviation->setData(x, y);
}

void PlotBase::enableWalshMed() {
	walshMed = new QCPGraph(this->xAxis, this->yAxis);
	walshMed->setName("Мед. сер. Уолша");
	walshMed->setLineStyle(QCPGraph::lsLine);
	QPen pen;
	pen.setColor(Qt::darkMagenta);
	pen.setWidthF(1.5);
	walshMed->setPen(pen);
}

void PlotBase::plotWalshMed() {
	QVector<double> x{cs->dataVector->walshAveragesMed(), cs->dataVector->walshAveragesMed()},
		y{yRange.lower, yRange.upper};

	walshMed->setData(x, y);
}

void PlotBase::enableMed() {
	med = new QCPGraph(this->xAxis, this->yAxis);
	med->setName("Мед.");
	med->setLineStyle(QCPGraph::lsLine);
	QPen pen;
	pen.setColor(Qt::green);
	pen.setWidthF(1.5);
	med->setPen(pen);
}

void PlotBase::plotMed() {
	QVector<double> x{cs->dataVector->med(), cs->dataVector->med()},
		y{yRange.lower, yRange.upper};

	med->setData(x, y);
}

ClassSeries* PlotBase::classSeries() {
	return cs;
}



void PlotBase::mouseMoveEvent(QMouseEvent *event) {
	QPoint screenPoint = event->pos();
	double x = this->xAxis->pixelToCoord(screenPoint.x());
	double y = this->yAxis->pixelToCoord(screenPoint.y());
	double y2 = this->yAxis2->pixelToCoord(screenPoint.y());

	coordinatesLabel->show();

	coordinatesLabel->move(screenPoint -
			QPoint(coordinatesLabel->size().width()+6,
				coordinatesLabel->size().height()+6));
	coordinatesLabel->setText(QString(coordinatesLabelString)
			.arg(x, 3, 'f', 3)
			.arg(y, 3, 'f', 3)
			.arg(y2, 3, 'f', 3));
	coordinatesLabel->adjustSize();

	coordinatesTimer->stop();
	coordinatesTimer->setInterval(1800);
	coordinatesTimer->start();

	QCustomPlot::mouseMoveEvent(event);
}

void PlotBase::handleZoomX(const QCPRange& newRange) {
	this->xAxis->setRange(newRange.bounded(xRange.lower, xRange.upper));
}

void PlotBase::handleZoomY(const QCPRange& newRange) {
	this->yAxis->setRange(newRange.bounded(yRange.lower, yRange.upper));
}

void PlotBase::handleZoomY2(const QCPRange& newRange) {
	this->yAxis2->setRange(newRange.bounded(yRange2.lower, yRange2.upper));
}

void PlotBase::toggleLog(bool state) {
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

void PlotBase::zoomHome() {
	handleZoomX(xRange);
	handleZoomY(yRange);
	handleZoomY2(yRange2);
	replot();
}
