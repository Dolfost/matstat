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

class ChartViewBase : public QChartView {
	Q_OBJECT
public:
	ChartViewBase(QWidget* parent = nullptr);

	ClassSeries* classSeries();

	ClassSeries* cs = nullptr;

	QChartView* chartView;

	QChart* chart = nullptr;
	QValueAxis* xAxis = nullptr;
	QValueAxis* yAxis = nullptr;

	QAreaSeries* barAreaSeries = nullptr;
	QLineSeries* lowerBarAreaSeries = nullptr;
	QLineSeries* upperBarAreaSeries = nullptr;

	QSplineSeries* continiousSplineSeries = nullptr;

	QLineSeries* meanLineSeries = nullptr;

	QLineSeries* standatrDeviationLineSeries = nullptr;

	QLineSeries* medLineSeries = nullptr;

	QLineSeries* walshMedLineSeries = nullptr;
private:
	QLabel* coordinatesLabel = nullptr;

protected:
	void mouseMoveEvent(QMouseEvent*) override;

	void fill(ClassSeries* cs);
};

#endif // !_CHART_BASE_HPP_
