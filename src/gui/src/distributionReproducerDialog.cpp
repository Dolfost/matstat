#include "distributionReproducerDialog.hpp"
#include "vector/quantile.hpp"
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qtablewidget.h>
#include <vector>

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
		for (int i = 0; i < (int)ss::Vector::Distribution::Model::Count; i++) {
			distributionComboBox->insertItem(i, QString::fromStdString(ss::Vector::Distribution::distributionName[i]));
		}

		distributionComboBox->setCurrentIndex((int)ve->vector->dist.model);

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

		groupBox = new QGroupBox("Перевірка рівності параматрів і оцінок");
		boxLay = new QVBoxLayout();
		QVBoxLayout* tableLay = new QVBoxLayout();
		tableLay->setContentsMargins(0,0,0,0);
		boxLay->setContentsMargins(0,0,0,0);
		groupBox->setLayout(boxLay);

		ttestTable = new QTableWidget();
		ttestTable->setMaximumHeight(120);
		tableLay->addWidget(ttestTable);

		ttestWidget = new QStackedWidget();
		ttestWidget->addWidget(new QWidget);
		ttestWidget->addWidget(new QWidget);
		ttestWidget->addWidget(new QWidget);
		ttestWidget->widget(0)->setLayout(tableLay);
		ttestWidget->widget(1)->setLayout(new QVBoxLayout);
		ttestWidget->widget(1)->layout()->addWidget(
			new QLabel("Вибірка не була змодельована в програмі")
		);
		ttestWidget->widget(2)->setLayout(new QVBoxLayout);
		ttestWidget->widget(2)->layout()->addWidget(
			new QLabel("Розподіл за яким генерували вибірку і відтворюваний розподіл не зходяться")
		);
		boxLay->addWidget(ttestWidget);

		tablesLayout->addWidget(groupBox);

		connect(consentsProbabilitySpinBox, &QDoubleSpinBox::valueChanged,
				this, &DistributionReproducerDialog::makeConsents);

		distribute(distributionComboBox->currentIndex());

		this->adjustSize();
		this->show();
}

void DistributionReproducerDialog::distribute(int dist) {
	ve->vector->reproduceDistribution(ss::Vector::Distribution::Model(dist));

	if (dist != (int)ss::Vector::Distribution::Model::Unknown) {
		refill();
		makeTtest();
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
	parameterTable->setRowCount(ve->vector->dist.parametersCount);
	parameterTable->setColumnWidth(0, 55);
	parameterTable->setColumnWidth(1, 200);
	deviationTable->setRowCount(ve->vector->dist.parametersCount);
	deviationTable->setColumnWidth(0, 100);
	deviationTable->setColumnWidth(1, 200);
	functionDeviationTable->setColumnWidth(0, 55);

	for (int i = 0; i < ve->vector->dist.parametersCount; i++) {
		parameterTable->setItem(i, 0, new QTableWidgetItem(
					QString::fromStdString(ve->vector->dist.paremeterNames[i]))
				);
		parameterTable->setItem(i, 1, new QTableWidgetItem(
					QString::number(ve->vector->dist.parameters[i], 'f', precision))
				);
		deviationTable->setItem(i, 0, new QTableWidgetItem(
					"D{" + QString::fromStdString(ve->vector->dist.parametersDeviationNames[i]) + "}")
				);
		deviationTable->setItem(i, 1, new QTableWidgetItem(
					QString::number(ve->vector->dist.parametersDeviation[i], 'f', precision))
				);
	}

	if (ve->vector->dist.parametersCount == 2) {
		deviationTable->insertRow(2);
		deviationTable->setItem(2, 0, new QTableWidgetItem(
					"cov{" + QString::fromStdString(ve->vector->dist.paremeterNames[0]) + "," +
					QString::fromStdString(ve->vector->dist.paremeterNames[1]) + "}")
				);
		deviationTable->setItem(2, 1, new QTableWidgetItem(
					QString::number(ve->vector->dist.parametersCv, 'f', precision))
				);
	}

	QStringList headers = {" "};
	QList<double> dispersions;

	double step, a, b;
	if (ve->vector->dist.domain.first == ve->vector->dist.domain.second) {
		a = ve->vector->min();
		b = ve->vector->max();
		step = abs(a-b)/500;
	} else {
		a = ve->vector->dist.domain.first;
		b = ve->vector->dist.domain.second;
		step = abs(a-b)/500;
	}

	for (double x = a + 0.01;
			x <= b;
			x += step) {
		dispersions.append(ve->vector->dist.cdfDev(x));
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
	double quantile = ss::pearQuantile(1-prob,
																		ve->vector->cs.count()-1);
	double crit = ve->vector->pearConsentCriterion();
	pear.append(QString("%1 ≤ pearQuantile(1-%2, %3) = %4\n")
						 .arg(crit)
						 .arg(prob)
						 .arg(ve->vector->cs.count()-1)
						 .arg(quantile,
						3, 'f', precision)
						 );
	if (crit <= quantile)
		pear.append("Головна гіпотеза виконується (функції збігаються)");
	else
		pear.append("Головна гіпотеза не виконується (функції не збігаються)");
	
	consentTextEdit->setText(kolm + "\n\n" + pear);
}

void DistributionReproducerDialog::makeTtest() {
	if (ve->isModeled) {
		ttestWidget->setCurrentIndex(0);
		ss::Vector::Distribution& rep = (ve->vector->dist);

		if (ve->modelDistribution != rep.model) {
			ttestWidget->setCurrentIndex(2);
			return;
		}

		std::vector<double> probs = {
			0.01, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5,
			0.6, 0.7, 0.8, 0.9, 0.95, 0.96, 0.97, 0.98, 0.99};
		std::vector<double> t;

		ttestTable->setRowCount(rep.parameters.size());
		ttestTable->setColumnCount(1 + probs.size());

		QStringList vHeader, hHeader;
		for (int i = 0; i < rep.parameters.size(); i++) {
			vHeader.push_back(QString::fromStdString(rep.paremeterNames[i]));
			t.push_back((ve->modelParameters[i]-rep.parameters[i]) / 
				std::sqrt(rep.parametersDeviation[i]));
			ttestTable->setItem(i, 0, new QTableWidgetItem(
						QString::number(t[i], 'f', 3)));
			for (int j = 1; j < probs.size()+1; j++) {
			ttestTable->setItem(i, j, new QTableWidgetItem(
				std::abs(t[i]) <= 
				ss::studQuantile(1-probs[j-1]/2, ve->vector->size()) 
				? "+" : "-"));
			}
		}
		hHeader.append("t");

		for (int i = 0; i < probs.size(); i++) {
			hHeader.append(QString::number(probs[i]));
		}

		ttestTable->setHorizontalHeaderLabels(hHeader);
		ttestTable->setVerticalHeaderLabels(vHeader);

		ttestTable->setColumnWidth(0, 60);
		for (int i = 0; i < probs.size(); i++) {
			ttestTable->setColumnWidth(i+1, 35);
		}
	} else {
		ttestWidget->setCurrentIndex(1);
	}
}

void DistributionReproducerDialog::vectorDeletedHandler(VectorEntry* vectorEntry) {
	if (ve == vectorEntry)
		this->close();
}
