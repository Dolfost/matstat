#ifndef _TRANSFORMATION_FORMULA_EDITOR_DIALOG_
#define _TRANSFORMATION_FORMULA_EDITOR_DIALOG_

#include "statistics/dataVector.hpp"

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>

#include "Section.h"

class TransformationFormulaEditorDialog : public QDialog {
	Q_OBJECT
public:
	TransformationFormulaEditorDialog(int*,
			DataVector*,
			QString,
			QWidget* = nullptr,
			Qt::WindowFlags = Qt::WindowFlags()
			);

	bool transfromVector(const DataVector*);

private:
	QLineEdit* formulaLineEdit = nullptr;
	QPushButton* transformButton = nullptr;
	QTextEdit* statusTextEdit = nullptr;

	DataVector* dv = nullptr;
	int* transformIdx = nullptr;
	QString vecName;

public slots:
	void transform();
	void vectorDeletedHandler(int, DataVector*);

signals:
	void vectorTransformed(const std::list<double>*, QString);
};

#endif // !_TRANSFORMATION_FORMULA_EDITOR_DIALOG_
