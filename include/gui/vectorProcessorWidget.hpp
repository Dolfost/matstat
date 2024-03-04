#ifndef _VECTOR_PROCESSOR_WIDGET_HPP_
#define _VECTOR_PROCESSOR_WIDGET_HPP_

#include <QList>
#include <QTreeWidget>
#include <QHeaderView>
#include <QMenu>
#include <QAction>
#include <QtCore/qcoreevent.h>

#include "./statistics/dataVector.hpp"
#include "./statistics/classSeries.hpp"
#include "guiTypes.hpp"

class VectorProcessorWidget : public QTabWidget {
	Q_OBJECT
public:
	VectorProcessorWidget(QWidget* = nullptr);

	enum Tab {
		TwoD,
		ThreeD,
		FourD,
		Count,
		Current
	};
	enum ItemType {
		Vector,
		ClassCount2D,
		Min2D,
		Max2D, 
	};
	const QStringList tabName = {
		"2D",
		"3D",
		"4D"
	};

private:
	QWidget* tab[3] = {nullptr};
	QTreeWidget* tree[3] = {nullptr};

	int precision = 5;

	void twoDContextMenu(QMenu*);
	void threeDContextMenu(QMenu*);
	void fourDContextMenu(QMenu*);

	QList<QTreeWidgetItem*> activeItems[3];
public slots:
	void appendVector(VectorEntry*);
	void vectorDeletedHandler(VectorEntry*);

private slots:
	void append1dVector(QTreeWidgetItem* item, VectorEntry*);
	void append2dVector(QTreeWidgetItem* item, VectorEntry*);
	void append3dVector(QTreeWidgetItem* item, VectorEntry*);

	void showContextMenu(const QPoint&);

	void makeActiveAction();
	void deactivateAction();
	void removeAction();
	void removeVectorEntryFromLists(QTreeWidgetItem*);

	void itemDoubleClikedHandler(QTreeWidgetItem*, int);
	void itemChangedHandler(QTreeWidgetItem*, int);

	void emit2D(QTreeWidgetItem* item);
	void emit3D(QTreeWidgetItem* item);
	void emit4D(QTreeWidgetItem* item);

signals:
	void tabSelected(Tab);
	void duplicateAdded(VectorEntry*, Tab);
	void vectorRemoved(VectorEntry*);

	void twoDVectorsSelected(VectorEntry*, ClassSeries*);
	void threeDVectorsSelected(VectorEntry*, VectorEntry*);
	void fourDVectorsSelected(VectorEntry*, VectorEntry*, VectorEntry*);
};

class ClassTreeItem : public QTreeWidgetItem {
public:
	ClassTreeItem(int);
	~ClassTreeItem();
};

#endif // !_VECTOR_PROCESSOR_WIDGET_HPP_
