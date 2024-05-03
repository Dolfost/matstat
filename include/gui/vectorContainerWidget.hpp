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
	enum DataCell {
		Data = 69,
	};

	signed int vectorCount = 0;

	int precision = 4;

	QList<std::pair<VectorEntry*, QTableWidgetItem*>> selectedVectors();
	std::pair<VectorEntry*, QTableWidgetItem*> selectedVector();

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

	void tTestDependentAction();
	void tTestIndependentAction();

signals:
	void vectorSelected(VectorEntry*);
	void vectorDeleted(VectorEntry*);
	void outliersRemoved(bool);
	void distributionSelected(VectorEntry*);

	void message(QString);
};


class HorizontalHeaderItem : public QTableWidgetItem {
public:
	HorizontalHeaderItem(int type = 0);
};

#endif // !_VECTOR_CONTAINER_WIDGET_HPP_
