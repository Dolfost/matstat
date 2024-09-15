#ifndef _VECTOR_HYPOTHESIS_DIALOG_HPP_
#define _VECTOR_HYPOTHESIS_DIALOG_HPP_

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

#include "vector/hypothesis.hpp"

class VectorHypothesisDialog : public QDialog {
public:
	VectorHypothesisDialog(
			QList<Vector*>,
			ss::VectorHypothesis::Procedure = ss::VectorHypothesis::Procedure::tTestDependent,
			QWidget* = nullptr,
			Qt::WindowFlags = Qt::WindowFlags()
			);

private:
	QList<Vector*> vectors;
	ss::VectorHypothesis vectorSet;

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

#endif // !_VECTOR_HYPOTHESIS_DIALOG_HPP_
