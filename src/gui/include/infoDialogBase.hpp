#ifndef _INFO_DIALOG_BASE_HPP_
#define _INFO_DIALOG_BASE_HPP_

#include "Section.h"
#include <QTextEdit>
#include<dialogBase.hpp>

class InfoDialogBase: public DialogBase {
public:
	InfoDialogBase(
		VectorEntry*, 
		QWidget* = nullptr,
		Qt::WindowFlags = Qt::WindowFlags()
	);
	
protected:
	QTableWidget* i_table = nullptr;
	ui::Section* i_additionalSection = nullptr;
	QTextEdit* i_additionalText = nullptr;

protected:
	QString n(double);
	void fillTable(QList<QStringList>);

protected:
	double i_prob = 0.95;
	static const int i_precision = 4;
	QStringList i_headers = {
		"Назва", "Позначення", "Незсунуте значення", "σ{θ}", "Нижн. дов. знач. (0.95)", 
		"Зсунуте значення", "Верх. дов. знач. (0.95)"
	};
};

#endif // !_INFO_DIALOG_BASE_HPP_
