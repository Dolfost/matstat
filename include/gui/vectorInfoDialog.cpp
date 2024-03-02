#include "vectorInfoDialog.hpp"
#include "gui/Section.h"
#include <QtCore/qcontainerfwd.h>
#include <locale>
#include <numeric>

VectorInfoDialog::VectorInfoDialog(
		DataVector* vec, QString name,
		QWidget *parent, Qt::WindowFlags f) 
	: QDialog(parent, f) {
		dv = vec;
		vecName = name;

		VarSeries varSeries(dv);
		varSeries.makeSeries();

		this->setWindowTitle("Інформація про вектор " + vecName);
		this->setAttribute(Qt::WA_DeleteOnClose, true);
		QVBoxLayout* mainLayout = new QVBoxLayout();
		this->setLayout(mainLayout);
		mainLayout->setContentsMargins(8,8,8,8);
		mainLayout->setSpacing(8);

		QGroupBox* gropupBox = new QGroupBox("Точкові оцінки");
		auto* lay = new QHBoxLayout;
		QTableWidget* charTable = new QTableWidget;
		charTable->verticalHeader()->hide();
		charTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		charTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		lay->setContentsMargins(0,0,0,0);
		gropupBox->setLayout(lay);
		lay->addWidget(charTable);
		mainLayout->addWidget(gropupBox);

		QStringList headers = {
			"Назва", "Позначення", "Значення", "Зсунуте значення"
		};

		QList<QStringList> contents = {
		{"Математичне сподівання", "v₁", QString::number(dv->mean(), 'f', precision), "—"},
		{"Дисперсія", "μ₂", QString::number(dv->variance(), 'f', precision),
			QString::number(dv->variance(DataVector::Measure::Population), 'f', precision), "—"},
		{"Медіана", "MED", QString::number(dv->med(), 'f', precision),"—"},
		{"Розмір", "N", QString::number(dv->size()),"—"},
		{"Найменше спостереження", "xₘᵢₙ", QString::number(dv->min(), 'f', precision),"—"},
		{"Найбільше спостереження", "xₘₐₓ", QString::number(dv->max(), 'f', precision),"—"},
		{"Кількість варіант", "r", QString::number(varSeries.variantsCount()),"—"},
		{"Медіана серідніх Уолша", "WAM", QString::number(dv->walshAveragesMed(), 'f', precision),"—"},
		{"Середньоквадратичне відхилення", "СКВ", QString::number(dv->standardDeviation(), 'f', precision),
			QString::number(dv->standardDeviation(DataVector::Measure::Population), 'f', precision)},
		{"Абсолютне відхилення медіани", "MAD", QString::number(dv->mad(), 'f', precision), "—"},
		{"Коефіцієнт асиметрії", "A", QString::number(dv->skew(), 'f', precision),
			QString::number(dv->skew(DataVector::Measure::Population), 'f', precision)},
		{"Коефіцієнт ексцесу", "E", QString::number(dv->kurtosis(), 'f', precision), 
			QString::number(dv->kurtosis(DataVector::Measure::Population), 'f', precision)},
		{"Коефіцієнт варіації пірсона", "W", QString::number(dv->variationCoef(), 'f', precision), 
			QString::number(dv->variationCoef(DataVector::Measure::Population), 'f', precision)}
		};

		for (int x = 1; x <= 8; x++) {
		contents.append({"Центральний момент " + QString::number(x) + " порядку",
				"μ" + QString(QChar(0x2080+x)), QString::number(dv->centralMoment(x), 'f', precision),
				QString::number(dv->centralMoment(x, DataVector::Measure::Population), 'f', precision)});
		}
		for (int x = 1; x <= 8; x++) {
		contents.append({"Початковий момент " + QString::number(x) + " порядку",
				"v" + QString(QChar(0x2080+x)), QString::number(dv->rawMoment(x), 'f', precision), "—"});
		}
		for (double x = 0.0; x <= 0.5 ; x+=0.05) {
		contents.append({"Усічене середнє (α=" + QString::number(x) + ")", 
				"X*", QString::number(dv->turncatedMean(x), 'f', precision), "—"});
		}

		QList<int> columnWidths = {
			230, 80, 200, 200
		};

		charTable->setMinimumWidth(std::accumulate(columnWidths.begin(), columnWidths.end(), 20));
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
		lay = new QHBoxLayout;
		lay->setContentsMargins(0,0,0,0);
		charTable = new QTableWidget();
		charTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		charTable->setRowCount(4);
		charTable->setColumnCount(2);
		headers = {"Величина", "Значення"};
		charTable->verticalHeader()->hide();
		charTable->setFixedHeight(165);
		charTable->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
		charTable->setHorizontalHeaderLabels(headers);
		lay->addWidget(charTable);
		mainLayout->addWidget(section);
		QList<QStringList> deviation = {
			{"σ{v₁}", QString::number(dv->meanDeviation(), 'f', precision)},
			{"σ{μ₂}", QString::number(dv->varianceDeviation(), 'f', precision)},
			{"σ{A}", QString::number(dv->skewDeviation(), 'f', precision)},
			{"σ{E}", QString::number(dv->kurtosisDeviation(), 'f', precision)},
		};
		charTable->setColumnWidth(0, 75);
		charTable->setColumnWidth(1, 150);
		for (row = 0; row < charTable->rowCount(); row++) {
			for (col = 0; col < charTable->columnCount(); col++) {
				QTableWidgetItem* tableItem = new QTableWidgetItem(deviation[row][col]);
				charTable->setItem(row, col, tableItem);
			}
		}
		section->setContentLayout(*lay);

		charTable = new QTableWidget();
		charTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		charTable->setRowCount(4);
		headers = {"Величина"};
		charTable->verticalHeader()->hide();
		charTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		lay->addWidget(charTable);
		QList<double> probs = {
			0.99, 0.98, 0.97, 0.95, 0.9, 0.85, 0.8, 0.75, 0.7, 0.65,
			0.6, 0.55, 0.5, 0.45, 0.4
		};

		charTable->setColumnCount(probs.length()+1);
		charTable->setColumnWidth(0, 70);

		charTable->setItem(0, 0, new QTableWidgetItem("θv₁"));
		charTable->setItem(1, 0, new QTableWidgetItem("θμ₂"));
		charTable->setItem(2, 0, new QTableWidgetItem("θA"));
		charTable->setItem(3, 0, new QTableWidgetItem("θE"));

		for (col = 1 ; col < charTable->columnCount(); col++) {
			headers.append("𝛼 = " + QString::number(probs[col-1]));
			charTable->setItem(0, col, new QTableWidgetItem("fd"));
			charTable->setItem(1, col, new QTableWidgetItem("df"));
			charTable->setItem(2, col, new QTableWidgetItem("gjl"));
			charTable->setItem(3, col, new QTableWidgetItem("glj;"));
		}

		charTable->setHorizontalHeaderLabels(headers);




		section = new ui::Section("Варіаційний ряд", 100);
		lay = new QHBoxLayout;
		lay->setContentsMargins(0,0,0,0);
		charTable = new QTableWidget;
		charTable->setFixedHeight(130);
		charTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		lay->addWidget(charTable);
		mainLayout->addWidget(section);

		charTable->setRowCount(3);
		charTable->setColumnCount(varSeries.variantsCount());
		charTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		charTable->setVerticalHeaderLabels(
				{"Варіанта", "Кількість", "Відносна частота"}
				);

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
