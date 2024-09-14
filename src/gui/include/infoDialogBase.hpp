#ifndef _INFO_DIALOG_BASE_HPP_
#define _INFO_DIALOG_BASE_HPP_

#include<dialogBase.hpp>

class InfoDialogBase: public DialogBase {
public:
	InfoDialogBase(VectorEntry*, QWidget*);
	
protected:
	QTableWidget* i_table = nullptr;

protected slots:
	virtual void fill() = 0;

protected:
	QString n(double);
	static const int i_precision = 4;
};

#endif // !_INFO_DIALOG_BASE_HPP_
