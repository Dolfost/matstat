#include "vectorContainerWidget.hpp"
#include <QtCore/qnamespace.h>
#include <QtCore/qpoint.h>
#include <iterator>

VectorContainerWidget::VectorContainerWidget(QWidget* parent) : QTableWidget(parent) {
	this->setColumnCount(InfoCell::Count);
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

	for (int i = 0; i < InfoCell::Count; i++) {
		QTableWidgetItem* item = new QTableWidgetItem();
		item->setText(headers[i]);
		this->setColumnWidth(i, widths[i]); this->setHorizontalHeaderItem(i, item);
	}

	connect(this, &QTableWidget::customContextMenuRequested,
			this, &VectorContainerWidget::showContextMenu);
	connect(this, &QTableWidget::cellDoubleClicked,
			this, &VectorContainerWidget::makeActiveAction);
}

void VectorContainerWidget::appendVector(VectorEntry* vectorEntry) {
	int row = this->rowCount();

	this->insertRow(row);

	this->setColumnCount( 
			(vectorEntry->vector->size() + InfoCell::Count > this->columnCount() ?
			vectorEntry->vector->size() + InfoCell::Count : this->columnCount()));
	if (vectorEntry->name.length() == 0)
		vectorEntry->name = "V" + QString::number(++vectorCount);

	fillRow(row, vectorEntry);
}

void VectorContainerWidget::appendList(const std::list<double>* vec, QString name) {
	VectorEntry* vectorEntry = new VectorEntry;
	vectorEntry->vector = new DataVector(*vec);
	vectorEntry->name = name;
	appendVector(vectorEntry);
}

void VectorContainerWidget::fillRow(int row, VectorEntry* vectorEntry) {
	QStringList info = {
		vectorEntry->name,
		QString::number(vectorEntry->vector->size()),
		QString::number(vectorEntry->vector->min()),
		QString::number(vectorEntry->vector->max()),
	};

	QList<HorizontalHeaderItem*> infoItems;
	infoItems.append(new HorizontalHeaderItem);
	infoItems[InfoCell::Name]->setData(Qt::DisplayRole,
			QVariant(vectorEntry->name));
	infoItems[InfoCell::Name]->setData(Qt::UserRole, QVariant::fromValue(vectorEntry));

	infoItems.append(new HorizontalHeaderItem);
	infoItems[InfoCell::Size]->setData(Qt::DisplayRole,
			QVariant((int)vectorEntry->vector->size()));

	infoItems.append(new HorizontalHeaderItem);
	infoItems[InfoCell::Min]->setData(Qt::DisplayRole,
			QVariant(vectorEntry->vector->min()));

	infoItems.append(new HorizontalHeaderItem);
	infoItems[InfoCell::Max]->setData(Qt::DisplayRole,
			QVariant(vectorEntry->vector->max()));

	for (int i = 0; i < InfoCell::Count; i++) {
		this->setItem(row, i, infoItems[i]);
	}

	auto list = vectorEntry->vector->vector();
	auto it = list.begin();
	for (size_t col = InfoCell::Count;
			col < vectorEntry->vector->size() + InfoCell::Count;
			col++) {
		QTableWidgetItem* tableItem = new QTableWidgetItem();
		tableItem->setText(QString::number(*it));
		it++;
		this->setItem(row, col, tableItem);
	}

	for (size_t i = InfoCell::Count; i < this->columnCount() + InfoCell::Count; i++) {
		QTableWidgetItem* headerItem = new QTableWidgetItem();
		headerItem->setText(QString::number(i - InfoCell::Count+1));
		this->setHorizontalHeaderItem(i, headerItem);
	}
}

void VectorContainerWidget::refillRow(int idx, VectorEntry* vectorEntry) {
	fillRow(idx, vectorEntry);
}

void VectorContainerWidget::showContextMenu(const QPoint& pos) {
	if (this->currentRow() == -1)
		return;

	QMenu menu;


	QAction* setActiveAction = menu.addAction("Додати до процессора");
	connect(setActiveAction, &QAction::triggered,
			this, &VectorContainerWidget::makeActiveAction);

	QAction* removeOutliersAction = menu.addAction("Видалити аномалії");
	connect(removeOutliersAction, &QAction::triggered,
			this, &VectorContainerWidget::removeOutliersAction);

	QMenu* transform = menu.addMenu("Трансформації…");
	QAction* normalizeAction = transform->addAction("Нормалізувати");
	connect(normalizeAction, &QAction::triggered,
			this, &VectorContainerWidget::standardizeAction);
	QAction* logAction = transform->addAction("Логарифмувати");
	connect(logAction, &QAction::triggered,
			this, &VectorContainerWidget::logAction);
	QAction* reverseAction = transform->addAction("Обернути");
	connect(reverseAction, &QAction::triggered,
			this, &VectorContainerWidget::reverseAction);
	QAction* rightShiftAction = transform->addAction("Зсунути на xₘᵢₙ+1");
	connect(rightShiftAction, &QAction::triggered,
			this, &VectorContainerWidget::rightShiftAction);
	transform->addSeparator();
	QAction* transformAction = transform->addAction("Власне перетворення…");
	connect(transformAction, &QAction::triggered,
			this, &VectorContainerWidget::transformAction);

	menu.addSeparator();

	QAction* infoAction = menu.addAction("Про вектор…");
	connect(infoAction, &QAction::triggered,
			this, &VectorContainerWidget::infoAction);

	menu.addSeparator();

	QAction* deleteAction = menu.addAction("Видалити");
	connect(deleteAction, &QAction::triggered,
			this, &VectorContainerWidget::deleteAction);
	QAction* deleteAllAction = menu.addAction("Видалити всі");
	connect(deleteAllAction, &QAction::triggered,
			this, &VectorContainerWidget::deleteAllAction);

	menu.exec(mapToGlobal(pos));
}

void VectorContainerWidget::makeActiveAction() {
	VectorEntry* ve = this->itemAt(this->currentRow(), InfoCell::Name)->
			data(Qt::UserRole).value<VectorEntry*>();
	emit vectorSelected(ve);
}

void VectorContainerWidget::deleteAction() {
	VectorEntry* ve = this->itemAt(this->currentRow(), InfoCell::Name)->
			data(Qt::UserRole).value<VectorEntry*>();
	emit vectorDeleted(ve);

	delete ve;

	this->removeRow(this->currentRow());
}

void VectorContainerWidget::deleteAllAction() {
	for (int i = 0; i < this->rowCount(); i++) {
	VectorEntry* ve = this->itemAt(i, InfoCell::Name)->
			data(Qt::UserRole).value<VectorEntry*>();
		emit vectorDeleted(ve);
		delete ve;
	}

	this->clearContents();
	this->setRowCount(0);
}

void VectorContainerWidget::standardizeAction() {
	VectorEntry* ve = this->itemAt(this->currentRow(), InfoCell::Name)->
			data(Qt::UserRole).value<VectorEntry*>();
	DataVector newVector(ve->vector->vector());
	newVector.standardize();

	appendList(&newVector.vector(),
			QString("S(%1)")
			.arg(ve->name));
}

void VectorContainerWidget::logAction() {
	VectorEntry* ve = this->itemAt(this->currentRow(), InfoCell::Name)->
			data(Qt::UserRole).value<VectorEntry*>();
	DataVector newVector(ve->vector->vector());
	newVector.transform("log(x)");

	appendList(&newVector.vector(),
			QString("LN(%1)")
			.arg(this->item(this->currentRow(), 0)->text()));
}

void VectorContainerWidget::reverseAction() {
	VectorEntry* ve = this->itemAt(this->currentRow(), InfoCell::Name)->
			data(Qt::UserRole).value<VectorEntry*>();
	DataVector newVector(ve->vector->vector());
	newVector.transform("1/x");

	appendList(&newVector.vector(),
			QString("R(%1)")
			.arg(this->item(this->currentRow(), 0)->text()));
}

void VectorContainerWidget::rightShiftAction() {
	VectorEntry* ve = this->itemAt(this->currentRow(), InfoCell::Name)->
			data(Qt::UserRole).value<VectorEntry*>();
	DataVector newVector(ve->vector->vector());
	newVector.transform("x+abs(xmin)+1");

	appendList(&newVector.vector(),
			QString("RS(%1)")
			.arg(this->item(this->currentRow(), 0)->text()));
}

void VectorContainerWidget::transformAction() {
	VectorEntry* ve = this->itemAt(this->currentRow(), InfoCell::Name)->
			data(Qt::UserRole).value<VectorEntry*>();
	TransformationFormulaEditorDialog* tfe = 
		new TransformationFormulaEditorDialog(ve, this);
	connect(tfe, &TransformationFormulaEditorDialog::vectorTransformed,
			this, &VectorContainerWidget::appendVector);
	connect(this, &VectorContainerWidget::vectorDeleted,
			tfe, &TransformationFormulaEditorDialog::vectorDeletedHandler);
}

void VectorContainerWidget::removeOutliersAction() {
	VectorEntry* ve = this->itemAt(this->currentRow(), InfoCell::Name)->
			data(Qt::UserRole).value<VectorEntry*>();
	DataVector newVector(ve->vector->vector());
	bool ok = newVector.removeOutliers();

	emit outliersRemoved(ok);

	if (!ok) // no entries removed
		return;

	appendList(&newVector.vector(),
			QString("RMOUT(%1)")
			.arg(this->item(this->currentRow(), 0)->text()));
}

void VectorContainerWidget::infoAction() {
	VectorEntry* ve = this->itemAt(this->currentRow(), InfoCell::Name)->
			data(Qt::UserRole).value<VectorEntry*>();
	VectorInfoDialog* tfe = 
		new VectorInfoDialog(ve, this);
	connect(this, &VectorContainerWidget::vectorDeleted,
			tfe, &VectorInfoDialog::vectorDeletedHandler);
}

HorizontalHeaderItem::HorizontalHeaderItem() {
	QBrush background("#414141");
	this->setBackground(background);
}
