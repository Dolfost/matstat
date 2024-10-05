#ifndef _VECTOR_TRANSFORMATION_DIALOG_
#define _VECTOR_TRANSFORMATION_DIALOG_

#include "vector.hpp"

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>

#include "guiTypes.hpp"

#include <transformationDialogBase.hpp>

class VectorTransformationDialog : public TransformationDialogBase {
	Q_OBJECT
public:
	VectorTransformationDialog(
			QList<Vector*>,
			QWidget* = nullptr,
			Qt::WindowFlags = Qt::WindowFlags()
	);

private:
	QLineEdit* xExpression = nullptr;

public slots:
	virtual void transform() override;

signals:
	void vectorTransformed(Vector*);
};

#endif // !_VECTOR_TRANSFORMATION_DIALOG_
