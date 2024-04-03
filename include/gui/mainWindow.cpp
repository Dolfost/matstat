#include "mainWindow.hpp"

#include "gui/setGeneratorDialog.hpp"
#include "gui/vectorContainerWidget.hpp"

#include "statistics/densityChart.hpp"
#include "statistics/distributionChart.hpp"

#include <QWidget>
#include <QGroupBox>

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

	connect(this->vectorPicker, SIGNAL(vectorSelected(const std::list<double>*)),
			vectorContainer, SLOT(appendList(const std::list<double>*)));

	connect(this->vectorContainer, &VectorContainerWidget::vectorSelected,
			vectorProcessor, &VectorProcessorWidget::appendVector);
	connect(this->vectorContainer, &VectorContainerWidget::outliersRemoved,
			this, &MainWindow::outliersRemovedHandler);
	connect(this->vectorContainer, &VectorContainerWidget::vectorDeleted,
			this->vectorProcessor, &VectorProcessorWidget::vectorDeletedHandler);
	connect(this->vectorContainer, &VectorContainerWidget::distributionSelected,
			this->vectorProcessor, &VectorProcessorWidget::distributionSelectedHandler);
	connect(this->vectorContainer, SIGNAL(message(QString)),
			this, SLOT(showMessage(QString)));

	connect(this->vectorProcessor, &VectorProcessorWidget::duplicateAdded,
			this, &MainWindow::vectorProcessorDuplicateHandler);
	connect(this->vectorProcessor, &VectorProcessorWidget::twoDVectorsSelected,
			this, &MainWindow::plot2D);

	// open();
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

	setGenerator = new SetGeneratorDialog(nullptr, this, false);
	setGenerator->setAttribute(Qt::WA_DeleteOnClose, false);
	connect(setGenerator, &SetGeneratorDialog::setGenerated,
			vectorContainer, &VectorContainerWidget::appendVector);
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

	QMenu *viewMenu = menuBar()->addMenu("Вигляд");

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


	vectorPicker->fileContents(filepath);
	openVectorPicker();
}

void MainWindow::plot2D(VectorEntry* ve) {
	densityChart->fill(ve->vector);
	distributionChart->fill(ve->vector);
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

void MainWindow::vectorProcessorDuplicateHandler(VectorEntry* vectorEntry,
		VectorProcessorWidget::Tab t) {
	this->showMessage("Вектор '" + vectorEntry->name + 
			"' вже доданий до вкладки " + vectorProcessor->tabName[t]);
}

void MainWindow::showMessage(QString msg, int dur) {
	if (dur == 0)
		dur = messageTime;

	this->statusBar()->showMessage(msg);
}
