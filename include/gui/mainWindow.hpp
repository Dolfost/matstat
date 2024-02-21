#ifndef _MAIN_WINDOW_HPP_
#define _MAIN_WINDOW_HPP_

#include <QMainWindow>
#include <QtWidgets/qboxlayout.h>

#include "statistics/dataSeries.hpp"
#include "statistics/dataVector.hpp"
#include "statistics/classSeries.hpp"

#include "statistics/densityChart.hpp"
#include "statistics/distributionChart.hpp"

class MainWindow : public QMainWindow {
public:
	MainWindow(QWidget* parent = nullptr);

private:
	QWidget* mainWidget = nullptr;
	QVBoxLayout* mainLayout = nullptr;

	QString filepath;
	DataSeries* dataSeries = nullptr;
	DataVector* dataVector = nullptr;
	ClassSeries* classSeries = nullptr;

	DensityChart* densityChart = nullptr;
	DistributionChart* distributionChart = nullptr;

	QTextEdit* dataReportTextEdit = nullptr;

	void createActions();

private slots:
	void open();
	void updateGui();
};

#endif // !_MAIN_WINDOW_HPP_
