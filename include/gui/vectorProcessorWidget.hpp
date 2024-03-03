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

	QList<QTreeWidgetItem*> twoDActiveItems;
	QList<QTreeWidgetItem*> threeDActiveItems;
	QList<QTreeWidgetItem*> fourDActiveItems;
public slots:
	void vectorDeletedHandler(VectorEntry*);
	void appendVector(VectorEntry*);

private slots:
	void append1dVector(QTreeWidgetItem* item, VectorEntry*);
	void append2dVector(QTreeWidgetItem* item, VectorEntry*);
	void append3dVector(QTreeWidgetItem* item, VectorEntry*);

	void showContextMenu(const QPoint&);

	void makeActiveAction();
	void removeAction();
	void removeVectorEntryFromLists(QTreeWidgetItem*);

signals:
	void tabSelected(Tab);
	void duplicateAdded(VectorEntry*, Tab);
	void vectorRemoved(VectorEntry*);

	void twoDVectorsSelected(VectorEntry*, int);
	void threeDVectorsSelected(VectorEntry*, VectorEntry*);
	void fourDVectorsSelected(VectorEntry*, VectorEntry*, VectorEntry*);

};

#endif // !_VECTOR_PROCESSOR_WIDGET_HPP_
