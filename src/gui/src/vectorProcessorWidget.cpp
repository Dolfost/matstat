#include "vectorProcessorWidget.hpp"
#include <QtCore/qlogging.h>
#include <QtCore/qnamespace.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qtreewidget.h>

VectorProcessorWidget::VectorProcessorWidget(
		QWidget* parent) : QTabWidget(parent) {
	this->setDocumentMode(true);
	for (int i = 0; i < Tab::Count; i++) {
		tree[i] = new QTreeWidget;
		tab[i] = new QWidget;

		tree[i]->setHeaderLabel("Вектор");
		tree[i]->setContextMenuPolicy(Qt::CustomContextMenu);
		tree[i]->setExpandsOnDoubleClick(false);
		tree[i]->setEditTriggers(QAbstractItemView::NoEditTriggers);
		connect(tree[i], &QTreeWidget::customContextMenuRequested,
				this, &VectorProcessorWidget::showContextMenu);
		connect(tree[i], &QTreeWidget::itemDoubleClicked,
				this, &VectorProcessorWidget::itemDoubleClikedHandler);
		connect(tree[i], &QTreeWidget::itemChanged,
				this, &VectorProcessorWidget::itemChangedHandler);

		tab[i]->setLayout(new QVBoxLayout);
		tab[i]->layout()->addWidget(tree[i]);
		tab[i]->layout()->setContentsMargins(0,0,0,0);

		this->addTab(tab[i], tabName[i]);
	}

	connect(this, &QTabWidget::currentChanged,
			this, &VectorProcessorWidget::emitTabSelected);
}

void VectorProcessorWidget::appendVector(VectorEntry* vectorEntry) {
	int idx = this->currentIndex();

	for (int i = 0; i < tree[idx]->topLevelItemCount(); i++) {
		if (tree[idx]->topLevelItem(i)->data(0, Qt::UserRole).
			value<VectorEntry*>() == vectorEntry) {
			emit duplicateAdded(vectorEntry, Tab(idx));
			return;
		}
	}

	QTreeWidgetItem *item = new QTreeWidgetItem(ItemType::Vector);
	item->setIcon(0, this->style()->standardIcon(QStyle::SP_MediaPlay));
	item->setData(0, Qt::DisplayRole, QVariant(vectorEntry->name));
	item->setData(0, Qt::ToolTipRole, QVariant(vectorEntry->name));
	item->setData(0, Qt::UserRole, QVariant::fromValue(vectorEntry));

    tree[idx]->addTopLevelItem(item);

	QTreeWidgetItem* maxItem = new QTreeWidgetItem(ItemType::Max2D);
	maxItem->setData(0, Qt::ToolTipRole, QVariant("Максимальна реалізація випадкової величини"));
	maxItem->setIcon(0, this->style()->standardIcon(QStyle::SP_ArrowUp));
	maxItem->setData(0, Qt::DisplayRole, vectorEntry->vector->max());
	item->addChild(maxItem);

	QTreeWidgetItem* minItem = new QTreeWidgetItem(ItemType::Min2D);
	minItem->setData(0, Qt::ToolTipRole, QVariant("Мінімальна реалізація випадкової величини"));
	minItem->setIcon(0, this->style()->standardIcon(QStyle::SP_ArrowDown));
	minItem->setData(0, Qt::DisplayRole, vectorEntry->vector->min());
	item->addChild(minItem);

	switch (idx) {
		case Tab::TwoD:
			append1dVector(item, vectorEntry);
			break;
		case Tab::ThreeD:
			append2dVector(item, vectorEntry);
			break;
		case Tab::FourD:
			append2dVector(item, vectorEntry);
			break;
	}
}

void VectorProcessorWidget::append1dVector(QTreeWidgetItem* parent,
		VectorEntry* vectorEntry) {
	// vectorEntry->vector->makeClassSeries();
	ClassTreeItem2D* classItem = new ClassTreeItem2D(ItemType::ClassCount2D);
	classItem->setIcon(0, this->style()->standardIcon(QStyle::SP_BrowserReload));
	classItem->setData(0, Qt::EditRole,
				QVariant(int(vectorEntry->vector->classSeries.calculateCount())));
	parent->addChild(classItem);

	ConfindenceItem2D* confidenceItem =
		new ConfindenceItem2D(ItemType::Confidence2D);
	confidenceItem->setIcon(0, this->style()->standardIcon(QStyle::SP_ArrowForward));
	confidenceItem->setData(0, Qt::EditRole,
				QVariant(vectorEntry->vector->dist.confidence));
	parent->addChild(confidenceItem);

	// QDoubleSpinBox* spinBox = qobject_cast<QDoubleSpinBox*>(parent->treeWidget()->itemWidget(confidenceItem, 0));
	// qDebug() << "A";
	// if (spinBox) {
	// 	qDebug() << "B";
	// 	spinBox->setDecimals(4);
	// }
}

void VectorProcessorWidget::append2dVector(QTreeWidgetItem* parent,
		VectorEntry* vectorEntry) {
}

void VectorProcessorWidget::append3dVector(QTreeWidgetItem* parent,
		VectorEntry* vectorEntry) {
}

void VectorProcessorWidget::showContextMenu(const QPoint& point) {
	int idx = this->currentIndex();
	QTreeWidgetItem* item = tree[idx]->currentItem();
	if (item == nullptr)
		return;

	QMenu menu;

	switch (item->type()) {
		case ItemType::Vector:
			{
				if (item->data(0, Qt::UserRole+1).value<bool>()) {
					QAction* deactivateAction = menu.addAction("Прибрати з активних");
					connect(deactivateAction, &QAction::triggered,
							this, &VectorProcessorWidget::deactivateAction);
				} else {
					QAction* makeActiveAction = menu.addAction("Додати до активних");
					connect(makeActiveAction, &QAction::triggered,
							this, &VectorProcessorWidget::makeActiveAction);
				}
			}
			break;
	}

	switch (this->currentIndex()) {
		case Tab::TwoD:
			twoDContextMenu(&menu);
			break;
		case Tab::ThreeD:
			threeDContextMenu(&menu);
			break;
		case Tab::FourD:
			fourDContextMenu(&menu);
			break;
	}

	switch (item->type()) {
		case ItemType::Vector:
			{
				menu.addSeparator();
				QAction* removeAction = menu.addAction("Прибрати з списку");
				connect(removeAction, &QAction::triggered,
						this, &VectorProcessorWidget::removeAction);
				break;
			}
	}

	menu.exec(mapToGlobal(point));
}

void VectorProcessorWidget::twoDContextMenu(QMenu* menu) {
}

void VectorProcessorWidget::threeDContextMenu(QMenu* menu) {

}

void VectorProcessorWidget::fourDContextMenu(QMenu* menu) {

}

void VectorProcessorWidget::deactivateAction() {
	int idx = this->currentIndex();
	QTreeWidgetItem* item = tree[idx]->currentItem();

	item->setIcon(0, this->style()->standardIcon(QStyle::SP_MediaPlay));
	item->setData(0, Qt::UserRole+1, QVariant(false));
	auto it = std::find(activeItems[idx].begin(), activeItems[idx].end(), item);
	if (it != activeItems[idx].end())
		activeItems[idx].erase(it);
}

void VectorProcessorWidget::makeActiveAction() {
	int idx = this->currentIndex();
	QTreeWidgetItem* item = tree[idx]->currentItem();
	item->setIcon(0, this->style()->standardIcon(QStyle::SP_MediaPause));
	item->setData(0, Qt::UserRole+1, QVariant(true));

	if (activeItems[idx].length() == idx + 1) {
		activeItems[idx].first()->setIcon(0, this->style()->
				standardIcon(QStyle::SP_MediaPlay));
		activeItems[idx].first()->setData(0, Qt::UserRole+1, QVariant(false));
		activeItems[idx].pop_front();
	}

	activeItems[idx].push_back(item);
	switch (idx) {
		case Tab::TwoD:
			emit2D(item);
			break;

		case Tab::ThreeD:
			emit3D(item);
			break;

		case Tab::FourD:
			emit4D(item);
			break;
default:
			return;
	}
}

void VectorProcessorWidget::removeAction() {
	int idx = this->currentIndex();
	QTreeWidgetItem* item = tree[idx]->currentItem();

	emit vectorRemoved(item->data(0, Qt::UserRole).value<VectorEntry*>());

	tree[idx]->invisibleRootItem()->removeChild(item);
}

void VectorProcessorWidget::vectorDeletedHandler(VectorEntry* ve) {
	for (int idx = 0; idx < Tab::Count; idx++) {
		for (int i = 0; i < tree[idx]->topLevelItemCount(); i++) {
			if (tree[idx]->topLevelItem(i)->data(0, Qt::UserRole).
					value<VectorEntry*>() == ve) {
				removeVectorEntryFromLists(tree[idx]->topLevelItem(i));
				tree[idx]->invisibleRootItem()->removeChild(
						tree[idx]->topLevelItem(i)
						);
			}
		}
	}
}

void VectorProcessorWidget::removeVectorEntryFromLists(QTreeWidgetItem* item) {
	for (auto& lst : activeItems) {
		for (auto& i : lst) {
			auto it = std::find(lst.begin(), lst.end(), item);
			if (it != lst.end())
				lst.erase(it);
		}	
	}
}

void VectorProcessorWidget::itemDoubleClikedHandler(
		QTreeWidgetItem* item, int col) {
	int idx = this->currentIndex();
	switch (item->type()) {
		case ItemType::Vector:
			if (item->data(0, Qt::UserRole+1).value<bool>())
				deactivateAction();
			else
				makeActiveAction();
			break;
		case ItemType::Confidence2D:
		case ItemType::ClassCount2D:
			tree[idx]->editItem(item, col);
	}
}

void VectorProcessorWidget::emitTabSelected(int tab) {
	emit tabSelected((Tab)tab);
}

void VectorProcessorWidget::emit2D(QTreeWidgetItem* item) {
	item->data(0, Qt::UserRole).value<VectorEntry*>()->vector->classSeries.setCount(
			item->child(2)->data(0, Qt::EditRole).value<int>());
	item->data(0, Qt::UserRole).value<VectorEntry*>()->
		vector->dist.confidence = 
		item->child(3)->data(0, Qt::EditRole).value<double>();

	emit twoDVectorsSelected(activeItems[Tab::TwoD].front()->
			data(0, Qt::UserRole).value<VectorEntry*>());
}

void VectorProcessorWidget::emit3D(QTreeWidgetItem* item) {
	if (activeItems[Tab::ThreeD].length() == 2)
		emit threeDVectorsSelected(
				activeItems[Tab::ThreeD][0]->data(0, Qt::UserRole).
				value<VectorEntry*>(), 
				activeItems[Tab::ThreeD][1]->data(0, Qt::UserRole).
				value<VectorEntry*>()
				);
}

void VectorProcessorWidget::emit4D(QTreeWidgetItem* item) {
	if (activeItems[Tab::FourD].length() == 3)
		emit fourDVectorsSelected(
				activeItems[Tab::FourD][0]->data(0, Qt::UserRole).
				value<VectorEntry*>(), 
				activeItems[Tab::FourD][1]->data(0, Qt::UserRole).
				value<VectorEntry*>(),
				activeItems[Tab::FourD][2]->data(0, Qt::UserRole).
				value<VectorEntry*>()
				);
}

void VectorProcessorWidget::itemChangedHandler(QTreeWidgetItem* item, int col) {
	switch (item->type()) {
		case ItemType::ClassCount2D:
			{
				VectorEntry* ve = item->parent()->data(0, Qt::UserRole).
							value<VectorEntry*>();
				if (item->data(0, Qt::EditRole).value<int>() < 1) {
					// ve->vector->makeClassSeries();
					item->setData(0, Qt::EditRole, QVariant(
								(int)ve->vector->classSeries.count()));
				} else {
					ve->vector->classSeries.setCount(item->data(0, Qt::EditRole).value<int>());
				}

				if (item->parent()->data(0, Qt::UserRole+1).value<bool>())
					emit2D(item->parent());
				break;
			}
		case ItemType::Confidence2D:
			{
				double dev = item->data(0, Qt::EditRole).value<double>();
				if (dev < 0 or dev > 1)
					item->setData(0, Qt::EditRole, QVariant(0.5));
				else if (item->parent()->data(0, Qt::UserRole+1).value<bool>())
					emit2D(item->parent());
				break;
			}
	}
}

void VectorProcessorWidget::distributionSelectedHandler(VectorEntry* ve) {
	for (auto const& i : activeItems[Tab::TwoD]) {
		if (i->data(0, Qt::UserRole+1).value<bool>())
			emit2D(i);
	}
};

// Items
ClassTreeItem2D::ClassTreeItem2D(int type) : QTreeWidgetItem(type) {
	this->setFlags(this->flags() | Qt::ItemIsEditable);
	this->setData(0, Qt::ToolTipRole, "Кількість класів розбиття");
}

ConfindenceItem2D::ConfindenceItem2D(int type) : QTreeWidgetItem(type) {
	this->setFlags(this->flags() | Qt::ItemIsEditable);
	this->setData(0, Qt::ToolTipRole, "Імовірність промаху F(x) від теоретичної");
}
	
