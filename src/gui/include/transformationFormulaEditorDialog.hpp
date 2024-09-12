#ifndef _TRANSFORMATION_FORMULA_EDITOR_DIALOG_
#define _TRANSFORMATION_FORMULA_EDITOR_DIALOG_

#include "vector.hpp"

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>

#include "Section.h"

#include "guiTypes.hpp"

class TransformationFormulaEditorDialog : public QDialog {
	Q_OBJECT
public:
	TransformationFormulaEditorDialog(
			QList<Vector*>,
			QWidget* = nullptr,
			Qt::WindowFlags = Qt::WindowFlags()
			);

private:
	QLineEdit* formulaLineEdit = nullptr;
	QLineEdit* vectorNames = nullptr;
	QPushButton* transformButton = nullptr;
	QTextEdit* statusTextEdit = nullptr;

	QList<Vector*> vecs;
	static int trIdx;

public slots:
	void transform();
	void vectorDeletedHandler(Vector*);

private slots:
	void makeVectorNames();

signals:
	void vectorTransformed(Vector*);
};

#endif // !_TRANSFORMATION_FORMULA_EDITOR_DIALOG_
