#ifndef _CHART_VIEW_BASE_HPP_
#define _CHART_VIEW_BASE_HPP_

#include <QtCharts/qbarseries.h>
#include <QtCharts/qbarset.h>
#include <QtCharts/qchart.h>
#include <QChartView>
#include <QAreaSeries>
#include <QSplineSeries>
#include <QtCharts/qvalueaxis.h>
#include <QtWidgets/qlabel.h>
#include <QLogValueAxis>

#include "classSeries.hpp"

#include "QCustomPlot/qcustomplot.h"

class PlotBase : public QCustomPlot {
	Q_OBJECT
public:
	PlotBase(QWidget* parent = nullptr);

	ClassSeries* classSeries();

	ClassSeries* cs = nullptr;

	QCPBars* bars = nullptr;

	QSharedPointer<QCPAxisTickerFixed> xFixedTicker;
	QSharedPointer<QCPAxisTicker> yTicker;
	QSharedPointer<QCPAxisTickerLog> yLogTicker;

	QSplineSeries* continiousSplineSeries = nullptr;

	QLineSeries* meanLineSeries = nullptr;

	QLineSeries* standatrDeviationLineSeries = nullptr;

	QLineSeries* medLineSeries = nullptr;

	QLineSeries* walshMedLineSeries = nullptr;
private:
	QLabel* coordinatesLabel = nullptr;

private slots:
	void handleZoomX(const QCPRange &  newRange);
	void handleZoomY(const QCPRange &  newRange);

protected:
	void mouseMoveEvent(QMouseEvent*) override;

	void fill(ClassSeries* cs);
};

#endif // !_CHART_BASE_HPP_
