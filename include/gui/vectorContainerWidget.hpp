#ifndef _VECTOR_CONTAINER_WIDGET_HPP_
#define _VECTOR_CONTAINER_WIDGET_HPP_

#include <QTableWidget>
#include <QHeaderView>
#include <QList>
#include <QMenu>
#include <QFileDialog>
#include <QtCore/qnamespace.h>


#include "guiTypes.hpp"


class VectorContainerWidget : public QTableWidget {
	Q_OBJECT
public:
	VectorContainerWidget(QWidget* = nullptr);

private:
	enum InfoCell {
		Name,
		Size,
		Min,
		Max,
		Count,
	};

	signed int vectorCount = 0;

	int precision = 4;


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
	void reproductionAction();
	void trimAction();
	void removeOutliersAction();
	void infoAction();
	void generateAction();
	void writeAction();

signals:
	void vectorSelected(VectorEntry*);
	void vectorDeleted(VectorEntry*);
	void outliersRemoved(bool);
	void distributionSelected(VectorEntry*);

	void message(QString);
};


class HorizontalHeaderItem : public QTableWidgetItem {
public:
	HorizontalHeaderItem();
};

#endif // !_VECTOR_CONTAINER_WIDGET_HPP_
