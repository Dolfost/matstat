#ifndef _RELATIVE_FREQUENCY_CHART_HPP_
#define _RELATIVE_FREQUENCY_CHART_HPP_

#include <QChart>
#include <QtCharts/qbarseries.h>

#include "classSeries.hpp"
#include "plotBase.hpp"

class RelativeFrequencyChart : public PlotBase {
	Q_OBJECT
public:
    RelativeFrequencyChart(QWidget* parent = nullptr);

	void fill(ClassSeries* clSr);
};

#endif // !_GRAPH_HPP_
