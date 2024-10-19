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

	class InfoTableWidget: public QTableWidget {
	public:
		InfoTableWidget(
			QStringList = {
				"Назва", "Позначення", "Незсунуте значення", "σ{θ}", "Нижн. дов. знач. (0.95)", 
				"Зсунуте значення", "Верх. дов. знач. (0.95)"
			}
		);
		void fill(QList<QStringList>);
		void setHeaders(QStringList h) {
			i_headers = h;
		}
	protected:
		QStringList i_headers;
	};

	class IntervalTableWidget: public QTableWidget {
	public:
		IntervalTableWidget();
		void fill(
			QList<std::tuple<QString, QString, std::function<double(double, ss::Bound)>,
			QString>>
		);
	protected:
		QList<double> i_probs = {
			0.99, 0.98, 0.97, 0.96, 0.95, 0.9, 0.85, 0.8, 0.7, 0.6
		};
	};

	class Item: public QTableWidgetItem {
	public:
		Item(
			const QString& text, 
			int type = Type
		): QTableWidgetItem(text, type) {
			QFont f("JuliaMono");
			setFont(f);
		}
	};
	
protected:
	ui::Section* i_additionalSection = nullptr;
	QTextEdit* i_additionalText = nullptr;

protected:
	double i_prob = 0.95;
};

#endif // !_INFO_DIALOG_BASE_HPP_
