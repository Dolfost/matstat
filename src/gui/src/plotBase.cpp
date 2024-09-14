#include <plotBase.hpp>

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
	this->xAxis->setTickLabelRotation(45);
	this->xAxis->setNumberFormat("f");
	this->xAxis->setNumberPrecision(3);
	this->xAxis->setScaleType(QCPAxis::stLinear);
	this->xAxis2->setNumberFormat("f");
	this->xAxis2->setNumberPrecision(2);
	this->xAxis2->setScaleType(QCPAxis::stLinear);

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

	connect(this->xAxis, qOverload<const QCPRange&>(&QCPAxis::rangeChanged),
			this, &PlotBase::handleZoomX);
	connect(this->xAxis2, qOverload<const QCPRange&>(&QCPAxis::rangeChanged),
			this, &PlotBase::handleZoomX2);
	connect(this->yAxis, qOverload<const QCPRange&>(&QCPAxis::rangeChanged),
			this, &PlotBase::handleZoomY);
	connect(this->yAxis2, qOverload<const QCPRange&>(&QCPAxis::rangeChanged),
			this, &PlotBase::handleZoomY2);

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

	addLayer("stat", layer("main"));

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

void PlotBase::fill() {
	replot();
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
	yAxis2->setScaleRatio(yAxis, yRange2.size()/yRange.size());
	yAxis2->blockSignals(false);
}

void PlotBase::handleZoomY2(const QCPRange& newRange) {
	this->yAxis2->setRange(newRange.bounded(yRange2.lower, yRange2.upper));

	yAxis->blockSignals(true);
	yAxis->setScaleRatio(yAxis2, yRange.size()/yRange2.size());
	yAxis->blockSignals(false);
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
