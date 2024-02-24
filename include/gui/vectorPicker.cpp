#include "vectorPicker.hpp"
#include <QtCore/qstringlist.h>
#include <QtWidgets/qtabwidget.h>
#include <QtWidgets/qwidget.h>
#include <vector>

VectorPicker::VectorPicker(QWidget *parent, Qt::WindowFlags f) 
	: QDialog(parent, f) {
		this->setWindowTitle("Менеджер векторів");
		this->setMinimumSize(300,400);
		this->setAttribute(Qt::WA_DeleteOnClose, false);
		QVBoxLayout* mainLayout = new QVBoxLayout();
		mainLayout->setSpacing(0);
		this->setLayout(mainLayout);
		mainLayout->setContentsMargins(0,0,0,0);
		QTabWidget* tabWidget = new QTabWidget();
		QWidget* contetnsTab = new QWidget();
		contentsTabLayout = new QVBoxLayout();
		contentsTabLayout->setContentsMargins(0,0,0,0);
		contetnsTab->setLayout(contentsTabLayout);
		QWidget* vectorsTab = new QWidget();
		vectorsTabLayout = new QVBoxLayout();
		vectorsTabLayout->setContentsMargins(0,0,0,0);
		vectorsTab->setLayout(vectorsTabLayout);

		tabWidget->addTab(contetnsTab, "По-рядковий вміст");
		tabWidget->addTab(vectorsTab, "По-векторний вміст");
		tabWidget->setDocumentMode(true);
		mainLayout->addWidget(tabWidget);

		statusBar = new QStatusBar();
		mainLayout->addWidget(statusBar);

		setContentsTab();
		setVectorsTab();
}

void VectorPicker::fileContents(QString filepath) {
	Status ok = dataSeries.readData(filepath);
	statusBar->showMessage(dataSeries.message());

	if (ok == Status::Ok) {
		fill();
	}

	this->show();
}

void VectorPicker::fill() {
	std::vector<std::list<double>> data = dataSeries.series(); 
	vectorsTableWidget->clear();
	vectorsTableWidget->setRowCount(data[0].size());
	vectorsTableWidget->setColumnCount(dataSeries.dimension());

	size_t row = 0, col = 0;
	for (auto const& vector : data) {
		row = 0;
		for (auto const& x : vector) {
			QTableWidgetItem* tableItem = new QTableWidgetItem;
			tableItem->setText(QString::number(x));
			vectorsTableWidget->setItem(row, col, tableItem);

			row++;
		}
		col++;
	}

	QStringList headersList;
	for (size_t i = 0; i < dataSeries.dimension(); i++) {
		headersList.append("Вектор " + QString::number(i+1));
	}
	vectorsTableWidget->setHorizontalHeaderLabels(headersList);

	contentsTextEdit->clear();
	QString textEditContents;

	for (auto const& x : dataSeries.filewiseSeries()) {
		textEditContents.append(QString::number(x) + " ");
	}

	contentsTextEdit->setText(textEditContents);
}

void VectorPicker::setContentsTab() {
	contentsTextEdit = new QTextEdit();
	addContentsPushButton = new QPushButton("Додати в вміст у контейнер");
	addContentsPushButton->setContentsMargins(50,50,50,50);
	QHBoxLayout* buttonLayout = new QHBoxLayout;
	buttonLayout->setContentsMargins(5,0,5,0);
	buttonLayout->addWidget(addContentsPushButton);
	contentsTabLayout->setSpacing(3);
	contentsTabLayout->addWidget(contentsTextEdit);
	contentsTabLayout->addLayout(buttonLayout);
	contentsTextEdit->setReadOnly(true);
	connect(addContentsPushButton, &QPushButton::clicked,
			this, &VectorPicker::addContents);
}

void VectorPicker::setVectorsTab() {
	vectorsTableWidget = new QTableWidget();
	vectorsTableWidget->setSelectionBehavior(
			QAbstractItemView::SelectColumns);
	vectorsTableWidget->setSelectionMode(
			QAbstractItemView::SingleSelection);
	vectorsTableWidget->setEditTriggers(
			QAbstractItemView::NoEditTriggers);

	vectorsTabLayout->addWidget(vectorsTableWidget);
	connect(vectorsTableWidget, &QTableWidget::cellDoubleClicked,
			this, &VectorPicker::addVector);
}

void VectorPicker::closeEvent(QCloseEvent* event) {
	this->hide();
	event->ignore();
}

void VectorPicker::addVector(int row, int col) {
	emit vectorSelected(dataSeries.series()[col]);
}

void VectorPicker::addContents() {
	emit vectorSelected(dataSeries.filewiseSeries());
}
