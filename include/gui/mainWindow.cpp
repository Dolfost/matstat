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
	dataVector = new DataVector({});
	classSeries = new ClassSeries(dataVector);

	createActions();

	QTabWidget* tabWidget = new QTabWidget();
	tabWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
	tabWidget->setDocumentMode(true);
	mainLayout->addWidget(tabWidget);
	QWidget* objectsTab = new QWidget();
	QWidget* dataReportTab = new QWidget();
	tabWidget->addTab(objectsTab, "Objects");
	tabWidget->addTab(dataReportTab, "Data report");
	QHBoxLayout* objectsTabLayout = new QHBoxLayout();
	QHBoxLayout* dataReportTabLayout = new QHBoxLayout();
	objectsTab->setLayout(objectsTabLayout);
	dataReportTab->setLayout(dataReportTabLayout);

	QCheckBox* box = new QCheckBox();
	objectsTabLayout->addWidget(box);
}

void MainWindow::createActions() {
	QMenu *fileMenu = menuBar()->addMenu("File");
	QMenu *viewMenu = menuBar()->addMenu("View");

    QAction* openAct = new QAction("Open...", this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip("Open an data vector");
    connect(openAct, &QAction::triggered, this, &MainWindow::open);
    fileMenu->addAction(openAct);

	QAction* toogleLogAct = new QAction("Log grid", this);
	toogleLogAct->setCheckable(true);
	openAct->setStatusTip("Toogle Log grid");
	connect(toogleLogAct, &QAction::toggled, densityChart, &DensityChart::toggleLog);
	viewMenu->addAction(toogleLogAct);
}

void MainWindow::open() {
	QString filepath = QFileDialog::getOpenFileName(this,
		"Open vector", QDir::homePath(), "Text files (*.txt *.csv *.DAT)");
	dataSeries->readData(filepath);
	this->statusBar()->showMessage(dataSeries->message());
	dataVector->setVector(dataSeries->series()[0]);

	updateGui();
}

void MainWindow::updateGui() {
	classSeries->makeSeries();

	densityChart->fill(classSeries);
	distributionChart->fill(classSeries);
}
