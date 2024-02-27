#ifndef _TRANSFORMATION_FORMULA_EDITOR_
#define _TRANSFORMATION_FORMULA_EDITOR_

#include "statistics/dataVector.hpp"

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

class TransformationFormulaEditor : public QDialog {
	Q_OBJECT
public:
	TransformationFormulaEditor(int, DataVector*, QString, QWidget* = nullptr,
			Qt::WindowFlags = Qt::WindowFlags());

	bool transfromVector(const DataVector*);

private:
	QLabel* tipsLabel = nullptr;
	QLineEdit* formulaLineEdit = nullptr;
	QPushButton* transformButton = nullptr;
	QTextEdit* statusTextEdit = nullptr;

	DataVector* dv = nullptr;
	int idx = 0;

public slots:
	void transform();

signals:
	void vectorTransformed(int, DataVector*);
};

#endif // !_TRANSFORMATION_FORMULA_EDITOR_
