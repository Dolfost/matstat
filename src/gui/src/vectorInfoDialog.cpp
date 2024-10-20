#include "vectorInfoDialog.hpp"
#include "Section.h"

#include <namedWidget.hpp>
#include <sectionedWidget.hpp>

VectorInfoDialog::VectorInfoDialog(
		Vector* v,
		QWidget *p, Qt::WindowFlags f) 
	: InfoDialogBase(v, p, f) {
	v_vector = v;

	auto tw = new NamedWidget<InfoTableWidget>;
	tw->setTitle("Точкові оцінки");
	tw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	v_table = tw->widget();
	v_mainLayout->insertWidget(0, tw);

	auto iw = new SectionedWidget<IntervalTableWidget>;
	iw->setTitle("Інтервальні оцінки");
	v_interval = iw->widget();
	v_mainLayout->insertWidget(1, iw);

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
	ss::Vector& vv = *v_vector->vector();
	QList<QStringList> contents = {
		{
			"Стат. початковий момент першого порядку", "v₁",
			n(vv.mean()), 
			n(vv.meanDeviation()),
			n(vv.meanConfidence(i_prob, ss::Bound::Lower)),
			"",
			n(vv.meanConfidence(i_prob, ss::Bound::Upper)),
		},
		{
			"Стат. центральний момент другого порядку", "μ₂",
			n(vv.variance()),
			n(vv.varianceDeviation()),
			n(vv.varianceConfidence(i_prob, ss::Bound::Lower)),
			n(vv.variance(ss::Measure::Population)),
			n(vv.varianceConfidence(i_prob, ss::Bound::Upper)),
		 },
		{
			"Коефіцієнт асиметрії", "A",
			n(vv.skew()),
			n(vv.skewDeviation()),
			n(vv.skewConfidence(i_prob, ss::Bound::Lower)),
			n(vv.skew(ss::Measure::Population)),
			n(vv.skewConfidence(i_prob, ss::Bound::Upper)),
		},
		{
			"Коефіцієнт ексцесу", "E",
			n(vv.kurtosis()), 
			n(vv.kurtosisDeviation()),
			n(vv.kurtosisConfidence(i_prob, ss::Bound::Lower)),
			n(vv.kurtosis(ss::Measure::Population)),
			n(vv.kurtosisConfidence(i_prob, ss::Bound::Upper)),
		},
		{
			"Медіана серідніх Уолша", "WAM",
			n(vv.wam()),
			"",
			"", 
			"", 
			""
		},
		{
			"Середньоквадратичне відхилення", "СКВ",
			n(vv.sd()),
			"",
			"", 
			n(vv.sd(ss::Measure::Population)),
			""
		},
		{
			"Абсолютне відхилення медіани", "MAD",
			n(vv.mad()), 
			"",
			"",
			"", 
			"", 
			""
		},
		{
			"Коефіцієнт контрексцесу", "𝜘",
			n(vv.counterKurtosis()), 
			"",
			"",
			n(vv.counterKurtosis(ss::Measure::Population)),
			""
		},
		{
			"Коефіцієнт варіації Пірсона", "W",
			n(vv.cv()), 
			"",
			"", 
			n(vv.cv(ss::Measure::Population)),
			""
		},
		{
			"Непараметричнйи коефіцієнт варіації", "Wₕ",
			n(vv.ncv()),
			"",
			"", 
			"", 
			""
		},
		{
			"Медіана", "MED", 
			n(vv.med()), 
			"", 
			"", 
			"", 
			""
		},
		{
			"Розмір", "N", 
			n(vv.size()),
			"",
			"", 
			"", 
			""
		},
		{
			"Найменше спостереження", "xₘᵢₙ", 
			n(vv.min()), 
			"", 
			"", 
			"", 
			""
		},
		{
			"Найбільше спостереження", "xₘₐₓ", 
			n(vv.max()),
			"", 
			"",
			"",
			""
		},
		{
			"Кількість варіант", "r", 
			n(vv.vs.count()),
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
				n(vv.centralMoment(x)),
				"", 
				"", 
				n(vv.centralMoment(x, ss::Measure::Population)), 
				""
			}
		);
	}

	for (int x = 1; x <= 8; x++) {
		contents.append(
			{
				"Початковий момент " + QString::number(x) + " порядку", "v" + QString(QChar(0x2080+x)), 
				n(vv.rawMoment(x)), 
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
				n(vv.tmean(x)),
				"", 
				"",
				"", 
				""
			}
		);
	}

	v_table->fill(contents);

	v_interval->fill({
		{
			"v₁",
			n(vv.meanDeviation()),
			[&](double a, ss::Bound b) { return vv.meanConfidence(a, b); },
			n(vv.mean()),
		},
		{
    "μ₂",
			n(vv.varianceDeviation()),
			[&](double a, ss::Bound b) { return vv.varianceConfidence(a, b); },
			n(vv.variance()),
		},
		{
			"A", 
			n(vv.skewDeviation()),
			[&](double a, ss::Bound b) { return vv.skewConfidence(a, b); },
			n(vv.skew()),
		},
		{
			"E", 
			n(vv.kurtosisDeviation()),
			[&](double a, ss::Bound b) { return vv.kurtosisConfidence(a, b); },
			n(vv.kurtosis()),
		},
	});

	int row, col;
	QStringList header;
	v_var->setColumnCount(vv.vs.count());
	col = 0;
	for (auto const& [variant, value] : vv.vs()) {
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

	if (v_vector->distribuitonModel() != ss::Vector::Distribution::Model::Unknown) {
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
		for (auto const& p : v_vector->distributionParameters()) {
			addInfo.append(
				QString::fromStdString("    " + ss::Vector::Distribution::parameterName[(int)v_vector->model()][i++]) + 
				" " + n(p) + "\n");
		}
		i_additionalText->setText(addInfo);
	} else
		i_additionalText->setText("Вектор було імпортовано в програму.");
}


