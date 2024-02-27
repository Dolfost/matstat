#include "mainWindow.hpp"

#include "gui/vectorContainer.hpp"
#include "statistics/dataSeries.hpp"
#include "statistics/dataVector.hpp"
#include "statistics/classSeries.hpp"

#include "statistics/densityChart.hpp"
#include "statistics/distributionChart.hpp"

#include <QWidget>
#include <QtCore/qnamespace.h>

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

	vectorPicker = new VectorPicker(this);

	this->resize(900,800);

	updateGui();

	connect(this->vectorPicker, &VectorPicker::vectorSelected,
			vectorContainer, &VectorContainer::appendVector);
	connect(this->vectorContainer, &VectorContainer::vectorSelected,
			this, &MainWindow::setActiveVector);

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
	QTabWidget* tabWidget = new QTabWidget();
	tabWidget->setDocumentMode(true);
	QWidget* objectsTab = new QWidget();
	QWidget* dataReportTab = new QWidget();
	tabWidget->addTab(objectsTab, "Обʼєкти даних");
	tabWidget->addTab(dataReportTab, "Звіт");
	QHBoxLayout* objectsTabLayout = new QHBoxLayout();
	objectsTabLayout->setContentsMargins(0,0,0,0);
	QHBoxLayout* dataReportTabLayout = new QHBoxLayout();
	dataReportTabLayout->setContentsMargins(0,0,0,0);
	objectsTab->setLayout(objectsTabLayout);
	dataReportTab->setLayout(dataReportTabLayout);

	dataReportTextEdit = new QTextEdit();
	dataReportTextEdit->setReadOnly(true);
	dataReportTabLayout->addWidget(dataReportTextEdit);

	vectorContainer = new VectorContainer();
	objectsTabLayout->addWidget(vectorContainer);

	mainSplitter->addWidget(tabWidget);
}

void MainWindow::createActions() {
	QMenu *fileMenu = menuBar()->addMenu("Файл");
	QMenu *viewMenu = menuBar()->addMenu("Вигляд");

    QAction* openAct = new QAction("Відкрити...", this);
    openAct->setShortcuts(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);

    QAction* openVectorPickerAct = new QAction("Менеджер векторів", this);
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
	// 	"Відкрити вектор", QDir::homePath(), "Text files (*.txt *.csv *.DAT)");
	filepath = "/Users/vladyslav/Lib/NAU/Mathematical_statistics/Labs/data/500/norm3n.txt"; 

	vectorPicker->fileContents(filepath);
	openVectorPicker();

	updateGui();
}

void MainWindow::updateGui() {
	classSeries->makeSeries();

	densityChart->fill(classSeries);
	distributionChart->fill(classSeries);

	dataReportTextEdit->clear();
	dataReportTextEdit->append("File " + filepath + "\n");
	dataReportTextEdit->append(dataVector->report());
}

void MainWindow::setActiveVector(DataVector* dv) {
	dataVector->setVector(dv->vector());
	updateGui();
}

void MainWindow::openVectorPicker() {
	vectorPicker->show();
	this->setFocus();
	vectorPicker->setFocus();
	vectorPicker->activateWindow();
}
