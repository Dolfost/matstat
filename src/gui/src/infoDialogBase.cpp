#include <infoDialogBase.hpp>

#include <QHeaderView>
#include <QBuffer>

InfoDialogBase::InfoDialogBase(
	VectorEntry* ve, 
	QWidget* p,
	Qt::WindowFlags f): VectorEntryDialogBase(ve, p, f) {
	setWindowTitle("Інформація про вектор " + v_vectorEntry->name());

	v_mainLayout->setContentsMargins(0, 0, 0, 5);

	i_additionalSection = new ui::Section("Додаткова інформація", 200);
	i_additionalText = new QTextEdit;
	QHBoxLayout* lay = new QHBoxLayout;
	lay->setContentsMargins(0,0,0,0);
	i_additionalText = new QTextEdit;
	i_additionalText->setMaximumHeight(100);
	i_additionalText->setReadOnly(true);
	lay->addWidget(i_additionalText);
	i_additionalSection->setContentLayout(*lay);

	resize(700, 200);
}

QString InfoDialogBase::n(double arg) {
	return QString::number(arg, 'f', i_precision);
}

QString InfoDialogBase::m(QList<QList<double>> mtrx) {
	QList<QList<QString>> r;
	for (auto const& x : mtrx) {
		QList<QString> row;
		for (auto const& y : x)
			row.push_back(n(y));
		r.push_back(row);
	}
	
	return ms(r);
}

QString InfoDialogBase::ms(QList<QList<QString>> s) {
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

InfoDialogBase::InfoTableWidget::InfoTableWidget(
	QStringList headers 
) {
	i_headers = headers;
	verticalHeader()->hide();
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
}

void InfoDialogBase::InfoTableWidget::fill(QList<QStringList> contents) {
	if (contents.length() == 0)
		return;
	clear();
	setRowCount(contents.length());
	setColumnCount(contents[0].length());
	setHorizontalHeaderLabels(i_headers);

	int col = 0, row = 0;
	for (auto& rowLabels : contents) {
		col = 0;
		for (auto& itemLabel : rowLabels) {
			Item* tableItem = new Item(
				itemLabel.size() ? itemLabel : "—"
			);
			setItem(row, col, tableItem);
			col++;
		}
		row++;
	}
}

InfoDialogBase::IntervalTableWidget::IntervalTableWidget() {
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	setColumnCount(2 + 2*i_probs.size());
	horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
}

void InfoDialogBase::IntervalTableWidget::fill( // name, deviation, conf functor, value
	QList<std::tuple<QString, QString, std::function<double(double, ss::Bound)>, QString>> l
) {
	QStringList header = {"σ{T}"};
	header.resize(2 + 2*i_probs.size());
	header[i_probs.size()+1] = "θ зсунута";
	QStringList vheader;

	setRowCount(l.size());

	int col, row;
	for (row = 0 ; row < l.size(); row++) {
		setItem(row, 0, new Item(std::get<1>(l[row]).size() ? std::get<1>(l[row]) : "—"));
		setItem(row, i_probs.size()+1, new Item(std::get<3>(l[row])));
		vheader.push_back(std::get<0>(l[row]).size() ? std::get<0>(l[row]) : "—");
		for (col = 1 ; col < i_probs.length()+1; col++) {
			int prob = col - 1;
			header[col] = ("INF 𝛼 = " + QString::number(i_probs[prob]));
			setItem(row, col, new Item(
				n(std::get<2>(l[row])(i_probs[prob], ss::Bound::Lower))
			));
			header[2*i_probs.size() + 2 - col] = ("SUP 𝛼 = " + QString::number(i_probs[prob]));
			setItem(row, 2*i_probs.size() + 2 - col, new Item(
				n(std::get<2>(l[row])(i_probs[prob], ss::Bound::Upper))
			));
		}
	}

	setVerticalHeaderLabels(vheader);
	setHorizontalHeaderLabels(header);
}
