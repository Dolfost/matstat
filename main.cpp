#include <QApplication>
#include <QDebug>
#include <QtCore/qlogging.h>
#include <QtWidgets/qmainwindow.h>

#include "calculator.hpp"

#include "statistics/dataseries.hpp"
#include "statistics/varseries.hpp"
#include "statistics/classseries.hpp"
#include "statistics/chart.hpp"
#include "types.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    Calculator calculator(nullptr);

	// DataSeries* ds = new DataSeries();
	// Status ok = ds->readData("/Users/vladyslav/Lib/NAU/Mathematical_statistics/Labs/Lab_1/random_numbers2.txt");
	//
	// qDebug() << ds->message();
	// qDebug() << "DATA SERIES:";
	// for (auto& i : ds->series()) {
	// 	qDebug() << i;
	// }
	// qDebug() << "Status: " << static_cast<int>(ok);
	//
	//
	// VarSeries* vs = new VarSeries(ds);
	// vs->makeSeries();
	// 
	// qDebug() << "VAR SERIES:";
	// for (auto const& [key, val] : vs->series()) {
	// 	qDebug() << key << val.first << val.second;
	// }
	// qDebug() << "xmin:" << vs->seriesMin() << "xmax:" << vs->seriesMax();
	// qDebug() << "r:" << vs->size();
	//
	//
	// ClassSeries* cs = new ClassSeries(vs);
	// cs->makeSeries();
	//
	// qDebug() << "class count" << cs->classCount() << "step" << cs->step();
	// qDebug() << "CLASS SERIES";
	//
	// int j = 0;
	// for (auto const& i : cs->series()) {
	// 	qDebug() << "in (" + QString::number(cs->seriesMin() + j*cs->step()) + ";"+ QString::number(cs->seriesMin() + (j+1)*(cs->step())) + "]" << i.first << i.second;
	// 	j++;
	// }
	//
	// BarChart* bc = new BarChart(cs);
	// QChartView* cv = bc->createChart();

	calculator.show();

    return app.exec();
}

