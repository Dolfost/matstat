#ifndef _DENSITY_CHART_HPP_
#define _DENSITY_CHART_HPP_

#include <QChart>
#include <QtCharts/qbarseries.h>

#include "classSeries.hpp"
#include "plotBase.hpp"

class DensityChart : public PlotBase {
	Q_OBJECT
public:
    DensityChart(QWidget* parent = nullptr);
	QCPBars* bars = nullptr;

	void fill(ClassSeries* clSr);
};

#endif // !_DENSITY_CHART_HPP_
