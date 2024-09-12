#ifndef _VECTOR_CONTAINER_WIDGET_HPP_
#define _VECTOR_CONTAINER_WIDGET_HPP_

#include <QTableWidget>
#include <QHeaderView>
#include <QList>
#include <QMenu>
#include <QFileDialog>
#include <QtCore/qnamespace.h>


#include "guiTypes.hpp"
#include "vectorChain.hpp"


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

	QList<std::pair<Vector*, QTableWidgetItem*>> selectedVectors();
	std::pair<Vector*, QTableWidgetItem*> selectedVector();

public slots:
	void appendList(const std::list<double>*, QString = "");
	void appendVector(Vector*);
	void fillRow(int, Vector*);
	void refillRow(int, Vector*);

private slots:
	void showContextMenu(const QPoint&);
	QMenu* vectorContextMenu();
	// QMenu* vectorPairContextMenu();
	// QMenu* vectorChainContextMenu();

	void makeActiveAction();
	void deleteAction();
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
	void makeHypothesisAction(ss::VectorChain::Procedure);

	void vectorDistributionAction();
	void vectorDensityAction();
	void classCountAction(int);
	void confidenceAction(double);

signals:
	void vectorSelected(Vector*);
	void vectorDeleted(Vector*);
	void outliersRemoved(bool);
	void redrawVector(Vector*);

	void message(QString);
};


class HorizontalHeaderItem : public QTableWidgetItem {
public:
	HorizontalHeaderItem(int type = 0);
};

#endif // !_VECTOR_CONTAINER_WIDGET_HPP_
