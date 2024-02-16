#include <QChart>
#include <QBarSet>
#include <QBarSeries>
#include <QLineSeries>
#include <QChartView>
#include <QValueAxis>
#include <cmath>

#include "classseries.hpp"
#include "chart.hpp"

BarChart::BarChart(ClassSeries* cs) {
	classSeries = cs;
}

QChartView* BarChart::createChart(QWidget* parent) {
	QBarSet *barSet = new QBarSet("Distribution");
	for (auto const& i: classSeries->series()) {
		*barSet << i.first;
	}

	QBarSeries *series = new QBarSeries();
	series->setBarWidth(1);
	series->append(barSet);

	QChart *chart = new QChart();
	chart->setTitle("Distribution Chart");

	QValueAxis *axisX = new QValueAxis();
	chart->addAxis(axisX, Qt::AlignBottom);
	axisX->setTickCount(classSeries->classCount()+1);
	axisX->setRange(classSeries->seriesMin(), classSeries->seriesMax());
	axisX->setLabelsAngle(90);
	// series->attachAxis(axisX);

	chart->addSeries(series);
	QValueAxis *axisY = new QValueAxis();
	chart->addAxis(axisY, Qt::AlignLeft);
	series->attachAxis(axisY);

	// // line
 //    QLineSeries* lineSeries = new QLineSeries();
 //    lineSeries->attachAxis(axisX);
 //    lineSeries->attachAxis(axisY);
 //    for (double x = classSeries->seriesMin(); x <= classSeries->seriesMax(); x += 0.01) {
 //        lineSeries->append(x, 10*sin(20*x));
 //    }
 //    chart->addSeries(lineSeries);

	QChartView *chartView = new QChartView(chart, parent);
	chartView->setRenderHint(QPainter::Antialiasing);

	return chartView;
}
