#ifndef _VECTOR_PAIR_TRANSFORMATION_DIALOG_
#define _VECTOR_PAIR_TRANSFORMATION_DIALOG_

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

class VectorPairTransformationDialog : public TransformationDialogBase {
	Q_OBJECT
public:
	VectorPairTransformationDialog(
			QList<VectorPair*>,
			QWidget* = nullptr,
			Qt::WindowFlags = Qt::WindowFlags()
	);

private:
	QLineEdit* xExpression = nullptr;
	QLineEdit* yExpression = nullptr;

public slots:
	virtual void transform() override;
	
signals:
	void vectorTransformed(VectorPair*);
};

#endif // !_VECTOR_PAIR_TRANSFORMATION_DIALOG_
