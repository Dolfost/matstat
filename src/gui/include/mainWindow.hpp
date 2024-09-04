#ifndef _MAIN_WINDOW_HPP_
#define _MAIN_WINDOW_HPP_

#include <QMainWindow>
#include <QtCore/qlist.h>
#include <QtWidgets/qboxlayout.h>
#include <QSplitter>


#include "vectorContainerWidget.hpp"
#include "vectorProcessorWidget.hpp"
#include "vectorPickerDialog.hpp"
#include "setGeneratorDialog.hpp"
#include "charts.hpp"

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

	VectorContainerWidget* vectorContainer = nullptr;
	VectorProcessorWidget* vectorProcessor = nullptr;
	VectorPickerDialog* vectorPicker = nullptr;
	SetGeneratorDialog* setGenerator = nullptr;
	Charts* charts = nullptr;

	void createCharts();
	void createVectorContainers();
	void createActions();

	int messageTime = 4000;

	void _addFile(QString);

private slots:
	void open();
	void openVectorPicker();
	void openSetGenerator();


	// handlers
	void outliersRemovedHandler(bool);
	void vectorProcessorDuplicateHandler(VectorEntry*,
			Tab);

	void showMessage(QString, int = 4000);
};

#endif // !_MAIN_WINDOW_HPP_
