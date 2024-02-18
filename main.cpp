#include <QApplication>
#include <QDebug>
#include <QtCore/qlogging.h>
#include <QtWidgets/qdialog.h>
#include <QtWidgets/qmainwindow.h>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QChartView>
#include <QCheckBox>

#include "statistics/dataSeries.hpp"
#include "statistics/varSeries.hpp"
#include "statistics/classSeries.hpp"
#include "statistics/densityChart.hpp"
#include "statistics/distributionChart.hpp"

#include "types.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

	QMainWindow mainWindow;

	// QString filepath = QFileDialog::getOpenFileName(&mainWindow,
    // "Open data", QDir::homePath(), "Text files (*.txt *.csv)");

	DataSeries* ds = new DataSeries();
	Status ok = ds->readData("/Users/vladyslav/Lib/NAU/Mathematical_statistics/Labs/data/500/exp1.txt");

	qDebug() << ds->message();
	qDebug() << "DATA SERIES:"; for (auto& i : ds->series()) {
		qDebug() << i;
	}
	qDebug() << "Status: " << static_cast<int>(ok);

	DataVector* dv = new DataVector(ds->series()[0]);

	qDebug() << "1st DATA VECTOR: max = " + QString::number(dv->max()) + " min = " + QString::number(dv->min());
	int j = 0;
	for (auto const& i : dv->vector()) {
		qDebug() << "idx " << j+1 << "val" << i;
		j++;
	}

	VarSeries* vs = new VarSeries(dv);
	vs->makeSeries();

	qDebug() << "VAR SERIES:";
	for (auto const& [key, val] : vs->series()) {
		qDebug() << key << val.first << val.second;
	}
	qDebug() << "xmin:" << vs->dataVector->min() << "xmax:" << vs->dataVector->max();
	qDebug() << "r:" << vs->variantsCount() << " N:" << vs->dataVector->size();


	ClassSeries* cs = new ClassSeries(dv);
	cs->makeSeries();

	qDebug() << "class count" << cs->classCount() << "step" << cs->step();
	qDebug() << "CLASS SERIES";

	j = 0;
	for (auto const& i : cs->series()) {
		qDebug() << "in (" + QString::number(cs->dataVector->min() + j*cs->step()) + ";"+ QString::number(cs->dataVector->min() + (j+1)*(cs->step())) + "]" << i.first << i.second;
		j++;
	}

	// qDebug() << "mad: " << dv->mad() << "skew: " << dv->skew() << "kurtosis: " << dv->kurtosis() << "walsh_med" << dv->walshAveragesMed() << "covar coef" << dv->variationCoef();
	qDebug() << "variance" << dv->variance() << "med" << dv->med();

	QHBoxLayout* layout = new QHBoxLayout();
	QVBoxLayout* layout2 = new QVBoxLayout();
	QCheckBox* logCheckBox = new QCheckBox("log grid");

	DensityChart* densityChart = new DensityChart();
	densityChart->fill(cs);
	

	DistributionChart* distributionChart = new DistributionChart();
	distributionChart->fill(cs);

	QObject::connect(logCheckBox, &QCheckBox::stateChanged, densityChart, &DensityChart::toggleLog);
	QObject::connect(logCheckBox, &QCheckBox::stateChanged, distributionChart, &DistributionChart::toggleLog);

	layout->setContentsMargins(0,0,0,0);
	layout->addWidget(densityChart);
	layout->addWidget(distributionChart);

	layout2->addLayout(layout);
	layout2->addWidget(logCheckBox);

	QWidget* centralWidget = new QWidget(&mainWindow);
	centralWidget->setLayout(layout2);

	mainWindow.setCentralWidget(centralWidget);
	mainWindow.setMinimumSize(600, 800);
	mainWindow.show();

	// QDialog* dia = new QDialog();
	// dia->setFixedSize(50, 50);
	// dia->exec();
	//
	// dv->standardize();
	// cs->makeSeries();
	// distributionChart->fill(cs);
	// frequencyChart->fill(cs);

    return app.exec();
}

