#ifndef _HYPOTHESIS_MANAGER_DIALOG_HPP_
#define _HYPOTHESIS_MANAGER_DIALOG_HPP_

#include <QDialog>
#include <QList>
#include <QLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QDoubleSpinBox>

#include "guiTypes.hpp"

#include "dataVectorSet.hpp"

class HypothesisManagerDialog : public QDialog {
public:
	HypothesisManagerDialog(
			QList<VectorEntry*>,
			DataVectorSet::Procedure = DataVectorSet::Procedure::tTestDependentP,
			QWidget* = nullptr,
			Qt::WindowFlags = Qt::WindowFlags()
			);

private:
	QList<VectorEntry*> vectors;
	DataVectorSet vectorSet;

private:
	QVBoxLayout* mainLayout = nullptr;

	QComboBox* procedureComboBox = nullptr;
	QLineEdit* vectorsLineEdit = nullptr;
	QTextEdit* resTextEdit = nullptr;
	QDoubleSpinBox* levelSpinBox = nullptr;

private slots:
	void makeVectorList();
	void compute();

public slots:
	void vectorDeletedHandler(VectorEntry*);

};

#endif // !_HYPOTHESIS_MANAGER_DIALOG_HPP_
