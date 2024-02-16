#ifndef _GRAPH_HPP_
#define _GRAPH_HPP_

#include <QChart>
#include <QChartView>

#include "classseries.hpp"

class BarChart {
public:
    BarChart(ClassSeries* cs);

    QChartView* createChart(QWidget* parent = nullptr);

private:

	ClassSeries* classSeries = nullptr;
};

#endif // !_GRAPH_HPP_
