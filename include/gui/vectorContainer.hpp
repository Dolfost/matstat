#ifndef _VECTOR_CONTAINER_HPP_
#define _VECTOR_CONTAINER_HPP_

#include <QTableWidget>
#include <QHeaderView>
#include <QList>
#include <QMenu>

#include "gui/transformationFormulaEditor.hpp"

#include "./statistics/dataVector.hpp"

class VectorContainer : public QTableWidget {
	Q_OBJECT
public:
	VectorContainer(QWidget* = nullptr);

private:
	std::list<DataVector*> vectorList;
	const short vectorInfoCells = 4;
	signed int vectorCount = 0;

	void appendNamedVector(const std::list<double>&, QString = "");

public slots:
	void fillRow(int, DataVector*, QString = "");
	void refillRow(int, DataVector*);
	void appendVector(const std::list<double>&);

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

signals:
	void vectorSelected(DataVector*);
	void vectorDeleted(int, DataVector*);
};


class HorizontalHeaderItem : public QTableWidgetItem {
public:
	HorizontalHeaderItem();
};

#endif // !_VECTOR_CONTAINER_HPP_
