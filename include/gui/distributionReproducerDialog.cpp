#include "distributionReproducerDialog.hpp"
#include "gui/Section.h"
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qtablewidget.h>
#include <random>

#include "statistics/classSeries.hpp"

DistributionReproducerDialog::DistributionReproducerDialog(
		VectorEntry* vectorEntry,
		QWidget *parent, Qt::WindowFlags f) 
	: QDialog(parent, f) {
		ve = vectorEntry;

		this->setWindowTitle("Інформація про відтворення розподілу " + ve->name);
		this->setAttribute(Qt::WA_DeleteOnClose, true);
		QVBoxLayout* mainLayout = new QVBoxLayout();
		this->setLayout(mainLayout);
		mainLayout->setContentsMargins(10,10,10,10);

		distributionComboBox = new QComboBox();
		for (int i = 0; i < DistributionReproducer::Distribution::CountD; i++) {
			distributionComboBox->insertItem(i, DistributionReproducer::distributionName[i]);
		}

		distributionComboBox->setCurrentIndex(ve->vector->rep.model);

		connect(this->distributionComboBox, &QComboBox::currentIndexChanged,
				this, &DistributionReproducerDialog::distribute);

		QGridLayout* distributionLayout = new QGridLayout;
		distributionLayout->addWidget(new QLabel("Відтворюваний розподіл: "), 0, 0);
		distributionLayout->addWidget(distributionComboBox, 0, 1);

		tablesWidget = new QWidget;
		tablesLayout = new QVBoxLayout();
		tablesLayout->setContentsMargins(0,0,0,0);
		tablesWidget->setLayout(tablesLayout);
		parameterTable = new QTableWidget();
		deviationTable = new QTableWidget();
		functionTable = new QTableWidget();
		functionDeviationTable = new QTableWidget();

		QGroupBox* groupBox;
		QVBoxLayout* boxLay;

		groupBox = new QGroupBox("Параметри");
		boxLay = new QVBoxLayout();
		groupBox->setLayout(boxLay);
		boxLay->setContentsMargins(0,0,0,0);
		boxLay->addWidget(parameterTable);
		tablesLayout->addWidget(groupBox);

		groupBox = new QGroupBox("Відхилення");
		boxLay = new QVBoxLayout();
		boxLay->setContentsMargins(0,0,0,0);
		groupBox->setLayout(boxLay);
		boxLay->addWidget(deviationTable);
		tablesLayout->addWidget(groupBox);

		groupBox = new QGroupBox("Функції");
		boxLay = new QVBoxLayout();
		boxLay->setContentsMargins(0,0,0,0);
		groupBox->setLayout(boxLay);
		boxLay->addWidget(functionTable);
		boxLay->addWidget(functionDeviationTable);
		tablesLayout->addWidget(groupBox);

		parameterTable->setColumnCount(2);
		parameterTable->setFixedHeight(85);
		parameterTable->verticalHeader()->setVisible(false);
		parameterTable->setHorizontalHeaderLabels({"Назва", "Значення"});

		deviationTable->setColumnCount(2);
		deviationTable->setFixedHeight(120);
		deviationTable->verticalHeader()->setVisible(false);
		deviationTable->setHorizontalHeaderLabels({"Назва", "Значення"});

		functionTable->setColumnCount(2);
		functionTable->setFixedHeight(100);
		functionTable->verticalHeader()->setVisible(false);
		functionTable->setHorizontalHeaderLabels({"Назва", "Значення"});

		functionDeviationTable->setColumnCount(501);
		functionDeviationTable->setRowCount(1);
		functionDeviationTable->setFixedHeight(80);
		functionDeviationTable->verticalHeader()->setVisible(false);

		mainLayout->addLayout(distributionLayout);
		mainLayout->addWidget(tablesWidget);

		groupBox = new QGroupBox("Оцінки згоди відтворення");
		boxLay = new QVBoxLayout();
		boxLay->setContentsMargins(0,0,0,0);
		groupBox->setLayout(boxLay);

		QGridLayout* probLayout = new QGridLayout;

		consentsProbabilitySpinBox = new QDoubleSpinBox();
		consentsProbabilitySpinBox->setDecimals(3);
		consentsProbabilitySpinBox->setRange(0.001, 1);
		consentsProbabilitySpinBox->setValue(0.95);
		consentsProbabilitySpinBox->setSingleStep(0.05);

		probLayout->addWidget(new QLabel("Критичний рівень значущості"), 0, 0);
		probLayout->addWidget(consentsProbabilitySpinBox, 0, 1);
		consentTextEdit = new QTextEdit;
		consentTextEdit->setMaximumHeight(100);

		tablesLayout->addWidget(groupBox);

		boxLay->addLayout(probLayout);
		boxLay->addWidget(consentTextEdit);

		connect(consentsProbabilitySpinBox, &QDoubleSpinBox::valueChanged,
				this, &DistributionReproducerDialog::makeConsents);

		distribute(DistributionReproducer::Distribution(distributionComboBox->currentIndex()));

		this->adjustSize();
		this->show();
}

void DistributionReproducerDialog::distribute(int dist) {
	ve->vector->reproduceDistribution(DistributionReproducer::Distribution(dist));

	if (dist != DistributionReproducer::Distribution::UnknownD) {
		refill();
		tablesWidget->setVisible(true);
		this->adjustSize();
		this->resize(750, this->height());
	} else {
		tablesWidget->setVisible(false);
		this->adjustSize();
	}

	emit distributionSelected(ve);
}

void DistributionReproducerDialog::refill() {
	parameterTable->setRowCount(ve->vector->rep.parametersCount);
	parameterTable->setColumnWidth(0, 55);
	parameterTable->setColumnWidth(1, 200);
	deviationTable->setRowCount(ve->vector->rep.parametersCount);
	deviationTable->setColumnWidth(0, 100);
	deviationTable->setColumnWidth(1, 200);
	functionTable->setRowCount(2);
	functionTable->setColumnWidth(0, 55);
	functionTable->setColumnWidth(1, 600);
	functionDeviationTable->setColumnWidth(0, 55);

	for (int i = 0; i < ve->vector->rep.parametersCount; i++) {
		parameterTable->setItem(i, 0, new QTableWidgetItem(
					ve->vector->rep.paremeterNames[i])
				);
		parameterTable->setItem(i, 1, new QTableWidgetItem(
					QString::number(ve->vector->rep.parameters[i], 'f', precision))
				);
		deviationTable->setItem(i, 0, new QTableWidgetItem(
					"D{" + ve->vector->rep.parametersDeviationNames[i] + "}")
				);
		deviationTable->setItem(i, 1, new QTableWidgetItem(
					QString::number(ve->vector->rep.parametersDeviation[i], 'f', precision))
				);
	}

	if (ve->vector->rep.parametersCount == 2) {
		deviationTable->insertRow(2);
		deviationTable->setItem(2, 0, new QTableWidgetItem(
					"cov{" + ve->vector->rep.paremeterNames[0] + "," +
					ve->vector->rep.paremeterNames[1] + "}")
				);
		deviationTable->setItem(2, 1, new QTableWidgetItem(
					QString::number(ve->vector->rep.parametersCv, 'f', precision))
				);
	}

	functionTable->setItem(0, 0, new QTableWidgetItem(
				"f(x)"));
	functionTable->setItem(0, 1, new QTableWidgetItem(
				ve->vector->rep.pdfString));
	functionTable->setItem(1, 0, new QTableWidgetItem(
				"F(x)"));
	functionTable->setItem(1, 1, new QTableWidgetItem(
				ve->vector->rep.cdfString));

	QStringList headers = {" "};
	QList<double> dispersions;

	double step, a, b;
	if (ve->vector->rep.domain.first == ve->vector->rep.domain.second) {
		a = ve->vector->min();
		b = ve->vector->max();
		step = abs(a-b)/500;
	} else {
		a = ve->vector->rep.domain.first;
		b = ve->vector->rep.domain.second;
		step = abs(a-b)/500;
	}

	for (double x = a + 0.01;
			x <= b;
			x += step) {
		dispersions.append(ve->vector->rep.cdfDev(x));
		headers.append("x = " + QString::number(x, 'f', precision));
	}
	functionDeviationTable->setHorizontalHeaderLabels(headers);
		functionDeviationTable->setItem(0, 0, new QTableWidgetItem(
					"D{F(x)}")
				);
	for (int i = 1; i < dispersions.length()+1; i++) {
		functionDeviationTable->setItem(0, i, new QTableWidgetItem(
                    QString::number(dispersions[i-1], 'f', precision + 1))
				);
		functionDeviationTable->setColumnWidth(i, 200);
	}

	makeConsents();
}

void DistributionReproducerDialog::makeConsents() {
	double prob = consentsProbabilitySpinBox->value();
	QString kolm = QString(
				"Уточнений критерій згоди колмогорова: 1 - %1 ≤ %2\n")
			.arg(ve->vector->kolmConsentCriterion(), 3, 'f', precision)
			.arg(prob);
	if (1 - ve->vector->kolmConsentCriterion() <= prob)
		kolm.append("Головна гіпотеза виконується (функції збігаються)");
	else
		kolm.append("Головна гіпотеза не виконується (функції не збігаються)");

	QString pear = QString("Критерій згоди Пірсона: ");
	if (ve->vector->classSeries() != nullptr) {
			double quantile = Statistics::pearQuantile(1-prob,
							ve->vector->classSeries()->classCount()-1);
			double crit = ve->vector->pearConsentCriterion();
			pear.append(QString("%1 ≤ pearQuantile(1-%2, %3) = %4\n")
					.arg(crit)
					.arg(prob)
					.arg(ve->vector->classSeries()->classCount()-1)
					.arg(quantile,
						3, 'f', precision)
					);
			if (crit <= quantile)
				pear.append("Головна гіпотеза виконується (функції збігаються)");
			else
				pear.append("Головна гіпотеза не виконується (функції не збігаються)");
	} else 
		pear.append("вектор не був розбитий на класи");
	
	consentTextEdit->setText(kolm + "\n\n" + pear);
}

void DistributionReproducerDialog::vectorDeletedHandler(VectorEntry* vectorEntry) {
	if (ve == vectorEntry)
		this->close();
}
