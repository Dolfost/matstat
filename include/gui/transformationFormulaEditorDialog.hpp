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

#include "types.hpp"

#include "Section.h"

#include "guiTypes.hpp"

class TransformationFormulaEditorDialog : public QDialog {
	Q_OBJECT
public:
	TransformationFormulaEditorDialog(
			VectorEntry*,
			QWidget* = nullptr,
			Qt::WindowFlags = Qt::WindowFlags()
			);

private:
	QLineEdit* formulaLineEdit = nullptr;
	QPushButton* transformButton = nullptr;
	QTextEdit* statusTextEdit = nullptr;

	VectorEntry* ve = nullptr;
	static int trIdx;

public slots:
	void transform();
	void vectorDeletedHandler(VectorEntry*);

signals:
	void vectorTransformed(VectorEntry*);
};

#endif // !_TRANSFORMATION_FORMULA_EDITOR_DIALOG_
