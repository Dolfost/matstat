#ifndef _TRANSFORMATION_DIALOG_BASE_
#define _TRANSFORMATION_DIALOG_BASE_

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

#include <setDialogBase.hpp>

class TransformationDialogBase: public SetDialogBase {
	Q_OBJECT
public:
	TransformationDialogBase(
			QList<VectorEntry*>,
			QWidget* = nullptr,
			Qt::WindowFlags = Qt::WindowFlags()
			);

protected:
	QPushButton* transformButton = nullptr;
	QTextEdit* statusTextEdit = nullptr;
	QVBoxLayout* formulaLayout = nullptr;
	QTextEdit* varsTextEdit = nullptr;
	QTextEdit* statisticsTextEdit = nullptr;

	static int trIdx;
public slots:
	virtual void transform() = 0;

signals:
	void vectorTransformed(VectorEntry*);
};

class Formula: public QWidget {
public:
	Formula(const QString& = "f(x)", const QString& = "placeholder");

	void setName(const QString& n) { f_name->setText(n + " ="); };
	QString name() { return f_name->text(); };

	QLineEdit* line() { return f_lineEdit; };
protected:
	QLineEdit* f_lineEdit = new QLineEdit;
	QLabel* f_name = new QLabel;
};

#endif // !_TRANSFORMATION_DIALOG_BASE_
