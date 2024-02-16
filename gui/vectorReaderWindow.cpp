#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qtabwidget.h>
#include <vector>

#include "vectorReaderWindow.hpp"
#include "../statistics/dataseries.hpp"
#include "../statistics/vectordataseries.hpp"

VectorReaderWindow::VectorReaderWindow(QWidget *parent) : QDialog(parent) {
	setWindowTitle("Vector reader");
	QVBoxLayout* mainLayout = new QVBoxLayout();
	mainLayout->setContentsMargins(0,0,0,0);
	this->setContentsMargins(0,0,0,0);
	this->setLayout(mainLayout);
	statusBar = new QStatusBar();
	statusBar->setContentsMargins(0,0,0,0);

	QTabWidget* tabWidget = new QTabWidget(parent);
	tabWidget->setDocumentMode(true);
	tabWidget->setMovable(true);
	mainLayout->addWidget(tabWidget);

	QWidget* contentsTab = new QWidget();
	QWidget* vectorsTab = new QWidget();
	tabWidget->addTab(contentsTab, "Contents");
	tabWidget->addTab(vectorsTab, "Vectors");

	// contentsTab
	QVBoxLayout* contentsLayout = new QVBoxLayout();
	contentsLayout->setContentsMargins(0,0,0,0);
	contentsTab->setLayout(contentsLayout);
	contentsTextEdit = new QTextEdit();
	contentsLayout->addWidget(contentsTextEdit);

	// vectorsTab setup
	QVBoxLayout* vectorsLayout = new QVBoxLayout();
	vectorsLayout->setContentsMargins(0,0,0,0);
	vectorsTab->setLayout(vectorsLayout);
	vectorsTableWidget = new QTableWidget();
	vectorsTableWidget->setSelectionBehavior(QAbstractItemView::SelectColumns);
	vectorsLayout->addWidget(vectorsTableWidget);
	vectorsTableWidget->setColumnCount(1);
	importColumnwiseButton = new QPushButton("Imort selected vectors");
	vectorsLayout->addWidget(importColumnwiseButton);
	connect(importColumnwiseButton, &QPushButton::pressed, [=](){
			setVectors();
			this->done(0);
			});


	mainLayout->addWidget(statusBar);
}

void VectorReaderWindow::readData(QString file) {
	dataSeries = new DataSeries();
	Status status = dataSeries->readData(file);
	
	statusBar->showMessage(dataSeries->message());

	if (status != Status::Ok)
		return;

	vectorsTableWidget->setColumnCount(dataSeries->dimension());
	vectorsTableWidget->setRowCount(dataSeries->size());

	for (int i = 0; i < dataSeries->size(); i++) {
		for (int j = 0; j < dataSeries->dimension(); j++) {
			QTableWidgetItem* item = new QTableWidgetItem(QString::number(dataSeries->series()[i][j]));
			vectorsTableWidget->setItem(i, j, item);
		}
	}
}

void VectorReaderWindow::setVectors() {
	std::vector<VectorDataSeries> res;
	
	QItemSelectionModel *selectionModel = vectorsTableWidget->selectionModel();
	QModelIndexList selectedColumns = selectionModel->selectedColumns();


	for (const QModelIndex &index : selectedColumns) {
		res.push_back(dataSeries->series()[index.column()]);
	}
}

std::vector<VectorDataSeries> VectorReaderWindow::vectors() {
	return vectorDataSeries;
}
