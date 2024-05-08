#include "mainWindow.hpp"

#include "setGeneratorDialog.hpp"
#include "vectorContainerWidget.hpp"

#include <QWidget>
#include <QGroupBox>

#include <dataSeries.hpp>

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
			this->charts, &Charts::plot2D);
	connect(this->vectorProcessor, &VectorProcessorWidget::tabSelected,
			this->charts, &Charts::setCurrentIndex);


	_addFile("../../../data/500/norm3n.txt");
	_addFile("../../../data/500/norm.txt");
	_addFile("../../../data/500/exp.txt");
	_addFile("../../../data/500/veib.txt");
	_addFile("../../../data/500/exp1.txt");
	_addFile("../../../data/500/ravn1.txt");
	_addFile("../../../data/25/exp.txt");
	_addFile("../../../data/25/norm.txt");
	_addFile("../../../data/25/veib.txt");
}

void MainWindow::createCharts() {
	charts = new Charts;
	mainSplitter->addWidget(charts);
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
		Tab t) {
	this->showMessage("Вектор '" + vectorEntry->name + 
			"' вже доданий до вкладки " + vectorProcessor->tabName[t]);
}

void MainWindow::showMessage(QString msg, int dur) {
	if (dur == 0)
		dur = messageTime;

	this->statusBar()->showMessage(msg, dur);
}

void MainWindow::_addFile(QString file) {
	DataSeries s;
	s.readData(file);
	VectorEntry* ve = new VectorEntry;
	ve->vector = new DataVector(s.filewiseSeries());
	vectorContainer->appendVector(ve);

	qDebug() << QString(__func__) + ":" << s.message();
}

