#include "vectorContainerWidget.hpp"
#include <QtCore/qpoint.h>
#include <iterator>

VectorContainerWidget::VectorContainerWidget(QWidget* parent) : QTableWidget(parent) {
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
			this, &VectorContainerWidget::showContextMenu);
	connect(this, &QTableWidget::cellDoubleClicked,
			this, &VectorContainerWidget::makeActiveAction);
}

void VectorContainerWidget::appendVector(VectorEntry* vectorEntry) {
	int row = this->rowCount();

	this->insertRow(row);
	vectorList.push_back(vectorEntry);

	this->setColumnCount( 
			(vectorEntry->vector->size() + vectorInfoCells > this->columnCount() ?
			vectorEntry->vector->size() + vectorInfoCells : this->columnCount()));
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

	for (int i = 0; i < vectorInfoCells; i++) {
		HorizontalHeaderItem* item = new HorizontalHeaderItem;
		item->setText(info[i]);
		this->setItem(row, i, item);
	}

	auto list = vectorEntry->vector->vector();
	auto it = list.begin();
	for (size_t col = vectorInfoCells;
			col < vectorEntry->vector->size() + vectorInfoCells;
			col++) {
		QTableWidgetItem* tableItem = new QTableWidgetItem();
		tableItem->setText(QString::number(*it));
		it++;
		this->setItem(row, col, tableItem);
	}

	for (size_t i = vectorInfoCells; i < this->columnCount() + vectorInfoCells; i++) {
		QTableWidgetItem* headerItem = new QTableWidgetItem();
		headerItem->setText(QString::number(i - vectorInfoCells+1));
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
	std::list<VectorEntry*>::iterator it = vectorList.begin();
	std::advance(it, this->currentRow());
	emit vectorSelected(*it);
}

void VectorContainerWidget::deleteAction() {
	std::list<VectorEntry*>::iterator it = vectorList.begin();
	std::advance(it, this->currentRow());

	emit vectorDeleted(*it);

	delete *it;
	vectorList.erase(it);

	this->removeRow(this->currentRow());
}

void VectorContainerWidget::deleteAllAction() {
	for (auto vectorEntry : vectorList) {
		emit vectorDeleted(vectorEntry);
		delete vectorEntry;
	}
	vectorList.clear();
	this->clearContents();
	this->setRowCount(0);
}

void VectorContainerWidget::standardizeAction() {
	std::list<VectorEntry*>::iterator it = vectorList.begin();
	std::advance(it, this->currentRow());
	DataVector newVector((*it)->vector->vector());
	newVector.standardize();

	appendList(&newVector.vector(),
			QString("S(%1)")
			.arg((*it)->name));
}

void VectorContainerWidget::logAction() {
	std::list<VectorEntry*>::iterator it = vectorList.begin();
	std::advance(it, this->currentRow());
	DataVector newVector((*it)->vector->vector());
	newVector.transform("log(x)");

	appendList(&newVector.vector(),
			QString("LN(%1)")
			.arg(this->item(this->currentRow(), 0)->text()));
}

void VectorContainerWidget::reverseAction() {
	std::list<VectorEntry*>::iterator it = vectorList.begin();
	std::advance(it, this->currentRow());
	DataVector newVector((*it)->vector->vector());
	newVector.transform("1/x");

	appendList(&newVector.vector(),
			QString("R(%1)")
			.arg(this->item(this->currentRow(), 0)->text()));
}

void VectorContainerWidget::rightShiftAction() {
	std::list<VectorEntry*>::iterator it = vectorList.begin();
	std::advance(it, this->currentRow());
	DataVector newVector((*it)->vector->vector());
	newVector.transform("x+abs(xmin)+1");

	appendList(&newVector.vector(),
			QString("RS(%1)")
			.arg(this->item(this->currentRow(), 0)->text()));
}

void VectorContainerWidget::transformAction() {
	auto it = vectorList.begin();
	std::advance(it, this->currentRow());
	TransformationFormulaEditorDialog* tfe = 
		new TransformationFormulaEditorDialog(*it, this);
	connect(tfe, &TransformationFormulaEditorDialog::vectorTransformed,
			this, &VectorContainerWidget::appendVector);
	connect(this, &VectorContainerWidget::vectorDeleted,
			tfe, &TransformationFormulaEditorDialog::vectorDeletedHandler);
}

void VectorContainerWidget::removeOutliersAction() {
	std::list<VectorEntry*>::iterator it = vectorList.begin();
	std::advance(it, this->currentRow());
	DataVector newVector((*it)->vector->vector());
	bool ok = newVector.removeOutliers();

	emit outliersRemoved(ok);

	if (!ok) // no entries removed
		return;

	appendList(&newVector.vector(),
			QString("RMOUT(%1)")
			.arg(this->item(this->currentRow(), 0)->text()));
}

void VectorContainerWidget::infoAction() {
	auto it = vectorList.begin();
	std::advance(it, this->currentRow());
	VectorInfoDialog* tfe = 
		new VectorInfoDialog(*it, this);
	connect(this, &VectorContainerWidget::vectorDeleted,
			tfe, &VectorInfoDialog::vectorDeletedHandler);
}

HorizontalHeaderItem::HorizontalHeaderItem() {
	QBrush background("#414141");
	this->setBackground(background);
}
