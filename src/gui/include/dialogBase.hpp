
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

public slots:
	virtual void fill() = 0;

protected:
	QVBoxLayout* v_mainLayout = nullptr;
};

#endif // !_DIALOG_BASE_HPP_
