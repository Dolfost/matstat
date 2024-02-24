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
	VectorContainer(QWidget* = nullptr);

private:
	std::list<DataVector*> vectorList;
	const short vectorInfoCells = 4;
	signed int vectorCount = 0;

	void addVector(const std::list<double>&);
public slots:
	void insertVector(const std::list<double>&);
};


class HorizontalHeaderItem : public QTableWidgetItem {
public:
	HorizontalHeaderItem();
};

#endif // !_VECTOR_CONTAINER_HPP_
