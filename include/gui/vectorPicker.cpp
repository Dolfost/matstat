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
	vectorsTableWidget = new VectorPickerTable();
	vectorsTabLayout->addWidget(vectorsTableWidget);
}


// VectorPickerTable
VectorPickerTable::VectorPickerTable(QWidget* parent)
	: QTableWidget(parent) {
	this->setColumnCount(10);
	this->setRowCount(10);

	this->setDragEnabled(true);

	this->setSelectionBehavior(
			QAbstractItemView::SelectColumns);
	this->setSelectionMode(
			QAbstractItemView::SingleSelection);
	this->setEditTriggers(
			QAbstractItemView::NoEditTriggers);
}

// void VectorPickerTable::mousePressEvent(QMouseEvent *event) {
//     if (event->button() == Qt::LeftButton)
//         dragStartPosition = event->pos();
//
// 	QTableWidget::mousePressEvent(event);
// }
//
// void VectorPickerTable::mouseMoveEvent(QMouseEvent *event) {
//     if (!((event->pos() - dragStartPosition).manhattanLength()
//          < QApplication::startDragDistance())) {
//
// 		QDrag *drag = new QDrag(this);
// 		QMimeData *mimeData = new QMimeData;
//
// 		// mimeData->setData("", data);
// 		drag->setMimeData(mimeData);
//
// 		Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
// 	}
//
// 	QTableWidget::mouseMoveEvent(event);
// }
