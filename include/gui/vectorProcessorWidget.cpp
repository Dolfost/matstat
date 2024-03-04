#include "vectorProcessorWidget.hpp"
#include <QtCore/qlogging.h>
#include <QtCore/qnamespace.h>
#include <QtWidgets/qboxlayout.h>
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
		connect(tree[i], &QTreeWidget::customContextMenuRequested,
				this, &VectorProcessorWidget::showContextMenu);
		connect(tree[i], &QTreeWidget::itemDoubleClicked,
				this, &VectorProcessorWidget::itemDoubleClikedHandler);

		tab[i]->setLayout(new QVBoxLayout);
		tab[i]->layout()->addWidget(tree[i]);
		tab[i]->layout()->setContentsMargins(0,0,0,0);

		this->addTab(tab[i], tabName[i]);
	}
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
	maxItem->setIcon(0, this->style()->standardIcon(QStyle::SP_ArrowUp));
	maxItem->setData(0, Qt::DisplayRole, vectorEntry->vector->max());
	maxItem->setData(0, Qt::ToolTipRole, vectorEntry->vector->max());
	item->addChild(maxItem);

	QTreeWidgetItem* minItem = new QTreeWidgetItem(ItemType::Min2D);
	minItem->setIcon(0, this->style()->standardIcon(QStyle::SP_ArrowDown));
	minItem->setData(0, Qt::DisplayRole, vectorEntry->vector->min());
	minItem->setData(0, Qt::ToolTipRole, vectorEntry->vector->min());
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
	ClassSeries cs(vectorEntry->vector);
	QTreeWidgetItem* classItem = new QTreeWidgetItem(ItemType::ClassCount2D);
	classItem->setIcon(0, this->style()->standardIcon(QStyle::SP_BrowserReload));
	classItem->setData(0, Qt::EditRole,
				QVariant(int(cs.calculateClassCount())));
	parent->addChild(classItem);
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

			emit twoDVectorsSelected(activeItems[idx].front()->
					data(0, Qt::UserRole).value<VectorEntry*>(), 
					item->child(2)->data(0, Qt::EditRole).value<int>());
			break;

		case Tab::ThreeD:
			if (activeItems[idx].length() == 2)
				emit threeDVectorsSelected(
					activeItems[idx][0]->data(0, Qt::UserRole).
					value<VectorEntry*>(), 
					activeItems[idx][1]->data(0, Qt::UserRole).
					value<VectorEntry*>()
					);
						
			break;

		case Tab::FourD:
			if (activeItems[idx].length() == 3)
				emit fourDVectorsSelected(
					activeItems[idx][0]->data(0, Qt::UserRole).
					value<VectorEntry*>(), 
					activeItems[idx][1]->data(0, Qt::UserRole).
					value<VectorEntry*>(),
					activeItems[idx][2]->data(0, Qt::UserRole).
					value<VectorEntry*>()
					);
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
	switch (item->type()) {
		case ItemType::Vector:
			if (item->data(0, Qt::UserRole+1).value<bool>())
				deactivateAction();
			else
				makeActiveAction();
	}
}
