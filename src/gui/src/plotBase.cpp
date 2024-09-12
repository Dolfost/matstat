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

	// axes setup
	xFixedTicker = QSharedPointer<QCPAxisTickerFixed>(new QCPAxisTickerFixed);
	xFixedTicker->setTickStepStrategy(QCPAxisTicker::TickStepStrategy::tssMeetTickCount);
	this->xAxis->setTicker(xFixedTicker);
	this->xAxis->setTickLabelRotation(90);
	this->xAxis->setNumberFormat("f");
	this->xAxis->setNumberPrecision(3);
	this->xAxis->setScaleType(QCPAxis::stLinear);
	this->xAxis->setLabel("x (класи)");
	xTicker = QSharedPointer<QCPAxisTicker>(new QCPAxisTicker);
	xTicker->setTickCount(7);
	this->xAxis2->setTicker(xTicker);
	this->xAxis2->setNumberFormat("f");
	this->xAxis2->setNumberPrecision(2);
	this->xAxis2->setScaleType(QCPAxis::stLinear);

	yTicker = QSharedPointer<QCPAxisTicker>(new QCPAxisTicker);
	yTicker->setTickStepStrategy(QCPAxisTicker::TickStepStrategy::tssMeetTickCount);
	yTicker->setTickCount(11);

	yLogTicker = QSharedPointer<AxisTickerExp>(new AxisTickerExp);
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

	// connect(this->xAxis, SIGNAL(rangeChanged(QCPRange)),
	// 		this->xAxis2, SLOT(setRange(QCPRange)));
	// connect(this->xAxis2, SIGNAL(rangeChanged(QCPRange)),
	// 		this->xAxis, SLOT(setRange(QCPRange)));

	connect(this->xAxis, SIGNAL(rangeChanged(QCPRange)),
			SLOT(handleZoomX(QCPRange)));
	connect(this->xAxis2, SIGNAL(rangeChanged(QCPRange)),
			SLOT(handleZoomX2(QCPRange)));
	connect(this->yAxis, SIGNAL(rangeChanged(QCPRange)),
			SLOT(handleZoomY(QCPRange)));
	connect(this->yAxis2, SIGNAL(rangeChanged(QCPRange)),
			SLOT(handleZoomY2(QCPRange)));

	this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

	this->axisRect()->setRangeDragAxes({
			this->xAxis,
			this->xAxis2,
			this->yAxis,
			this->yAxis2}
			);
	this->axisRect()->setRangeZoomAxes({
			this->xAxis,
			this->xAxis2,
			this->yAxis,
			this->yAxis2}
			);


	xRange = QCPRange(-5, 5);
	yRange = yRange2 = QCPRange(0, 1);
	this->xAxis->setRange(xRange);
	this->yAxis->setRange(yRange);
	this->yAxis2->setRange(yRange2);

	
	scatterPen.setWidthF(1.8);
	scatterStyle.setSize(18);
	scatterStyle.setShape(QCPScatterStyle::ssTriangle);

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

void PlotBase::fill(ss::Vector* dataVector) {
	ss::Vector::ClassSeries& cs = dataVector->cs;

	xRange = QCPRange(dataVector->min(), dataVector->max());
	if (dataVector->dist.model != ss::Vector::Distribution::Model::Unknown) {
		xRange2 = QCPRange(dataVector->dist.domain.first,
				dataVector->dist.domain.second);
		this->xAxis2->setTickLabels(true);
	}

	if (dataVector->dist.domain.first == dataVector->dist.domain.second) {
		this->xAxis2->setTickLabels(false);
		xRange2 = xRange;
	} 

	this->xAxis2->setRange(xRange2);

	this->xAxis->setRange(xRange);
	xFixedTicker->setTickStep(cs.step());
	xFixedTicker->setTickOrigin(dataVector->min()+cs.step()/2);
	xFixedTicker->setTickCount(cs.count());

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
	scatterPen.setColor("#FF0000");
	scatterStyle.setPen(scatterPen);
	mean->setScatterStyle(scatterStyle);
	mean->setLineStyle(QCPGraph::lsNone);
}

void PlotBase::plotMean() {
	QVector<double> x{dv->mean()}, y{yRange.lower};
	mean->setData(x, y);
}

void PlotBase::enableStandartDeviation() {
	standatrDeviation = new QCPGraph(this->xAxis, this->yAxis);
	standatrDeviation->setName("Ск. відх.");
	standatrDeviation->setLineStyle(QCPGraph::lsNone);
	scatterPen.setColor(Qt::magenta);
	scatterStyle.setPen(scatterPen);
	standatrDeviation->setScatterStyle(scatterStyle);
}

void PlotBase::plotStandartDeviation() {
	double meanValue = dv->mean();
	double standatrDeviationValue = dv->sd();
	QVector<double>
		x{meanValue - standatrDeviationValue,
			meanValue + standatrDeviationValue},
		y{yRange.lower, yRange.lower};

	standatrDeviation->setData(x, y);
}

void PlotBase::enableWalshMed() {
	walshMed = new QCPGraph(this->xAxis, this->yAxis);
	walshMed->setName("Мед. сер. Уолша");
	walshMed->setLineStyle(QCPGraph::lsNone);
	scatterPen.setColor(Qt::darkMagenta);
	scatterStyle.setPen(scatterPen);
	walshMed->setScatterStyle(scatterStyle);
}

void PlotBase::plotWalshMed() {
	QVector<double> x{dv->walshAveragesMed()},
		y{yRange.lower};

	walshMed->setData(x, y);
}

void PlotBase::enableMed() {
	med = new QCPGraph(this->xAxis, this->yAxis);
	med->setName("Мед.");
	med->setLineStyle(QCPGraph::lsNone);
	scatterPen.setColor(Qt::green);
	scatterStyle.setPen(scatterPen);
	med->setScatterStyle(scatterStyle);
}

void PlotBase::plotMed() {
	QVector<double> x{dv->med()},
		y{yRange.lower};

	med->setData(x, y);
}

ss::Vector* PlotBase::vector() {
	return dv;
}


void PlotBase::mouseMoveEvent(QMouseEvent *event) {
	QPoint screenPoint = event->pos();
	double x = this->xAxis->pixelToCoord(screenPoint.x());
	double x2 = this->xAxis2->pixelToCoord(screenPoint.x());
	double y = this->yAxis->pixelToCoord(screenPoint.y());
	double y2 = this->yAxis2->pixelToCoord(screenPoint.y());

	coordinatesLabel->show();

	coordinatesLabel->move(screenPoint -
			QPoint(coordinatesLabel->size().width()+6,
				coordinatesLabel->size().height()+6));

	QString coordsLabel = coordinatesLabelString;
	coordsLabel.replace("${X}", QString::number(x, 'f', 3));
	coordsLabel.replace("${X2}", QString::number(x2, 'f', 3));
	coordsLabel.replace("${Y}", QString::number(y, 'f', 3));
	coordsLabel.replace("${Y2}", QString::number(y2, 'f', 3));
	coordinatesLabel->setText(coordsLabel);
	coordinatesLabel->adjustSize();

	coordinatesTimer->stop();
	coordinatesTimer->setInterval(1800);
	coordinatesTimer->start();

	QCustomPlot::mouseMoveEvent(event);
}

void PlotBase::handleZoomX(const QCPRange& newRange) {
	this->xAxis->setRange(newRange.bounded(xRange.lower, xRange.upper));

	xAxis2->blockSignals(true);
	xAxis2->setScaleRatio(xAxis, xRange2.size()/xRange.size());
	xAxis2->blockSignals(false);
}

void PlotBase::handleZoomX2(const QCPRange& newRange) {
	this->xAxis2->setRange(newRange.bounded(xRange2.lower, xRange2.upper));

	xAxis->blockSignals(true);
	xAxis->setScaleRatio(xAxis2, xRange.size()/xRange2.size());
	xAxis->blockSignals(false);
}

void PlotBase::handleZoomY(const QCPRange& newRange) {
	this->yAxis->setRange(newRange.bounded(yRange.lower, yRange.upper));

	yAxis2->blockSignals(true);
	yAxis2->setScaleRatio(yAxis, yRange2.upper/yRange.upper);
	yAxis2->blockSignals(false);
}

void PlotBase::handleZoomY2(const QCPRange& newRange) {
	this->yAxis2->setRange(newRange.bounded(yRange2.lower, yRange2.upper));

	yAxis->blockSignals(true);
	yAxis->setScaleRatio(yAxis2, yRange.upper/yRange2.upper);
	yAxis->blockSignals(false);
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
	handleZoomX2(xRange);
	handleZoomY(yRange);
	handleZoomY2(yRange2);
	replot();
}

void PlotBase::saveToPng() {
  auto al = antialiasedElements();
  setAntialiasedElements(QCP::aeAll);
  QString filename = QFileDialog::getSaveFileName(
      this, "Зберегти графік",
		QDir::homePath() + "/" + p_saveFilename + ".png",
      "Файли фото (*.png)");

  if (filename.length())
		savePng(filename, 0, 0, 4, 100);
	setAntialiasedElements(al);
}

void PlotBase::saveToJpg() {
  auto al = antialiasedElements();
  setAntialiasedElements(QCP::aeAll);
  QString filename = QFileDialog::getSaveFileName(
      this, "Зберегти графік",
      QDir::homePath() + "/" + p_saveFilename + ".jpg",
      "Файли фото (*.jpg)");

  if (filename.length())
	  saveJpg(filename, 0, 0, 4, 100);
  setAntialiasedElements(al);
}

void PlotBase::saveToPdf() {
  auto al = antialiasedElements();
  setAntialiasedElements(QCP::aeAll);
  QString filename = QFileDialog::getSaveFileName(
      this, "Зберегти графік",
      QDir::homePath() + "/" + p_saveFilename + ".pdf",
      "Файли документів (*.pdf)");

  if (filename.length())
	  savePdf(filename);
  setAntialiasedElements(al);
}
