#ifndef _MAIN_WINDOW_HPP_
#define _MAIN_WINDOW_HPP_

#include <QMainWindow>
#include <QtWidgets/qboxlayout.h>

#include "statistics/dataSeries.hpp"
#include "statistics/dataVector.hpp"
#include "statistics/classSeries.hpp"

#include "statistics/densityChart.hpp"
#include "statistics/distributionChart.hpp"

#include "vectorContainerWidget.hpp"
#include "vectorProcessorWidget.hpp"
#include "vectorPickerDialog.hpp"

#include "guiTypes.hpp"

class MainWindow : public QMainWindow {
	Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = nullptr);

private:
	QWidget* mainWidget = nullptr;
	QVBoxLayout* mainLayout = nullptr;
	QSplitter* mainSplitter = nullptr;

	QString filepath;
	DataSeries* dataSeries = nullptr;
	DataVector* dataVector = nullptr;
	ClassSeries* classSeries = nullptr;

	DensityChart* densityChart = nullptr;
	DistributionChart* distributionChart = nullptr;

	VectorContainerWidget* vectorContainer = nullptr;
	VectorProcessorWidget* vectorProcessor = nullptr;
	VectorPickerDialog* vectorPicker = nullptr;

	void createCharts();
	void createVectorContainers();
	void createActions();

	int messageTime = 4000;

private slots:
	void open();
	void openVectorPicker();
	void updateGui();

	void setActiveVector(VectorEntry*);

	// handlers
	void outliersRemovedHandler(bool);
};

#endif // !_MAIN_WINDOW_HPP_
