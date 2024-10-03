#include "vectorInfoDialog.hpp"
#include "Section.h"

VectorInfoDialog::VectorInfoDialog(
		Vector* v,
		QWidget *p, Qt::WindowFlags f) 
	: InfoDialogBase(v, p, f) {
	v_vector = v;


	ui::Section* section = new ui::Section("Варіаційний ряд", 150);
	QHBoxLayout* lay = new QHBoxLayout;
	lay->setContentsMargins(0,0,0,0);
	v_var = new QTableWidget;
	v_var->setEditTriggers(QAbstractItemView::NoEditTriggers);
	v_var->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	lay->addWidget(v_var);
	v_mainLayout->addWidget(section);
	v_var->setRowCount(3);
	v_var->setVerticalHeaderLabels(
		{"Xᵢ", "Nᵢ", "Pᵢ"}
	);
	v_var->setFixedHeight(130);
	section->setContentLayout(*lay);
	
	v_mainLayout->addWidget(i_additionalSection);

	fill();
}

void VectorInfoDialog::fill() {
	QList<QStringList> contents = {
		{
			"Стат. початковий момент першого порядку", "v₁",
			n(v_vector->vector()->mean()), 
			n(v_vector->vector()->meanDeviation()),
			n(v_vector->vector()->meanConfidence(i_prob, ss::Bound::Lower)),
			"",
			n(v_vector->vector()->meanConfidence(i_prob, ss::Bound::Upper)),
		},
		{
			"Стат. центральний момент другого порядку", "μ₂",
			n(v_vector->vector()->variance()),
			n(v_vector->vector()->varianceDeviation()),
			n(v_vector->vector()->varianceConfidence(i_prob, ss::Bound::Lower)),
			n(v_vector->vector()->variance(ss::Measure::Population)),
			n(v_vector->vector()->varianceConfidence(i_prob, ss::Bound::Upper)),
		 },
		{
			"Коефіцієнт асиметрії", "A",
			n(v_vector->vector()->skew()),
			n(v_vector->vector()->skewDeviation()),
			n(v_vector->vector()->skewConfidence(i_prob, ss::Bound::Lower)),
			n(v_vector->vector()->skew(ss::Measure::Population)),
			n(v_vector->vector()->skewConfidence(i_prob, ss::Bound::Upper)),
		},
		{
			"Коефіцієнт ексцесу", "E",
			n(v_vector->vector()->kurtosis()), 
			n(v_vector->vector()->kurtosisDeviation()),
			n(v_vector->vector()->kurtosisConfidence(i_prob, ss::Bound::Lower)),
			n(v_vector->vector()->kurtosis(ss::Measure::Population)),
			n(v_vector->vector()->kurtosisConfidence(i_prob, ss::Bound::Upper)),
		},
		{
			"Медіана серідніх Уолша", "WAM",
			n(v_vector->vector()->wam()),
			"",
			"", 
			"", 
			""
		},
		{
			"Середньоквадратичне відхилення", "СКВ",
			n(v_vector->vector()->sd()),
			"",
			"", 
			n(v_vector->vector()->sd(ss::Measure::Population)),
			""
		},
		{
			"Абсолютне відхилення медіани", "MAD",
			n(v_vector->vector()->mad()), 
			"",
			"",
			"", 
			"", 
			""
		},
		{
			"Коефіцієнт контрексцесу", "𝜘",
			n(v_vector->vector()->counterKurtosis()), 
			"",
			"",
			n(v_vector->vector()->counterKurtosis(ss::Measure::Population)),
			""
		},
		{
			"Коефіцієнт варіації Пірсона", "W",
			n(v_vector->vector()->cv()), 
			"",
			"", 
			n(v_vector->vector()->cv(ss::Measure::Population)),
			""
		},
		{
			"Непараметричнйи коефіцієнт варіації", "Wₕ",
			n(v_vector->vector()->ncv()),
			"",
			"", 
			"", 
			""
		},
		{
			"Медіана", "MED", 
			n(v_vector->vector()->med()), 
			"", 
			"", 
			"", 
			""
		},
		{
			"Розмір", "N", 
			n(v_vector->vector()->size()),
			""
			"", 
			"", 
			""
		},
		{
			"Найменше спостереження", "xₘᵢₙ", 
			n(v_vector->vector()->min()), 
			"", 
			"", 
			"", 
			""
		},
		{
			"Найбільше спостереження", "xₘₐₓ", 
			n(v_vector->vector()->max()),
			"", 
			"",
			"",
			""
		},
		{
			"Кількість варіант", "r", 
			n(v_vector->vector()->vs.count()),
			"", 
			"", 
			"",
			""
		},
	};

	for (int x = 1; x <= 8; x++) {
		contents.append(
			{
				"Центральний момент " + QString::number(x) + " порядку", "μ" + QString(QChar(0x2080+x)), 
				n(v_vector->vector()->centralMoment(x)),
				"", 
				"", 
				n(v_vector->vector()->centralMoment(x, ss::Measure::Population)), 
				""
			}
		);
	}

	for (int x = 1; x <= 8; x++) {
		contents.append(
			{
				"Початковий момент " + QString::number(x) + " порядку", "v" + QString(QChar(0x2080+x)), 
				n(v_vector->vector()->rawMoment(x)), 
				"", 
				"", 
				"", 
				""
			}
		);
	}

	for (double x = 0.0; x <= 0.5 ; x+=0.05) {
		contents.append(
			{
				"Усічене середнє (α=" + QString::number(x) + ")", "X*", 
				n(v_vector->vector()->tmean(x)),
				"", 
				"",
				"", 
				""
			}
		);
	}
	fillTable(contents);

	fillConfidence({
		{
			"v₁",
			n(v_vector->vector()->meanDeviation()),
			[=](double a, ss::Bound b) { return v_vector->vector()->meanConfidence(a, b); },
			n(v_vector->vector()->mean()),
		},
		{
    "μ₂",
			n(v_vector->vector()->varianceDeviation()),
			[=](double a, ss::Bound b) { return v_vector->vector()->varianceConfidence(a, b); },
			n(v_vector->vector()->variance()),
		},
		{
			"A", 
			n(v_vector->vector()->skewDeviation()),
			[=](double a, ss::Bound b) { return v_vector->vector()->skewConfidence(a, b); },
			n(v_vector->vector()->skew()),
		},
		{
			"E", 
			n(v_vector->vector()->kurtosisDeviation()),
			[=](double a, ss::Bound b) { return v_vector->vector()->kurtosisConfidence(a, b); },
			n(v_vector->vector()->kurtosis()),
		},
	});

	int row, col;
	QStringList header;
	v_var->setColumnCount(v_vector->vector()->vs.count());
	col = 0;
	for (auto const& [variant, value] : v_vector->vector()->vs()) {
		QTableWidgetItem* tableItem = new QTableWidgetItem(
			n(variant)
		);
		v_var->setItem(0, col, tableItem);
		tableItem = new QTableWidgetItem(
			n(value.first)
		);
		v_var->setItem(1, col, tableItem);
		tableItem = new QTableWidgetItem(
			n(value.second));
		v_var->setItem(2, col, tableItem);
		col++;
	}

	if (v_vector->isModeled()) {
		QString addInfo = QString(
			"Вектор %1 змодельвано у програмі.\n"
			"  Метод: %2\n"
			"  Розподіл: %3\n"
			"  Параметри: \n"
		)
			.arg(v_vector->name())
			.arg(QString::fromStdString(ss::Vector::Distribution::methodName[(int)v_vector->method()]))
			.arg(QString::fromStdString(ss::Vector::Distribution::distributionName[(int)v_vector->model()]));
		int i = 0;
		for (auto const& p : v_vector->parameters()) {
			addInfo.append(
				QString::fromStdString("    " + ss::Vector::Distribution::parameterName[(int)v_vector->model()][i++]) + 
				" " + n(p) + "\n");
		}
		i_additionalText->setText(addInfo);
	} else
		i_additionalText->setText("Вектор було імпортовано в програму.");
}


