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
#include <QTableWidget>

#include "guiTypes.hpp"

#include "vectorChain.hpp"

class HypothesisManagerDialog : public QDialog {
public:
	HypothesisManagerDialog(
			QList<Vector*>,
			ss::VectorChain::Procedure = ss::VectorChain::Procedure::tTestDependentP,
			QWidget* = nullptr,
			Qt::WindowFlags = Qt::WindowFlags()
			);

private:
	QList<Vector*> vectors;
	ss::VectorChain vectorSet;

private:
	QVBoxLayout* mainLayout = nullptr;

	QComboBox* procedureComboBox = nullptr;
	QLineEdit* vectorsLineEdit = nullptr;
	QTextEdit* resTextEdit = nullptr;
	QDoubleSpinBox* levelSpinBox = nullptr;
	QTableWidget* pmTable = nullptr;

private slots:
	void makeVectorList();
	void compute();

public slots:
	void vectorDeletedHandler(Vector*);

};

#endif // !_HYPOTHESIS_MANAGER_DIALOG_HPP_
