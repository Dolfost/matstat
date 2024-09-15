#include <QHeaderView>
#include <infoDialogBase.hpp>

InfoDialogBase::InfoDialogBase(
	VectorEntry* ve, 
	QWidget* p,
	Qt::WindowFlags f): DialogBase(ve, p, f) {
	setWindowTitle("Інформація про вектор " + v_vectorEntry->name());

	i_table = new QTableWidget;
	i_table->verticalHeader()->hide();
	i_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
	i_table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	v_mainLayout->addWidget(i_table);

	i_additionalSection = new ui::Section("Додаткова інформація", 200);
	i_additionalText = new QTextEdit();
	QHBoxLayout* lay = new QHBoxLayout;
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

void InfoDialogBase::fillTable(QList<QStringList> contents) {
	i_table->clear();
	i_table->setRowCount(contents.length());
	i_table->setColumnCount(contents[0].length());
	i_table->setHorizontalHeaderLabels(i_headers);

	int col = 0, row = 0;
	for (auto& rowLabels : contents) {
		col = 0;
		for (auto& itemLabel : rowLabels) {
			QTableWidgetItem* tableItem = new QTableWidgetItem(itemLabel);
			i_table->setItem(row, col, tableItem);
			i_table->setColumnWidth(col, i_columnWidths[col]);
			col++;
		}
		row++;
	}

	i_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

	int width = 0;
	for (int i = 0; i < 3; i += 1) {
		width += i_table->horizontalHeader()->sectionSize(i);
	}

	resize(width + 15, height());
}
