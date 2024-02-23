#include "vectorPicker.hpp"
#include <QtCore/qstringlist.h>
#include <QtWidgets/qtabwidget.h>
#include <QtWidgets/qwidget.h>
#include <vector>

VectorPicker::VectorPicker(QWidget *parent, Qt::WindowFlags f) 
	: QDialog(parent, f) {
		this->setWindowTitle("Менеджер векторів");
		this->setMinimumSize(300,400);
		QVBoxLayout* mainLayout = new QVBoxLayout();
		this->setLayout(mainLayout);
		mainLayout->setContentsMargins(0,0,0,0);
		QTabWidget* tabWidget = new QTabWidget();
		QWidget* contetnsTab = new QWidget();
		contentsTabLayout = new QHBoxLayout();
		contentsTabLayout->setContentsMargins(0,0,0,0);
		contetnsTab->setLayout(contentsTabLayout);
		QWidget* vectorsTab = new QWidget();
		vectorsTabLayout = new QHBoxLayout();
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

		connect(vectorsTableWidget, &QTableWidget::cellDoubleClicked,
				this, &VectorPicker::cellDoubleClickedHandler);
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
		for (auto const& x : vector) {
			row = 0;
			QTableWidgetItem* tableItem = new QTableWidgetItem;
			tableItem->setText(QString::number(x));
			vectorsTableWidget->setItem(row, col, tableItem);

			col++;
		}
		row++;
	}

	QStringList headersList;
	for (size_t i = 0; i < dataSeries.dimension(); i++) {
		headersList.append("Вектор " + QString::number(i+1));
	}
	vectorsTableWidget->setHorizontalHeaderLabels(headersList);

	contentsTextEdit->clear();
	QString textEditContents;

	std::vector<std::list<double>::iterator> iterators;
	for (auto& list : data) {
		iterators.push_back(list.begin());
	}

	for (row = 0; row < data[0].size(); row++) {
		for (col = 0; col < dataSeries.dimension(); col++) {
			textEditContents.append(QString(
						"%1 ")
					.arg(*(iterators[col]++))
					);
		}
	}

	contentsTextEdit->setText(textEditContents);
}

void VectorPicker::setContentsTab() {
	contentsTextEdit = new QTextEdit();
	contentsTabLayout->addWidget(contentsTextEdit);
	contentsTextEdit->setReadOnly(true);
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
}

void VectorPicker::closeEvent(QCloseEvent* event) {
	this->hide(); event->ignore();
}

void VectorPicker::cellDoubleClickedHandler(int row, int col) {
	emit vectorSelected(dataSeries.series()[col]);
}
