#ifndef _MAIN_WINDOW_HPP_
#define _MAIN_WINDOW_HPP_

#include <QMainWindow>
#include <QtCore/qlist.h>
#include <QtWidgets/qboxlayout.h>


#include "vectorContainerWidget.hpp"
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

	QString filepath;

	VectorContainerWidget* vectorContainer = nullptr;
	VectorPickerDialog* vectorPicker = nullptr;
	SetGeneratorDialog* setGenerator = nullptr;

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

	void showMessage(QString, int = 4000);
};

#endif // !_MAIN_WINDOW_HPP_
