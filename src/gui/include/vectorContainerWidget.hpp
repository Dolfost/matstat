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

	template<class T>
	using SelectedT = QList<T*>;
	SelectedT<VectorEntry> selectedVectors();
	SelectedT<VectorEntry> selectedVectorsEntryesList;
	SelectedT<Vector> selectedVectorsList;
	SelectedT<VectorPair> selectedVectorPairsList;
	SelectedT<VectorChain> selectedVectorChainsList;


public slots:
	void placeList(const std::list<double>&);
	void placeVector(ss::Vector&, QString = "");
	void placeVectorPair(ss::VectorPair&, QString = "");
	void appendVector(Vector*);
	void appendVectorPair(VectorPair*);
	// void appendVectorChain(VectorChain*);

private slots:
	void showContextMenu(const QPoint&);
	void fillVectorContextMenu(QMenu*);
	void fillVectorPairContextMenu(QMenu*);
	void fillVectorChainContextMenu(QMenu*);
	void fillGenericContextMenu(QMenu*);

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
	void mergePairAction();

signals:
	void vectorSelected(Vector*);

	void vectorDeleted(Vector*);
	void vectorPairDeleted(VectorPair*);
	void vectorChainDeleted(VectorChain*);

	void outliersRemoved(bool);
	void redrawVector(Vector*);

	void message(QString);
};


class HorizontalHeaderItem : public QTableWidgetItem {
public:
	HorizontalHeaderItem(int type = 0);
};

#endif // !_VECTOR_CONTAINER_WIDGET_HPP_
