#ifndef _VECTOR_CONTAINER_WIDGET_HPP_
#define _VECTOR_CONTAINER_WIDGET_HPP_

#include <QTableWidget>
#include <QHeaderView>
#include <QList>
#include <QMenu>
#include <QFileDialog>
#include <QtCore/qnamespace.h>


#include "guiTypes.hpp"
#include "vector/hypothesis.hpp"
#include "vectorPair/hypothesis.hpp"


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

	void deleteAction();

	void vectorStandardizeAction();
	void vectorLogAction();
	void vectorReverseAction();
	void vectorRightShiftAction();
	void vectorTransformAction();
	void vectorReproductionAction();
	void vectorTrimAction();
	void vectorRemoveOutliersAction();
	void vectorInfoAction();
	void vectorWriteAction();
	void vectorHypothesisAction(ss::VectorHypothesis::Procedure);
	void vectorDistributionAction();
	void vectorDensityAction();
	void vectorClassCountAction(int);
	void vectorPairCorelationRatioCountAction(int);
	void vectorConfidenceAction(double);
	void vectorMergePairAction();

	void vectorPairDensityAction();
	void vectorPairDistributionAction();
	void vectorPairCorelationAction();
	void vectorPairDensity3dAction();
	void vectorPairClassCountActionX(int);
	void vectorPairClassCountActionY(int);
	void vectorPairInfoAction();
	void vectorPairHypothesisAction(ss::VectorPairHypothesis::Procedure);

signals:
	void vectorDeleted(Vector*);
	void vectorPairDeleted(VectorPair*);
	void vectorChainDeleted(VectorChain*);

	void outliersRemoved(bool);
	void redrawVector(VectorEntry*);
	void vectorParametersChanged(VectorEntry*);

	void message(QString);
};


class HorizontalHeaderItem : public QTableWidgetItem {
public:
	HorizontalHeaderItem(int type = 0);
};

#endif // !_VECTOR_CONTAINER_WIDGET_HPP_
