#include "mainWindow.hpp"

#include "gui/vectorContainerWidget.hpp"
#include "statistics/dataSeries.hpp"
#include "statistics/dataVector.hpp"
#include "statistics/classSeries.hpp"

#include "statistics/densityChart.hpp"
#include "statistics/distributionChart.hpp"

#include <QWidget>
#include <QtCore/qnamespace.h>
#include <QtWidgets/qgroupbox.h>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	mainWidget = new QWidget();
	mainLayout = new QVBoxLayout();
	mainLayout->setContentsMargins(0,0,0,0);
	mainWidget->setLayout(mainLayout);
	this->setCentralWidget(mainWidget);

	mainSplitter = new QSplitter;
	mainSplitter->setOrientation(Qt::Vertical);
	mainSplitter->setHandleWidth(12);

	createCharts();
	createVectorContainers();
	createActions();

	mainLayout->addWidget(mainSplitter);

	vectorPicker = new VectorPickerDialog(this);

	this->resize(900,800);

	updateGui();

	connect(this->vectorPicker, SIGNAL(vectorSelected(const std::list<double>*)),
			vectorContainer, SLOT(appendList(const std::list<double>*)));

	connect(this->vectorContainer, &VectorContainerWidget::vectorSelected,
			vectorProcessor, &VectorProcessorWidget::appendVector);
	connect(this->vectorContainer, &VectorContainerWidget::outliersRemoved,
			this, &MainWindow::outliersRemovedHandler);

	connect(this->vectorProcessor, &VectorProcessorWidget::duplicateAdded,
			this, &MainWindow::vectorProcessorDuplicateHandler);

	open();
}

void MainWindow::createCharts() {
	QWidget* chartWidget = new QWidget();
	QHBoxLayout* chartsLayout = new QHBoxLayout();
	chartsLayout->setSpacing(0);
	chartsLayout->setContentsMargins(0,0,0,0);
	chartWidget->setLayout(chartsLayout);

	densityChart = new DensityChart(this);
	distributionChart = new DistributionChart(this);

	chartsLayout->addWidget(densityChart);
	chartsLayout->addWidget(distributionChart);

	mainSplitter->addWidget(chartWidget);
	mainSplitter->setSizes({600, 300});

	dataSeries = new DataSeries();
	dataVector = new DataVector({});
	classSeries = new ClassSeries(dataVector);
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

	QGroupBox* processorBox = new QGroupBox("Візуалізація векторів");
	processorBox->setFixedWidth(280);
	QVBoxLayout* processorLayout = new QVBoxLayout();
	processorLayout->setContentsMargins(0,0,0,0);
	processorBox->setLayout(processorLayout);
	vectorProcessor = new VectorProcessorWidget();
	processorLayout->addWidget(vectorProcessor);

	containersWidget->layout()->addWidget(processorBox);
	containersWidget->layout()->addWidget(objectsBox);

	mainSplitter->addWidget(containersWidget);
}

void MainWindow::createActions() {
	QMenu *fileMenu = menuBar()->addMenu("Файл");
	QMenu *viewMenu = menuBar()->addMenu("Вигляд");

    QAction* openAct = new QAction("Відкрити…", this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);

    QAction* openVectorPickerAct = new QAction("Менеджер векторів…", this);
    connect(openVectorPickerAct, &QAction::triggered, this, &MainWindow::openVectorPicker);
    fileMenu->addAction(openVectorPickerAct);


	QAction* toogleDensityLogAct = 
		new QAction("Логарифмічна сітка щільності", this);
	toogleDensityLogAct->setCheckable(true);
	connect(toogleDensityLogAct, &QAction::toggled,
			densityChart, &DensityChart::toggleLog);
	viewMenu->addAction(toogleDensityLogAct);

	QAction* toogleDistributionLogAct =
		new QAction("Логарифмічна сітка розподілу", this);
	toogleDistributionLogAct->setCheckable(true);
	connect(toogleDistributionLogAct, &QAction::toggled,
			distributionChart, &DistributionChart::toggleLog);
	viewMenu->addAction(toogleDistributionLogAct);

	QAction* zoomHomeAction = new QAction("Відмаштабувати графіки", this);
	connect(zoomHomeAction, &QAction::triggered,
			densityChart, &DensityChart::zoomHome);
	connect(zoomHomeAction, &QAction::triggered,
			distributionChart, &DistributionChart::zoomHome);
	viewMenu->addAction(zoomHomeAction);

	QAction* clearPlotsAction = new QAction("Очистити графіки", this);
	connect(clearPlotsAction, &QAction::triggered,
			densityChart, &DensityChart::clear);
	connect(clearPlotsAction, &QAction::triggered,
			distributionChart, &DistributionChart::clear);
	viewMenu->addAction(clearPlotsAction);
}

void MainWindow::open() {
	// filepath = QFileDialog::getOpenFileName(this,
		// "Відкрити вектор", QDir::homePath(), "Text files (*.txt *.csv *.DAT)");
	filepath = "/Users/vladyslav/Lib/NAU/Mathematical_statistics/Labs/data/500/norm3n.txt"; 

	vectorPicker->fileContents(filepath);
	openVectorPicker();

	updateGui();
}

void MainWindow::updateGui() {
	classSeries->makeSeries();

	densityChart->fill(classSeries);
	distributionChart->fill(classSeries);
}

void MainWindow::setActiveVector(VectorEntry* vectorEntry) {
	dataVector->setVector(vectorEntry->vector->vector());
	updateGui();
}

void MainWindow::openVectorPicker() {
	vectorPicker->show();
	this->setFocus();
	vectorPicker->setFocus();
	vectorPicker->activateWindow();
}

void MainWindow::outliersRemovedHandler(bool ok) {
	QString msg;
	if (ok)
		msg = "Аномалії прибрано.";
	else
		msg = "В результаті вилучення аномалій, вектор не змінився.";

	this->statusBar()->showMessage(msg, messageTime);
}

void MainWindow::vectorProcessorDuplicateHandler(VectorEntry* vectorEntry,
		VectorProcessorWidget::Tab t) {
	this->statusBar()->showMessage("Вектор '" + vectorEntry->name + 
			"' вже доданий до вкладки " + vectorProcessor->tabName[t],
			messageTime);
}
