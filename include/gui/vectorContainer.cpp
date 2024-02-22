#include "vectorContainer.hpp"

VectorContainer::VectorContainer() {
	this->setColumnCount(vectorInfoCells);
	this->setRowCount(0);
	this->setAcceptDrops(true);
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
		this->setColumnWidth(i, widths[i]); this->setHorizontalHeaderItem(i, item);
	}
}

void VectorContainer::addVector(std::list<double> vec) {
	int rowIdx = this->rowCount();
	this->insertRow(rowIdx);
	DataVector* dv = new DataVector(vec);
	vectorList.push_back(dv);

	this->setColumnCount( 
			(vec.size() + vectorInfoCells > this->columnCount() ?
			 vec.size() + vectorInfoCells : this->columnCount()));

	VerticalHeaderItem* nameItem = new VerticalHeaderItem();
	nameItem->setText("V" + QString::number(++vectorCount));
	this->setItem(rowIdx, 0, nameItem);

	VerticalHeaderItem* sizeItem = new VerticalHeaderItem();
	sizeItem->setText(QString::number(dv->size()));
	this->setItem(rowIdx, 1, sizeItem);

	VerticalHeaderItem* minItem = new VerticalHeaderItem();
	minItem->setText(QString::number(dv->min()));
	this->setItem(rowIdx, 2, minItem);

	VerticalHeaderItem* maxItem = new VerticalHeaderItem();
	maxItem->setText(QString::number(dv->max()));
	this->setItem(rowIdx, 3, maxItem);

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

void VectorContainer::dragEnterEvent(QDragEnterEvent *event) {
	QTableWidget::dragEnterEvent(event);
}

void VectorContainer::dropEvent(QDropEvent* event) {
const QMimeData* data = event->mimeData();

    QByteArray encoded = data->data("application/x-qabstractitemmodeldatalist");
    QDataStream stream(&encoded, QIODevice::ReadOnly);

    QList<QVariantList> columnDataList;
	std::list<double> rowList;

    while (!stream.atEnd()) {
        int row, col;
        QMap<int, QVariant> roleDataMap;
        stream >> row >> col >> roleDataMap;
		rowList.push_back(roleDataMap.first().toDouble());
    }

	addVector(rowList);
}

VerticalHeaderItem::VerticalHeaderItem() {
	QBrush background("#787f8a");
	this->setBackground(background);
}
