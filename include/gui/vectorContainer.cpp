#include "vectorContainer.hpp"
#include <QtCore/qpoint.h>
#include <iterator>

VectorContainer::VectorContainer(QWidget* parent) : QTableWidget(parent) {
	this->setColumnCount(vectorInfoCells);
	this->setRowCount(0);
	this->setAcceptDrops(false);
	this->setDragEnabled(false);
	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->setSelectionMode(QAbstractItemView::SingleSelection);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->verticalHeader()->hide();
	this->setContextMenuPolicy(Qt::CustomContextMenu);


	QStringList headers = {"Назва", "Розмір", "Мін.", "Макс.", "Файл"}; 
	QList<int> widths =   {90,      60,        75,     75}; 

	for (int i = 0; i < vectorInfoCells; i++) {
		QTableWidgetItem* item = new QTableWidgetItem();
		item->setText(headers[i]);
		this->setColumnWidth(i, widths[i]); this->setHorizontalHeaderItem(i, item);
	}

	connect(this, &QTableWidget::customContextMenuRequested,
			this, &VectorContainer::showContextMenu);
	connect(this, &QTableWidget::cellDoubleClicked,
			this, &VectorContainer::makeActiveAction);
}

void VectorContainer::insertVector(const std::list<double>& vec) {
	int rowIdx = this->rowCount();

	this->insertRow(rowIdx);
	DataVector* dv = new DataVector(vec);
	vectorList.push_back(dv);

	this->setColumnCount( 
			(vec.size() + vectorInfoCells > this->columnCount() ?
			 vec.size() + vectorInfoCells : this->columnCount()));

	QStringList info = {
		"V" + QString::number(++vectorCount),
		QString::number(dv->size()),
		QString::number(dv->min()),
		QString::number(dv->max()),
	};

	for (int i = 0; i < vectorInfoCells; i++) {
		HorizontalHeaderItem* item = new HorizontalHeaderItem;
		item->setText(info[i]);
		this->setItem(rowIdx, i, item);
	}

	auto list = dv->vector();
	auto it = list.begin();
	for (size_t col = vectorInfoCells; col < dv->size() + vectorInfoCells; col++) {
		QTableWidgetItem* tableItem = new QTableWidgetItem();
		tableItem->setText(QString::number(*it));
		it++;
		this->setItem(rowIdx, col, tableItem);
	}

	for (size_t i = vectorInfoCells; i < this->columnCount() + vectorInfoCells; i++) {
		QTableWidgetItem* headerItem = new QTableWidgetItem();
		headerItem->setText(QString::number(i - vectorInfoCells+1));
		this->setHorizontalHeaderItem(i, headerItem);
	}
}

void VectorContainer::showContextMenu(const QPoint& pos) {
	if (this->currentRow() == -1)
		return;

	QMenu menu;

	QAction* setActiveAction = menu.addAction("Зробити активним");
	connect(setActiveAction, &QAction::triggered,
			this, &VectorContainer::makeActiveAction);
	QAction* deleteAction = menu.addAction("Видалити");
	connect(deleteAction, &QAction::triggered,
			this, &VectorContainer::deleteAction);
	QAction* deleteAllAction = menu.addAction("Видалити всі");
	connect(deleteAllAction, &QAction::triggered,
			this, &VectorContainer::deleteAllAction);

	menu.exec(mapToGlobal(pos));
}

void VectorContainer::makeActiveAction() {
	std::list<DataVector*>::iterator it = vectorList.begin();
	std::advance(it, this->currentRow());
	emit vectorSelected(**it);
}

void VectorContainer::deleteAction() {
	std::list<DataVector*>::iterator it = vectorList.begin();
	std::advance(it, this->currentRow());
	delete *it;
	vectorList.erase(it);

	emit vectorDeleted(this->currentRow());

	this->removeRow(this->currentRow());
}

void VectorContainer::deleteAllAction() {
	this->clearContents();
	this->setRowCount(0);
	vectorList.clear();
}

HorizontalHeaderItem::HorizontalHeaderItem() {
	QBrush background("#414141");
	this->setBackground(background);
}
