#include "vectorProcessorWidget.hpp"
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
		connect(tree[i], &QTreeWidget::customContextMenuRequested,
				this, &VectorProcessorWidget::showContextMenu);

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
    item->setText(0, vectorEntry->name);
	item->setData(0, Qt::DisplayRole, QVariant(vectorEntry->name));
	item->setData(0, Qt::UserRole, QVariant::fromValue(vectorEntry));

    tree[idx]->addTopLevelItem(item);

	QTreeWidgetItem* maxItem = new QTreeWidgetItem(ItemType::Max2D);
	maxItem->setIcon(0, this->style()->standardIcon(QStyle::SP_ArrowUp));
	maxItem->setData(0, Qt::DisplayRole, vectorEntry->vector->max());
	item->addChild(maxItem);

	QTreeWidgetItem* minItem = new QTreeWidgetItem(ItemType::Min2D);
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

void VectorProcessorWidget::append1dVector(QTreeWidgetItem* item,
		VectorEntry* vectorEntry) {
	ClassSeries cs(vectorEntry->vector);
	QTreeWidgetItem* classItem = new QTreeWidgetItem(ItemType::ClassCount2D);
	classItem->setIcon(0, this->style()->standardIcon(QStyle::SP_BrowserReload));
	classItem->setData(0, Qt::EditRole,
				QVariant(int(cs.calculateClassCount())));
	item->addChild(classItem);
}

void VectorProcessorWidget::append2dVector(QTreeWidgetItem* item,
		VectorEntry* vectorEntry) {
}

void VectorProcessorWidget::append3dVector(QTreeWidgetItem* item,
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
				QAction* makeActiveAction = menu.addAction("Зробити активним");
				connect(makeActiveAction, &QAction::triggered,
						this, &VectorProcessorWidget::makeActiveAction);
				QAction* removeAction = menu.addAction("Прибрати");
				connect(removeAction, &QAction::triggered,
						this, &VectorProcessorWidget::removeAction);
				break;
			}

		default:
			return;
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

	menu.exec(mapToGlobal(point));
}

void VectorProcessorWidget::twoDContextMenu(QMenu* menu) {
}

void VectorProcessorWidget::threeDContextMenu(QMenu* menu) {

}

void VectorProcessorWidget::fourDContextMenu(QMenu* menu) {

}

void VectorProcessorWidget::makeActiveAction() {
	int idx = this->currentIndex();
	QTreeWidgetItem* item = tree[idx]->currentItem();
	VectorEntry* ve = item->data(0, Qt::UserRole).value<VectorEntry*>();
	item->setIcon(0, this->style()->standardIcon(QStyle::SP_MediaPause));

	switch (idx) {
		case Tab::TwoD:
			if (twoDActiveItems.length() == 1) {
				twoDActiveItems[0]->setIcon(0, this->style()->
						standardIcon(QStyle::SP_MediaPlay));
				twoDActiveItems.pop_front();
			}

			twoDActiveItems.push_back(item);

			emit twoDVectorsSelected(twoDActiveItems[0]->
					data(0, Qt::UserRole).value<VectorEntry*>(), 
					item->child(2)->data(0, Qt::EditRole).value<int>());
			break;

		case Tab::ThreeD:
			if (threeDActiveItems.length() == 2) {
				threeDActiveItems[0]->setIcon(0, this->style()->
						standardIcon(QStyle::SP_MediaPlay));
				threeDActiveItems.pop_front();
			}
			threeDActiveItems.push_back(item);

			if (threeDActiveItems.length() == 2)
				emit threeDVectorsSelected(
					threeDActiveItems[0]->data(0, Qt::UserRole).
					value<VectorEntry*>(), 
					threeDActiveItems[1]->data(0, Qt::UserRole).
					value<VectorEntry*>()
					);
						
			break;

		case Tab::FourD:
			if (fourDActiveItems.length() == 3) {
				fourDActiveItems[0]->setIcon(0, this->style()->
						standardIcon(QStyle::SP_MediaPlay));
				fourDActiveItems.pop_front();
			}

			fourDActiveItems.push_back(item);

			if (fourDActiveItems.length() == 3)
				emit fourDVectorsSelected(
					fourDActiveItems[0]->data(0, Qt::UserRole).
					value<VectorEntry*>(), 
					fourDActiveItems[1]->data(0, Qt::UserRole).
					value<VectorEntry*>(),
					fourDActiveItems[2]->data(0, Qt::UserRole).
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
		for (int i = 0; tree[idx]->topLevelItemCount(); i++) {
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
	auto it = std::find(twoDActiveItems.begin(), twoDActiveItems.end(), item);
	if (it != twoDActiveItems.end())
		twoDActiveItems.erase(it);

	it = std::find(threeDActiveItems.begin(), threeDActiveItems.end(), item);
	if (it != threeDActiveItems.end())
		threeDActiveItems.erase(it);

	it = std::find(fourDActiveItems.begin(), fourDActiveItems.end(), item);
	if (it != fourDActiveItems.end())
		fourDActiveItems.erase(it);
}
