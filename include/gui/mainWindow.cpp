#include "mainWindow.hpp"

#include "statistics/dataSeries.hpp"
#include "statistics/dataVector.hpp"
#include "statistics/classSeries.hpp"

#include "statistics/densityChart.hpp"
#include "statistics/distributionChart.hpp"

#include <QWidget>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
	mainWidget = new QWidget();
	mainLayout = new QVBoxLayout();
	mainLayout->setContentsMargins(0,0,0,0);
	mainWidget->setLayout(mainLayout);
	this->setCentralWidget(mainWidget);

	QHBoxLayout* chartsLayout = new QHBoxLayout();
	mainLayout->addItem(chartsLayout);

	densityChart = new DensityChart(this);
	distributionChart = new DistributionChart(this);

	chartsLayout->addWidget(densityChart);
	chartsLayout->addWidget(distributionChart);

	dataSeries = new DataSeries();
	dataVector = new DataVector();
	classSeries = new ClassSeries(dataVector);

	createActions();

	QTabWidget* tabWidget = new QTabWidget();
	tabWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	tabWidget->setDocumentMode(true);
	mainLayout->addWidget(tabWidget);
	QWidget* objectsTab = new QWidget();
	QWidget* dataReportTab = new QWidget();
	tabWidget->addTab(objectsTab, "Обʼєкти даних");
	tabWidget->addTab(dataReportTab, "Звіт");
	QHBoxLayout* objectsTabLayout = new QHBoxLayout();
	QHBoxLayout* dataReportTabLayout = new QHBoxLayout();
	objectsTab->setLayout(objectsTabLayout);
	dataReportTab->setLayout(dataReportTabLayout);

	dataReportTextEdit = new QTextEdit();
	dataReportTabLayout->addWidget(dataReportTextEdit);

	QCheckBox* box = new QCheckBox();
	objectsTabLayout->addWidget(box);
}

void MainWindow::createActions() {
	QMenu *fileMenu = menuBar()->addMenu("Файл");
	QMenu *viewMenu = menuBar()->addMenu("Вигляд");

    QAction* openAct = new QAction("Відкрити...", this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip("Open an data vector");
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);

	QAction* toogleDensityLogAct = new QAction("Логарифмічна сітка щільності", this);
	toogleDensityLogAct->setCheckable(true);
	connect(toogleDensityLogAct, &QAction::toggled, densityChart, &DensityChart::toggleLog);
	viewMenu->addAction(toogleDensityLogAct);

	QAction* toogleDistributionLogAct = new QAction("Логарифмічна сітка розподілу", this);
	toogleDistributionLogAct->setCheckable(true);
	connect(toogleDistributionLogAct, &QAction::toggled, distributionChart, &DistributionChart::toggleLog);
	viewMenu->addAction(toogleDistributionLogAct);
}

void MainWindow::open() {
	filepath = QFileDialog::getOpenFileName(this,
		"Відкрити вектор", QDir::homePath(), "Text files (*.txt *.csv *.DAT)");
	dataSeries->readData(filepath);
	this->statusBar()->showMessage(dataSeries->message());
	dataVector->setVector(dataSeries->series()[0]);

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
