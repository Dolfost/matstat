#ifndef _INFO_DIALOG_BASE_HPP_
#define _INFO_DIALOG_BASE_HPP_

#include "Section.h"
#include <QTextEdit>
#include<vectorEntryDialogBase.hpp>

class InfoDialogBase: public VectorEntryDialogBase {
public:
	InfoDialogBase(
		VectorEntry*, 
		QWidget* = nullptr,
		Qt::WindowFlags = Qt::WindowFlags()
	);
	
protected:
	QTableWidget* i_table = nullptr;

	QTableWidget* i_interval = nullptr;
	QList<double> i_probs = {
		0.99, 0.98, 0.97, 0.96, 0.95, 0.9, 0.85, 0.8, 0.7, 0.6
	};

	ui::Section* i_additionalSection = nullptr;
	QTextEdit* i_additionalText = nullptr;

protected:
	QString n(double);
	void fillTable(QList<QStringList>);
	void fillConfidence(QList<std::tuple<QString, QString, std::function<double(double, ss::Bound)>, QString>>);

protected:
	double i_prob = 0.95;
	static const int i_precision = 4;
	QStringList i_headers = {
		"Назва", "Позначення", "Незсунуте значення", "σ{θ}", "Нижн. дов. знач. (0.95)", 
		"Зсунуте значення", "Верх. дов. знач. (0.95)"
	};
	bool i_isResized = false;
};

#endif // !_INFO_DIALOG_BASE_HPP_
