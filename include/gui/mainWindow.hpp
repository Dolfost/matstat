#ifndef _MAIN_WINDOW_HPP_
#define _MAIN_WINDOW_HPP_

#include <QMainWindow>
#include <QtWidgets/qboxlayout.h>

#include "statistics/densityChart.hpp"
#include "statistics/distributionChart.hpp"

#include "vectorContainerWidget.hpp"
#include "vectorProcessorWidget.hpp"
#include "vectorPickerDialog.hpp"
#include "setGeneratorDialog.hpp"

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

	DensityChart* densityChart = nullptr;
	DistributionChart* distributionChart = nullptr;

	VectorContainerWidget* vectorContainer = nullptr;
	VectorProcessorWidget* vectorProcessor = nullptr;
	VectorPickerDialog* vectorPicker = nullptr;
	SetGeneratorDialog* setGenerator = nullptr;

	void createCharts();
	void createVectorContainers();
	void createActions();

	int messageTime = 4000;

private slots:
	void open();
	void openVectorPicker();
	void openSetGenerator();

	void plot2D(VectorEntry*);

	// handlers
	void outliersRemovedHandler(bool);
	void vectorProcessorDuplicateHandler(VectorEntry*,
			VectorProcessorWidget::Tab);

	void showMessage(QString, int = 0);
};

#endif // !_MAIN_WINDOW_HPP_
