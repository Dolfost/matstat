#ifndef _VECTOR_CONTAINER_HPP_
#define _VECTOR_CONTAINER_HPP_

#include <QTableWidget>
#include <QHeaderView>
#include <QList>
#include <QMouseEvent>
#include <QMimeData>

#include "./statistics/dataVector.hpp"

class VectorContainer : public QTableWidget {
public:
	VectorContainer();

private:
	QHeaderView* horizontalHeader = nullptr;
	std::list<DataVector*> vectorList;
	const short vectorInfoCells = 4;
	signed int vectorCount = 0;

	void addVector(const std::list<double>&);

protected:
	void dragEnterEvent(QDragEnterEvent* event) override;
	void dropEvent(QDropEvent* event) override;
};


class VerticalHeaderItem : public QTableWidgetItem {
public:
	VerticalHeaderItem();
};

#endif // !_VECTOR_CONTAINER_HPP_
