#include "mainWindow.hpp"

#include "setGeneratorDialog.hpp"
#include "vectorContainerWidget.hpp"

#include <QWidget>
#include <QGroupBox>

#include <QtWidgets/qmenubar.h>
#include <dataSeries.hpp>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	mainWidget = new QWidget();
	mainLayout = new QVBoxLayout();
	mainLayout->setContentsMargins(0,0,0,0);
	mainWidget->setLayout(mainLayout);
	this->setCentralWidget(mainWidget);

	createVectorContainers();
	createActions();

	vectorPicker = new VectorPickerDialog(this);

	this->resize(900,800);

	connect(this->vectorPicker, SIGNAL(vectorSelected(const std::list<double>&)),
				 vectorContainer, SLOT(placeList(const std::list<double>&)));

	connect(this->vectorContainer, &VectorContainerWidget::outliersRemoved,
				 this, &MainWindow::outliersRemovedHandler);
	connect(this->vectorContainer, SIGNAL(message(QString)),
				 this, SLOT(showMessage(QString)));

	_addFile("../../../data/500/norm3n.txt");
	_addFile("../../../data/500/norm.txt");
	_addFile("../../../data/500/exp.txt");
	_addFile("../../../data/500/veib.txt");
	// _addFile("../../../data/500/exp1.txt");
	// _addFile("../../../data/500/ravn1.txt");
	// _addFile("../../../data/25/exp.txt");
	// _addFile("../../../data/25/norm.txt");
	// _addFile("../../../data/25/veib.txt");
	// _addFile("../../../data/qtest/TR1(V10)-120.txt");
	// _addFile("../../../data/qtest/TR2(V11)-120.txt");
	// _addFile("../../../data/qtest/TR3(V12)-120.txt");
	// _addFile("../../../data/qtest/TR4(V13)-120.txt");
	// _addFile("../../../data/qtest/TR5(V14)-120.txt");
}

void MainWindow::createVectorContainers() {
	QWidget* containersWidget = new QWidget;
	containersWidget->setLayout(new QHBoxLayout);
	containersWidget->layout()->setContentsMargins(0,0,0,0);
	containersWidget->layout()->setSpacing(0);

	QGroupBox* objectsBox = new QGroupBox("Вектори даних");
	QVBoxLayout* objectsLayout = new QVBoxLayout();
	objectsLayout->setContentsMargins(0,0,0,0);
	objectsBox->setLayout(objectsLayout);
	vectorContainer = new VectorContainerWidget();
	objectsLayout->addWidget(vectorContainer);

	containersWidget->layout()->addWidget(objectsBox);

	mainLayout->addWidget(containersWidget);

	setGenerator = new SetGeneratorDialog(this, false);
	setGenerator->hide();
	setGenerator->setAttribute(Qt::WA_DeleteOnClose, false);
	connect(setGenerator, &SetGeneratorDialog::vectorGenerated,
				 vectorContainer, &VectorContainerWidget::appendVector);
	connect(setGenerator, &SetGeneratorDialog::vectorPairGenerated,
				 vectorContainer, &VectorContainerWidget::appendVectorPair);
}

void MainWindow::createActions() {
	QMenu *fileMenu = menuBar()->addMenu("Файл");

	QAction* openAct = new QAction("Відкрити…", this);
	openAct->setShortcuts(QKeySequence::Open);
	connect(openAct, &QAction::triggered, this, &MainWindow::open);
	fileMenu->addAction(openAct);

	QAction* openVectorPickerAct = new QAction("Менеджер векторів…", this);
	connect(openVectorPickerAct, &QAction::triggered, this, &MainWindow::openVectorPicker);
	fileMenu->addAction(openVectorPickerAct);



	QMenu *toolsMenu = menuBar()->addMenu("Інструменти");
	QAction* generateSetAction = new QAction("Генератор вибірок…", this);
	connect(generateSetAction, &QAction::triggered,
				 this, &MainWindow::openSetGenerator);
	toolsMenu->addAction(generateSetAction);
}

void MainWindow::open() {
	filepath = QFileDialog::getOpenFileName(this,
																				 "Відкрити вектор", QDir::homePath(), "Data files (*.txt *.csv *.DAT)");
	// filepath = "/Users/vladyslav/Lib/NAU/Mathematical_statistics/Labs/data/500/exp.txt"; 
	// filepath = "/Users/vladyslav/Lib/NAU/Mathematical_statistics/Labs/data/500/norm3n.txt"; 
	// filepath = "/Users/vladyslav/Lib/NAU/Mathematical_statistics/Labs/data/norm1_anomaly.txt"; 
	// filepath = "/Users/vladyslav/Lib/NAU/Mathematical_statistics/Labs/data/200/LOGNORM.DAT"; 
	// filepath = "/Users/vladyslav/Lib/NAU/Mathematical_statistics/Labs/data/200/VEIBUL.DAT"; 
	// filepath = "/Users/vladyslav/Lib/NAU/Mathematical_statistics/Labs/data/500/ravn.txt"; 
	// filepath = "/Users/vladyslav/Lib/NAU/Mathematical_statistics/Labs/data/500/veib.txt"; 

	if (filepath.size() == 0)
		return;

	vectorPicker->fileContents(filepath);
	openVectorPicker();
}


void MainWindow::openVectorPicker() {
	vectorPicker->show();
	//  NOTE: keep an eye on this comments
	// this->setFocus();
	// vectorPicker->setFocus();
	// vectorPicker->activateWindow();
}

void MainWindow::openSetGenerator() {
	setGenerator->show();
}

void MainWindow::outliersRemovedHandler(bool ok) {
	QString msg;
	if (ok)
		msg = "Аномалії прибрано.";
	else
		msg = "В результаті вилучення аномалій, вектор не змінився.";

	this->showMessage(msg);
}


void MainWindow::showMessage(QString msg, int dur) {
	if (dur == 0)
		dur = messageTime;

	this->statusBar()->showMessage(msg, dur);
}

void MainWindow::_addFile(QString file) {
	DataSeries s;
	std::string ans;
	try {
		s.readData(file.toStdString());
	} catch (std::exception& ex) {
		qDebug() << QString(__func__) + ":" << ex.what();
		return;
	}

	Vector* ve = new Vector;
	ve->setVector(new ss::Vector(s.filewiseSeries()));
	vectorContainer->appendVector(ve);
}

