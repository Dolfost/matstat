#include "vectorInfoDialog.hpp"
#include "gui/Section.h"
#include <QtCore/qcontainerfwd.h>
#include <locale>

VectorInfoDialog::VectorInfoDialog(
		DataVector* vec, QString name,
		QWidget *parent, Qt::WindowFlags f) 
	: QDialog(parent, f) {
		dv = vec;
		vecName = name;

		this->setWindowTitle("Інформація про вектор " + vecName);
		this->setAttribute(Qt::WA_DeleteOnClose, true);
		QVBoxLayout* mainLayout = new QVBoxLayout();
		this->setLayout(mainLayout);
		mainLayout->setContentsMargins(8,8,8,8);
		mainLayout->setSpacing(8);

		QGroupBox* gropupBox = new QGroupBox("Точкові оцінки");
		auto* lay = new QVBoxLayout;
		QTableWidget* charTable = new QTableWidget;
		charTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		charTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		lay->setContentsMargins(0,0,0,0);
		gropupBox->setLayout(lay);
		lay->addWidget(charTable);
		mainLayout->addWidget(gropupBox);

		QStringList headers = {
			"Назва", "Позначення", "Значення"
		};

		QList<QStringList> contents = {
		{"Математичне сподівання", "v₁", QString::number(dv->mean(), 'f', precision)},
		{"Дисперсія", "μ₂", QString::number(dv->variance(), 'f', precision)},
		{"Медіана", "MED", QString::number(dv->med(), 'f', precision)},
		{"Медіана серідніх Уолша", "WAM", QString::number(dv->walshAveragesMed(), 'f', precision)},
		{"Середньоквадратичне відхилення", "СКВ", QString::number(dv->standardDeviation(), 'f', precision)},
		{"Абсолютне відхилення медіани", "MAD", QString::number(dv->mad(), 'f', precision)},
		{"Коефіцієнт асиметрії", "A", QString::number(dv->skew(), 'f', precision)},
		{"Коефіцієнт ексцесу", "E", QString::number(dv->kurtosis(), 'f', precision)},
		{"Коефіцієнт варіації пірсона", "W", QString::number(dv->variationCoef(), 'f', precision)},
		{"Усічене середнє (α=0.1)", "X*", QString::number(dv->turncatedMean(0.1), 'f', precision)},
		{"Усічене середнє (α=0.2)", "X*", QString::number(dv->turncatedMean(0.2), 'f', precision)},
		{"Усічене середнє (α=0.3)", "X*", QString::number(dv->turncatedMean(0.3), 'f', precision)},
		{"Усічене середнє (α=0.4)", "X*", QString::number(dv->turncatedMean(0.4), 'f', precision)},
		{"Усічене середнє (α=0.5)", "X*", QString::number(dv->turncatedMean(0.5), 'f', precision)},
		{"Центральний момент 1 порядку", "μ₁", QString::number(dv->centralMoment(1), 'f', precision)},
		{"Центральний момент 2 порядку", "μ₂", QString::number(dv->centralMoment(2), 'f', precision)},
		{"Центральний момент 3 порядку", "μ₃", QString::number(dv->centralMoment(3), 'f', precision)},
		{"Центральний момент 4 порядку", "μ₄", QString::number(dv->centralMoment(4), 'f', precision)},
		{"Центральний момент 5 порядку", "μ₅", QString::number(dv->centralMoment(5), 'f', precision)},
		{"Початковий момент 1 порядку", "v₁", QString::number(dv->rawMoment(1), 'f', precision)},
		{"Початковий момент 2 порядку", "v₂", QString::number(dv->rawMoment(2), 'f', precision)},
		{"Початковий момент 3 порядку", "v₃", QString::number(dv->rawMoment(3), 'f', precision)},
		{"Початковий момент 4 порядку", "v₄", QString::number(dv->rawMoment(4), 'f', precision)},
		{"Початковий момент 5 порядку", "v₅", QString::number(dv->rawMoment(5), 'f', precision)},
		};

		QList<int> columnWidths = {
			230, 80, 120
		};


		charTable->setRowCount(contents.length());
		charTable->setColumnCount(contents[0].length());
		charTable->setHorizontalHeaderLabels(headers);

		int col = 0, row = 0;
		for (auto& rowLabels : contents) {
			col = 0;
			for (auto& itemLabel : rowLabels) {
				QTableWidgetItem* tableItem = new QTableWidgetItem(itemLabel);
				charTable->setItem(row, col, tableItem);
				charTable->setColumnWidth(col, columnWidths[col]);
				col++;
			}
			row++;
		}



		ui::Section* section = new ui::Section("Інтервальні оцінки", 100);
		lay = new QVBoxLayout;
		lay->setContentsMargins(0,0,0,0);
		section->setContentLayout(*lay);
		charTable = new QTableWidget();
		charTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		lay->addWidget(charTable);
		mainLayout->addWidget(section);


		section = new ui::Section("Варіаційний ряд", 100);
		lay = new QVBoxLayout;
		lay->setContentsMargins(0,0,0,0);
		charTable = new QTableWidget;
		charTable->setFixedHeight(120);
		charTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		lay->addWidget(charTable);
		mainLayout->addWidget(section);

		charTable->setRowCount(3);
		charTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		charTable->setColumnCount(dv->size());
		charTable->setVerticalHeaderLabels(
				{"Варіанта", "Кількість", "Відносна частота"}
				);

		VarSeries varSeries(dv);
		varSeries.makeSeries();
		col = 0;
		for (auto const& [variant, value] : varSeries.series()) {
			QTableWidgetItem* tableItem = new QTableWidgetItem(
					QString::number(variant, 'f', precision));
			charTable->setItem(0, col, tableItem);
			tableItem = new QTableWidgetItem(
					QString::number(value.first));
			charTable->setItem(1, col, tableItem);
			tableItem = new QTableWidgetItem(
					QString::number(value.second, 'f', precision));
			charTable->setItem(2, col, tableItem);
			col++;
		}
		section->setContentLayout(*lay);

		this->resize(800, 300);
		this->show();
}

void VectorInfoDialog::vectorDeletedHandler(int idx, DataVector* vec) {
	if (dv == vec)
		this->close();
}
