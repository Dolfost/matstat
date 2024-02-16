#include <QGraphicsSceneMouseEvent>
#include <QtCore/qnamespace.h>
#include <QtCore/qobject.h>
#include <QtWidgets/qboxlayout.h>

#include "chartViewBase.hpp"

ChartViewBase::ChartViewBase(QWidget* parent) : QChartView(parent) {
	chart = new QChart();
	chart->setMargins(QMargins(10,10,5,10));
	
	chartView = this;
	this->setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
	this->setParent(parent);
	this->setChart(chart);

	xAxis = new QValueAxis();
	xAxis->setLabelsAngle(90);
	chart->addAxis(xAxis, Qt::AlignBottom);

	yAxis = new QValueAxis();
	chart->addAxis(yAxis, Qt::AlignLeft);
	yAxis->setTickCount(11);
	yAxis->setMinorGridLineVisible(true);
	yAxis->setMinorTickCount(1);

	lowerBarAreaSeries = new QLineSeries();
	upperBarAreaSeries = new QLineSeries();
	barAreaSeries = new QAreaSeries(upperBarAreaSeries, lowerBarAreaSeries);
	chart->addSeries(barAreaSeries);
	barAreaSeries->attachAxis(xAxis);
	barAreaSeries->attachAxis(yAxis);

	continiousSplineSeries = new QSplineSeries();
	QPen continiousPen;
	continiousPen.setWidthF(1.2);
	continiousPen.setColor(Qt::red);
	continiousSplineSeries->setPen(continiousPen);
	chart->addSeries(continiousSplineSeries);
	continiousSplineSeries->attachAxis(xAxis);
	continiousSplineSeries->attachAxis(yAxis);

	meanLineSeries = new QLineSeries();
	chart->addSeries(meanLineSeries);
	meanLineSeries->setName("Mean");
	meanLineSeries->attachAxis(xAxis);
	meanLineSeries->attachAxis(yAxis);
	QPen meanPen;
    meanPen.setWidthF(1.0);
    meanPen.setColor(Qt::red);
    meanLineSeries->setPen(meanPen);

	walshMedLineSeries = new QLineSeries();
	chart->addSeries(walshMedLineSeries);
	walshMedLineSeries->setName("Walsh av. med.");
	walshMedLineSeries->attachAxis(xAxis);
	walshMedLineSeries->attachAxis(yAxis);
	QPen walshMedPen;
    walshMedPen.setWidthF(1.0);
    walshMedPen.setColor(Qt::darkBlue);
    walshMedPen.setDashPattern({10, 6});
    walshMedLineSeries->setPen(walshMedPen);

	standatrDeviationLineSeries = new QLineSeries();
	chart->addSeries(standatrDeviationLineSeries);
	standatrDeviationLineSeries->setName("St. dev.");
	standatrDeviationLineSeries->attachAxis(xAxis);
	standatrDeviationLineSeries->attachAxis(yAxis);
	QPen variancePen;
    variancePen.setDashPattern({10, 6});
    variancePen.setWidthF(1);
    variancePen.setColor(Qt::magenta);
    standatrDeviationLineSeries->setPen(variancePen);

	medLineSeries = new QLineSeries();
	chart->addSeries(medLineSeries);
	medLineSeries->setName("Med.");
	medLineSeries->attachAxis(xAxis);
	medLineSeries->attachAxis(yAxis);
	QPen medPen;
    medPen.setWidthF(1.5);
    medPen.setColor(Qt::darkGreen);
    medPen.setDashPattern({10, 6});
    medLineSeries->setPen(medPen);

	coordinatesLabel = new QLabel("", this);
	coordinatesLabel->setAlignment(Qt::AlignCenter);
	coordinatesLabel->setStyleSheet("color: black; font-size: 11px;");
	coordinatesLabel->setAlignment(Qt::AlignHCenter | Qt::AlignRight);
}

void ChartViewBase::fill(ClassSeries* cs) {
	lowerBarAreaSeries->clear();
	lowerBarAreaSeries->append(cs->dataVector->min(), 0);
	lowerBarAreaSeries->append(cs->dataVector->max(), 0);

	meanLineSeries->clear();
	meanLineSeries->append(cs->dataVector->mean(), 0);
	meanLineSeries->append(cs->dataVector->mean(), 1);
	meanLineSeries->setName(QString("Mean %1").arg(cs->dataVector->mean(), 0, 'f', 3));

	standatrDeviationLineSeries->clear();
	standatrDeviationLineSeries->append(cs->dataVector->mean() - cs->dataVector->standardDeviation(), 1);
	standatrDeviationLineSeries->append(cs->dataVector->mean() - cs->dataVector->standardDeviation(), -1);
	standatrDeviationLineSeries->append(cs->dataVector->mean() + cs->dataVector->standardDeviation(), -1);
	standatrDeviationLineSeries->append(cs->dataVector->mean() + cs->dataVector->standardDeviation(), 1);
	standatrDeviationLineSeries->setName(QString("St. dev. %1").arg(cs->dataVector->standardDeviation(), 0, 'f', 3));

	medLineSeries->clear();
	medLineSeries->append(cs->dataVector->med(), 0);
	medLineSeries->append(cs->dataVector->med(), 1);
	medLineSeries->setName(QString("Med. %1").arg(cs->dataVector->med(), 0, 'f', 3));

	walshMedLineSeries->clear();
	walshMedLineSeries->append(cs->dataVector->walshAveragesMed(), 0);
	walshMedLineSeries->append(cs->dataVector->walshAveragesMed(), 1);
	walshMedLineSeries->setName(QString("Walsh av. med. %1").arg(cs->dataVector->walshAveragesMed(), 0, 'f', 3));

	xAxis->setTickCount(cs->classCount()+1);

	xAxis->setRange(cs->dataVector->min(), cs->dataVector->max());
}

void ChartViewBase::mouseMoveEvent(QMouseEvent *event) {
    QPointF point = event->pos();
    QPointF chartPoint = chart->mapToValue(point);
	QSize labelSize;

	if (chartPoint.x() >= xAxis->min() && chartPoint.x() <= xAxis->max() &&
			chartPoint.y() >= yAxis->min() && chartPoint.y() <= yAxis->max()) {
			coordinatesLabel->setVisible(true);
		coordinatesLabel->setText(QString("%1\n%2")
				.arg(chartPoint.x(), 3, 'f', 3)
				.arg(chartPoint.y(), 3, 'f', 3));
		coordinatesLabel->adjustSize();
		labelSize = coordinatesLabel->size();
		coordinatesLabel->move(point.x() - labelSize.width()-5, 
				point.y()-labelSize.height()-5);
	} else {
		coordinatesLabel->setVisible(false);
	}

    QChartView::mouseMoveEvent(event);
}

ClassSeries* ChartViewBase::classSeries() {
	return cs;
}
