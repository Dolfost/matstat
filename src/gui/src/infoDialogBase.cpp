#include <infoDialogBase.hpp>

#include <QHeaderView>
#include <QBuffer>

InfoDialogBase::InfoDialogBase(
	VectorEntry* ve, 
	QWidget* p,
	Qt::WindowFlags f): VectorEntryDialogBase(ve, p, f) {
	setWindowTitle("Інформація про вектор " + v_vectorEntry->name());

	v_mainLayout->setContentsMargins(0, 0, 0, 5);

	i_table = new QTableWidget;
	i_table->verticalHeader()->hide();
	i_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	i_table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	i_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	i_table->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	v_mainLayout->addWidget(i_table);

	ui::Section* section = new ui::Section("Інтервальні оцінки", 100, this);
	QHBoxLayout* lay = new QHBoxLayout;
	lay->setContentsMargins(0,0,0,0);
	i_interval = new QTableWidget();
	i_interval->setEditTriggers(QAbstractItemView::NoEditTriggers);
	i_interval->setColumnCount(2 + 2*i_probs.size());
	i_interval->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	i_interval->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
	lay->addWidget(i_interval);
	v_mainLayout->addWidget(section);
	section->setContentLayout(*lay);


	i_additionalSection = new ui::Section("Додаткова інформація", 200);
	i_additionalText = new QTextEdit;
	lay = new QHBoxLayout;
	lay->setContentsMargins(0,0,0,0);
	i_additionalText = new QTextEdit;
	i_additionalText->setMaximumHeight(100);
	i_additionalText->setReadOnly(true);
	lay->addWidget(i_additionalText);
	i_additionalSection->setContentLayout(*lay);

	resize(450, 200);
	show();
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

void InfoDialogBase::fillTable(QList<QStringList> contents) {
	i_table->clear();
	i_table->setRowCount(contents.length());
	i_table->setColumnCount(contents[0].length());
	i_table->setHorizontalHeaderLabels(i_headers);

	int col = 0, row = 0;
	for (auto& rowLabels : contents) {
		col = 0;
		for (auto& itemLabel : rowLabels) {
			InfoTableWidgetItem* tableItem = new InfoTableWidgetItem(
				itemLabel.size() ? itemLabel : "—"
			);
			i_table->setItem(row, col, tableItem);
			col++;
		}
		row++;
	}

	int width = 0;
	for (int i = 0; i < 3; i += 1) {
		width += i_table->horizontalHeader()->sectionSize(i);
	}

	if (!i_isResized) {
		resize(width + 50, height());
		i_isResized = true;
	}
}

void InfoDialogBase::fillConfidence( // name, deviation, conf functor, value
	QList<std::tuple<QString, QString, std::function<double(double, ss::Bound)>, QString>> l
) {

	QStringList header = {"σ{T}"};
	header.resize(2 + 2*i_probs.size());
	header[i_probs.size()+1] = "θ зсунута";
	QStringList vheader;

	i_interval->setRowCount(l.size());

	int col, row;
	for (row = 0 ; row < l.size(); row++) {
		i_interval->setItem(row, 0, new InfoTableWidgetItem(std::get<1>(l[row]).size() ? std::get<1>(l[row]) : "—"));
		i_interval->setItem(row, i_probs.size()+1, new InfoTableWidgetItem(std::get<3>(l[row])));
		vheader.push_back(std::get<0>(l[row]).size() ? std::get<0>(l[row]) : "—");
		for (col = 1 ; col < i_probs.length()+1; col++) {
			int prob = col - 1;
			header[col] = ("INF 𝛼 = " + QString::number(i_probs[prob]));
			i_interval->setItem(row, col, new InfoTableWidgetItem(
				n(std::get<2>(l[row])(i_probs[prob], ss::Bound::Lower))
			));
			header[2*i_probs.size() + 2 - col] = ("SUP 𝛼 = " + QString::number(i_probs[prob]));
			i_interval->setItem(row, 2*i_probs.size() + 2 - col, new InfoTableWidgetItem(
				n(std::get<2>(l[row])(i_probs[prob], ss::Bound::Upper))
			));
		}
	}

	i_interval->setVerticalHeaderLabels(vheader);
	i_interval->setHorizontalHeaderLabels(header);
}
