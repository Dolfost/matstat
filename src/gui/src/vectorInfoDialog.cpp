#include "vectorInfoDialog.hpp"
#include "Section.h"
#include <QtCore/qcontainerfwd.h>
#include <numeric>

VectorInfoDialog::VectorInfoDialog(
		VectorEntry* vectorEntry,
		QWidget *parent, Qt::WindowFlags f) 
	: QDialog(parent, f) {
		ve = vectorEntry;

		ss::Vector::VarSeries& varSeries = vectorEntry->vector->varSeries;

		this->setWindowTitle("Інформація про вектор " + vectorEntry->name);
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
			"Назва", "Позначення", "Нижн. дов. знач. (0.95)", "Незсунуте значення",
			"Зсунуте значення", "Верх. дов. знач. (0.95)", "σ{θ}"
		};
		QList<int> columnWidths = {
			300, 80, 150, 130, 120, 150, 60
		};
		double prob = 0.95;

		QList<QStringList> contents = {
		{"Стат. початковий момент першого порядку", "v₁",
			QString::number(ve->vector->meanConfidence(prob,
						ss::Bound::Upper), 'f', precision),
			QString::number(ve->vector->mean(), 'f', precision), "—",
			QString::number(ve->vector->meanConfidence(prob,
						ss::Bound::Lower), 'f', precision),
			QString::number(ve->vector->meanDeviation(), 'f', precision)},
		{"Стат. центральний момент другого порядку", "μ₂",
			QString::number(ve->vector->varianceConfidence(prob,
						ss::Bound::Lower), 'f', precision),
			QString::number(ve->vector->variance(), 'f', precision),
			QString::number(ve->vector->variance(ss::Measure::Population), 'f', precision),
			QString::number(ve->vector->meanConfidence(prob,
						ss::Bound::Upper), 'f', precision),
			QString::number(ve->vector->varianceDeviation(), 'f', precision)},
		{"Коефіцієнт асиметрії", "A",
			QString::number(ve->vector->skewConfidence(prob,
						ss::Bound::Lower), 'f', precision),
			QString::number(ve->vector->skew(), 'f',
				precision),
			QString::number(ve->vector->skew(ss::Measure::Population), 'f', precision),
			QString::number(ve->vector->skewConfidence(prob,
						ss::Bound::Upper), 'f', precision),
			QString::number(ve->vector->skewDeviation(), 'f', precision)},
		{"Коефіцієнт ексцесу", "E",
			QString::number(ve->vector->kurtosisConfidence(prob,
						ss::Bound::Lower), 'f', precision),
			QString::number(ve->vector->kurtosis(),
				'f', precision), 
			QString::number(ve->vector->kurtosis(ss::Measure::Population), 'f', precision),
			QString::number(ve->vector->kurtosisConfidence(prob,
						ss::Bound::Upper), 'f', precision),
			QString::number(ve->vector->kurtosisDeviation(), 'f', precision)},
		{"Медіана серідніх Уолша", "WAM",
			"—",
			QString::number(ve->vector->walshAveragesMed(), 'f',
					precision),
			"—", "—", "—"},
		{"Середньоквадратичне відхилення", "СКВ",
			"—",
			QString::number(ve->vector->sd(), 'f', precision),
			QString::number(ve->vector->sd(ss::Measure::Population), 'f', precision),
			"—", "—"},
		{"Абсолютне відхилення медіани", "MAD",
			"—",
			QString::number(ve->vector->mad(), 'f', precision), "—",
			"—", "—", "—"},
		{"Коефіцієнт контрексцесу", "𝜘",
			"—",
			QString::number(ve->vector->counterKurtosis(), 'f', precision), 
			QString::number(ve->vector->counterKurtosis(ss::Measure::Population), 'f', precision),
			"—", "—"},
		{"Коефіцієнт варіації Пірсона", "W",
			"—",
			QString::number(ve->vector->cv(), 'f', precision), 
			QString::number(ve->vector->cv(ss::Measure::Population), 'f', precision),
			"—", "—"},
		{"Непараметричнйи коефіцієнт варіації", "Wₕ",
			"—",
			QString::number(ve->vector->ncv(), 'f',
					precision), 
			"—", "—", "—"},
		{"Медіана", "MED", "—", QString::number(ve->vector->med(), 'f', precision), "—", "—", "—"},
		{"Розмір", "N", QString::number(ve->vector->size()),"—"},
		{"Найменше спостереження", "xₘᵢₙ", "—", QString::number(ve->vector->min(), 'f', precision), "—", "—", "—"},
		{"Найбільше спостереження", "xₘₐₓ", "—", QString::number(ve->vector->max(), 'f', precision), "—", "—", "—"},
		{"Кількість варіант", "r", "—", QString::number(varSeries.count()), "—", "—","—"},
		};

		for (int x = 1; x <= 8; x++) {
		contents.append({"Центральний момент " + QString::number(x) + " порядку",
				"μ" + QString(QChar(0x2080+x)), "—", QString::number(ve->vector->centralMoment(x), 'f', precision),
				QString::number(ve->vector->centralMoment(x, ss::Measure::Population), 'f', precision), "—", "—"});
		}
		for (int x = 1; x <= 8; x++) {
		contents.append({"Початковий момент " + QString::number(x) + " порядку",
				"v" + QString(QChar(0x2080+x)), "—", QString::number(ve->vector->rawMoment(x), 'f', precision), "—", "—", "—"});
		}
		for (double x = 0.0; x <= 0.5 ; x+=0.05) {
		contents.append({"Усічене середнє (α=" + QString::number(x) + ")", 
				"X*", "—", QString::number(ve->vector->tmean(x), 'f', precision), "—", "—", "—"});
		}


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
			{"σ{v₁}", QString::number(ve->vector->meanDeviation(), 'f', precision)},
			{"σ{μ₂}", QString::number(ve->vector->varianceDeviation(), 'f', precision)},
			{"σ{A}", QString::number(ve->vector->skewDeviation(), 'f', precision)},
			{"σ{E}", QString::number(ve->vector->kurtosisDeviation(), 'f', precision)},
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
			0.99, 0.98, 0.97, 0.95, 0.9, 0.85, 0.8
		};

		charTable->setColumnCount(probs.length()*2+2);
		charTable->setColumnWidth(0, 70);

		charTable->setItem(0, 0, new QTableWidgetItem("θv₁"));
		charTable->setItem(1, 0, new QTableWidgetItem("θμ₂"));
		charTable->setItem(2, 0, new QTableWidgetItem("θA"));
		charTable->setItem(3, 0, new QTableWidgetItem("θE"));

		for (col = 1 ; col < probs.length()+1; col++) {
			int prob = col - 1;
			headers.append("INF 𝛼 = " + QString::number(probs[prob]));
			charTable->setItem(0, col, new QTableWidgetItem(
						QString::number(ve->vector->meanConfidence(probs[prob], 
								ss::Bound::Lower), 'f', precision)));
			charTable->setItem(1, col, new QTableWidgetItem(QString::number(
							ve->vector->varianceConfidence(probs[prob],
								ss::Bound::Lower), 'f', precision)));
			charTable->setItem(2, col, new QTableWidgetItem(QString::number(
							ve->vector->skewConfidence(probs[prob], 
								ss::Bound::Lower), 'f', precision)));
			charTable->setItem(3, col, new QTableWidgetItem(QString::number(
							ve->vector->kurtosisConfidence(probs[prob],
								ss::Bound::Lower), 'f', precision)));
		}

		headers.append("θ зсунута");
		charTable->setItem(0, col, new QTableWidgetItem(
					QString::number(ve->vector->mean(), 'f', precision)));
		charTable->setItem(1, col, new QTableWidgetItem(
					QString::number(ve->vector->variance(ss::Measure::Population), 'f', precision)));
		charTable->setItem(2, col, new QTableWidgetItem(
					QString::number(ve->vector->skew(ss::Measure::Population), 'f', precision)));
		charTable->setItem(3, col, new QTableWidgetItem(
					QString::number(ve->vector->kurtosis(ss::Measure::Population), 'f', precision)));

		for (int from = col; col < charTable->columnCount(); col++) {
			int prob = probs.length() - (col - from) - 1;
			headers.append("SUP 𝛼 = " + QString::number(probs[prob]));
			charTable->setItem(0, col, new QTableWidgetItem(
						QString::number(ve->vector->meanConfidence(probs[prob], 
								ss::Bound::Upper), 'f', precision)));
			charTable->setItem(1, col, new QTableWidgetItem(QString::number(
							ve->vector->varianceConfidence(probs[prob],
								ss::Bound::Upper), 'f', precision)));
			charTable->setItem(2, col, new QTableWidgetItem(QString::number(
							ve->vector->skewConfidence(probs[prob], 
								ss::Bound::Upper), 'f', precision)));
			charTable->setItem(3, col, new QTableWidgetItem(QString::number(
							ve->vector->kurtosisConfidence(probs[prob],
								ss::Bound::Upper), 'f', precision)));
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
		charTable->setColumnCount(varSeries.count());
		charTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		charTable->setVerticalHeaderLabels(
				{"Варіанта", "Кількість", "Відносна частота"}
				);

		col = 0;
		for (auto const& [variant, value] : varSeries()) {
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

		section = new ui::Section("Додаткова інформація про вектор", 100);
		lay = new QHBoxLayout;
		lay->setContentsMargins(0,0,0,0);
		mainLayout->addWidget(section);

		QTextEdit* additionalInfoTextEdit = new QTextEdit;
		additionalInfoTextEdit->setMaximumHeight(100);
		additionalInfoTextEdit->setReadOnly(true);
		lay->addWidget(additionalInfoTextEdit);

		if (ve->isModeled) {
			QString addInfo = QString(
					"Вектор %1 змодельвано у програмі.\n"
					"  Метод: %2\n"
					"  Розподіл: %3\n"
					"  Параметри: "
					)
				.arg(ve->name)
				.arg(ss::DistributionReproducer::methodName[ve->modelMethod])
				.arg(ss::DistributionReproducer::distributionName[ve->modelDistribution]);
			for (auto const& p : ve->modelParameters) {
				addInfo.append(QString::number(p, 'f', 3) + " ");
			}
			additionalInfoTextEdit->append(addInfo);
		}

		section->setContentLayout(*lay);
		

		this->resize(800, 300);
		this->show();
}

void VectorInfoDialog::vectorDeletedHandler(VectorEntry* vectorEntry) {
	if (vectorEntry == ve)
		this->close();
}
