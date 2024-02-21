#ifndef _VECTOR_CONTAINER_HPP_
#define _VECTOR_CONTAINER_HPP_

#include <QTableWidget>
#include <QHeaderView>
#include <QtCore/qlist.h>

#include "./statistics/dataVector.hpp"

class VectorContainer : public QTableWidget {
public:
	VectorContainer();

private:
	QHeaderView* horizontalHeader = nullptr;
	QList<DataVector> vectorList;
};



class VerticalHeaderItem : public QTableWidgetItem {
public:
	VerticalHeaderItem();
};

#endif // !_VECTOR_CONTAINER_HPP_
