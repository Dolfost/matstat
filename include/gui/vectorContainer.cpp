#include "vectorContainer.hpp"
#include <QtCore/qcontainerfwd.h>

VectorContainer::VectorContainer() {
	this->setColumnCount(100);
	this->setRowCount(5);
	this->setDragEnabled(true);
	this->setSelectionBehavior(QAbstractItemView::SelectRows);
	this->setSelectionMode(QAbstractItemView::SingleSelection);
	this->setEditTriggers(QAbstractItemView::NoEditTriggers);
	this->verticalHeader()->hide();
	horizontalHeader = new QHeaderView(Qt::Horizontal);
	this->setHorizontalHeader(horizontalHeader);

	QStringList headers = {"Назва", "Розмір", "Мін.", "Макс."}; 
	QList<int> widths =   {90,      60,        75,     75}; 

	for (int i = 0; i < 4; i++) {
		QTableWidgetItem* item = new QTableWidgetItem();
		item->setText(headers[i]);
		this->setColumnWidth(i, widths[i]);
		this->setHorizontalHeaderItem(i, item);
	}
}

VerticalHeaderItem::VerticalHeaderItem() {
	QBrush background;
	background.setColor("#787f8a");
	this->setBackground(background);
}

