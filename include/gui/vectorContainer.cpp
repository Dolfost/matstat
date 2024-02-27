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

void VectorContainer::appendVector(const std::list<double>& vec) {
	appendNamedVector(vec);
}

void VectorContainer::appendNamedVector(const std::list<double>& vec, QString name) {
	int row = this->rowCount();

	this->insertRow(row);
	DataVector* dv = new DataVector(vec);
	vectorList.push_back(dv);

	this->setColumnCount( 
			(vec.size() + vectorInfoCells > this->columnCount() ?
			 vec.size() + vectorInfoCells : this->columnCount()));
	if (name.length() == 0)
		name = "V" + QString::number(++vectorCount);

	fillRow(row, dv, name);
}

void VectorContainer::fillRow(int row, DataVector* dv, QString name) {
	QStringList info = {
		name,
		QString::number(dv->size()),
		QString::number(dv->min()),
		QString::number(dv->max()),
	};

	for (int i = 0; i < vectorInfoCells; i++) {
		HorizontalHeaderItem* item = new HorizontalHeaderItem;
		item->setText(info[i]);
		this->setItem(row, i, item);
	}

	auto list = dv->vector();
	auto it = list.begin();
	for (size_t col = vectorInfoCells; col < dv->size() + vectorInfoCells; col++) {
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

void VectorContainer::refillRow(int idx, DataVector* dv) {
	fillRow(idx, dv, this->item(idx, 0)->text());
}

void VectorContainer::showContextMenu(const QPoint& pos) {
	if (this->currentRow() == -1)
		return;

	QMenu menu;


	QAction* setActiveAction = menu.addAction("Зробити активним");
	connect(setActiveAction, &QAction::triggered,
			this, &VectorContainer::makeActiveAction);

	QMenu* edit = menu.addMenu("Трансформації…");
	QAction* normalizeAction = edit->addAction("Нормалізувати");
	connect(normalizeAction, &QAction::triggered,
			this, &VectorContainer::standardizeAction);
	QAction* logAction = edit->addAction("Логарифмувати");
	connect(logAction, &QAction::triggered,
			this, &VectorContainer::logAction);
	QAction* reverseAction = edit->addAction("Обернути");
	connect(reverseAction, &QAction::triggered,
			this, &VectorContainer::reverseAction);
	QAction* rightShiftAction = edit->addAction("Зсунути на xₘᵢₙ+1");
	connect(rightShiftAction, &QAction::triggered,
			this, &VectorContainer::rightShiftAction);
	edit->addSeparator();
	QAction* transformAction = edit->addAction("Власне перетворення…");
	connect(transformAction, &QAction::triggered,
			this, &VectorContainer::transformAction);

	menu.addSeparator();

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
	emit vectorSelected(*it);
}

void VectorContainer::deleteAction() {
	std::list<DataVector*>::iterator it = vectorList.begin();
	std::advance(it, this->currentRow());

	emit vectorDeleted(this->currentRow(), *it);

	delete *it;
	vectorList.erase(it);

	this->removeRow(this->currentRow());
}

void VectorContainer::deleteAllAction() {
	int i = 0;
	for (auto vector : vectorList) {
		emit vectorDeleted(i, vector);
		delete vector;
		i++;
	}
	vectorList.clear();
	this->clearContents();
	this->setRowCount(0);
}

void VectorContainer::standardizeAction() {
	std::list<DataVector*>::iterator it = vectorList.begin();
	std::advance(it, this->currentRow());
	DataVector* newVector = new DataVector((*it)->vector());
	newVector->standardize();

	appendNamedVector(newVector->vector(),
			QString("S(%1)")
			.arg(this->item(this->currentRow(), 0)->text()));
}

void VectorContainer::logAction() {
	std::list<DataVector*>::iterator it = vectorList.begin();
	std::advance(it, this->currentRow());
	DataVector* newVector = new DataVector((*it)->vector());
	newVector->transform("log(x)");

	appendNamedVector(newVector->vector(),
			QString("LN(%1)")
			.arg(this->item(this->currentRow(), 0)->text()));
}

void VectorContainer::reverseAction() {
	std::list<DataVector*>::iterator it = vectorList.begin();
	std::advance(it, this->currentRow());
	DataVector* newVector = new DataVector((*it)->vector());
	newVector->transform("1/x");

	appendNamedVector(newVector->vector(),
			QString("R(%1)")
			.arg(this->item(this->currentRow(), 0)->text()));
}

void VectorContainer::rightShiftAction() {
	std::list<DataVector*>::iterator it = vectorList.begin();
	std::advance(it, this->currentRow());
	DataVector* newVector = new DataVector((*it)->vector());
	qDebug() << newVector->transform("x+abs(xmin)+1");

	appendNamedVector(newVector->vector(),
			QString("RS(%1)")
			.arg(this->item(this->currentRow(), 0)->text()));
}

void VectorContainer::transformAction() {
	auto it = vectorList.begin();
	std::advance(it, this->currentRow());
	TransformationFormulaEditor* tfe = 
		new TransformationFormulaEditor(this->currentRow(), *it,
				this->item(this->currentRow(), 0)->text(), this);
	connect(tfe, &TransformationFormulaEditor::vectorTransformed,
			this, &VectorContainer::refillRow);
	connect(this, &VectorContainer::vectorDeleted,
			tfe, &TransformationFormulaEditor::vectorDeletedHandler);
}

HorizontalHeaderItem::HorizontalHeaderItem() {
	QBrush background("#414141");
	this->setBackground(background);
}
