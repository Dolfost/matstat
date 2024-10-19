#include<dialogBase.hpp>

DialogBase::DialogBase(
	QWidget* parent,
	Qt::WindowFlags wflags): QDialog(parent, wflags) {
	setAttribute(Qt::WA_DeleteOnClose, true);
	v_mainLayout = new QVBoxLayout();
	setLayout(v_mainLayout);
	v_mainLayout->setContentsMargins(0, 0, 0, 0);
	show();
	resize(500, 400);
}

QString DialogBase::n(double arg) {
	return QString::number(arg, 'f', i_precision);
}

QString DialogBase::m(QList<QList<double>> mtrx) {
	QList<QList<QString>> r;
	for (auto const& x : mtrx) {
		QList<QString> row;
		for (auto const& y : x)
			row.push_back(n(y));
		r.push_back(row);
	}
	
	return ms(r);
}

QString DialogBase::ms(QList<QList<QString>> s) {
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

