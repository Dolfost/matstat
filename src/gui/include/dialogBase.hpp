
#ifndef _DIALOG_BASE_HPP_
#define _DIALOG_BASE_HPP_

#include<Qt>
#include<QDialog>
#include<QVBoxLayout>

#include "guiTypes.hpp"
#include "vector.hpp"

class DialogBase: public QDialog {
	Q_OBJECT
public:
	DialogBase(
		QWidget* = nullptr,
		Qt::WindowFlags = Qt::WindowFlags()
	);

public:
	static QString n(double);
	static QString m(QList<QList<double>>);
	static QString ms(QList<QList<QString>>);

	static const int i_precision = 4;

public slots:
	virtual void fill() = 0;

protected:
	QVBoxLayout* v_mainLayout = nullptr;
};

#endif // !_DIALOG_BASE_HPP_
