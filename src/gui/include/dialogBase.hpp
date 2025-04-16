
#ifndef _DIALOG_BASE_HPP_
#define _DIALOG_BASE_HPP_

#include<Qt>
#include<QDialog>
#include<QMessageBox>
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

	template<typename T>
	QString m(T mtrx) {
		QList<QList<QString>> r;
		for (auto const& x : mtrx) {
			QList<QString> row;
			for (auto const& y : x)
			row.push_back(n(y));
			r.push_back(row);
		}

		return ms(r);
	}

	template<typename T>
	QString ms(T s) {
		int maxw = 0;
		for (auto const& x : s) {
			for (auto const& y : x) {
				if (y.size() > maxw)
					maxw = y.size();
			}
		}

		QString str;
		QTextStream a;
		a.setString(&str);
		a.setFieldAlignment(QTextStream::FieldAlignment::AlignLeft);
		for (auto& x : s) {
			a.setFieldWidth(maxw+1);
			for (auto it = x.begin(); it < x.end()-1; it++) {
				a << *it;
			}
			a.setFieldWidth(0);
			a << x.back();
			a << "\n";
		}

		str.chop(1);
		return str;
	}
	static const int i_precision = 4;

protected:
	void err(const QString& msg) {
		QMessageBox::warning(this, "Помилка", msg);
	}

public slots:
	virtual void fill() = 0;

protected:
	QVBoxLayout* v_mainLayout = nullptr;
};

#endif // !_DIALOG_BASE_HPP_
