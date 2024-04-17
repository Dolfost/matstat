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

#include "QCustomPlot/qcustomplot.h"
#include "dataVector.hpp"
#include "classSeries.hpp"

class PlotBase : public QCustomPlot {
	Q_OBJECT
public:
	PlotBase(QWidget* parent = nullptr);

	DataVector* dataVector();

	void enableMean();
	void plotMean();

	void enableStandartDeviation();
	void plotStandartDeviation();

	void enableMed();
	void plotMed();

	void enableWalshMed();
	void plotWalshMed();

	DataVector* dv = nullptr;

	QSharedPointer<QCPAxisTickerFixed> xFixedTicker;
	QSharedPointer<QCPAxisTicker> xTicker;
	QSharedPointer<QCPAxisTicker> yTicker;
	QSharedPointer<QCPAxisTickerLog> yLogTicker;
	QCPRange xRange;
	QCPRange xRange2;
	QCPRange yRange;
	QCPRange yRange2;

	QCPScatterStyle scatterStyle;
	QPen scatterPen;
	QCPGraph* mean = nullptr;
	QCPGraph* standatrDeviation = nullptr;
	QCPGraph* med = nullptr;
	QCPGraph* walshMed = nullptr;

	QCPTextElement* title = nullptr;

	QString coordinatesLabelString = "${X}\n${Y}";
private:
	QLabel* coordinatesLabel = nullptr;
	QTimer* coordinatesTimer = nullptr;

private slots:
	void handleZoomX(const QCPRange & newRange);
	void handleZoomX2(const QCPRange & newRange);
	void handleZoomY(const QCPRange & newRange);
	void handleZoomY2(const QCPRange& newRange);

public slots:
	void toggleLog(bool state);
	void zoomHome();
	void clear();

protected:
	void mouseMoveEvent(QMouseEvent*) override;

	void fill(DataVector*);
};

#endif // !_CHART_BASE_HPP_
