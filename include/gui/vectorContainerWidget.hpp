#ifndef _VECTOR_CONTAINER_WIDGET_HPP_
#define _VECTOR_CONTAINER_WIDGET_HPP_

#include <QTableWidget>
#include <QHeaderView>
#include <QList>
#include <QMenu>

#include "gui/transformationFormulaEditorDialog.hpp"
#include "gui/vectorInfoDialog.hpp"

#include "./statistics/dataVector.hpp"

#include "guiTypes.hpp"


class VectorContainerWidget : public QTableWidget {
	Q_OBJECT
public:
	VectorContainerWidget(QWidget* = nullptr);

private:
	std::list<VectorEntry*> vectorList;
	const short vectorInfoCells = 4;
	signed int vectorCount = 0;


public slots:
	void appendList(const std::list<double>*, QString = "");
	void appendVector(VectorEntry*);
	void fillRow(int, VectorEntry*);
	void refillRow(int, VectorEntry*);

private slots:
	void showContextMenu(const QPoint&);

	void makeActiveAction();
	void deleteAction();
	void deleteAllAction();
	void standardizeAction();
	void logAction();
	void reverseAction();
	void rightShiftAction();
	void transformAction();
	void removeOutliersAction();
	void infoAction();

signals:
	void vectorSelected(VectorEntry*);
	void vectorDeleted(int, VectorEntry*);
	void outliersRemoved(bool);
};


class HorizontalHeaderItem : public QTableWidgetItem {
public:
	HorizontalHeaderItem();
};

#endif // !_VECTOR_CONTAINER_WIDGET_HPP_
