#include "distributionReproducerDialog.hpp"
#include "gui/Section.h"
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qtablewidget.h>
#include <random>

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

		distributionComboBox->setCurrentIndex(ve->vector->reproduction.model);

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
		deviationTable->setFixedHeight(85);
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
}

void DistributionReproducerDialog::refill() {
	parameterTable->setRowCount(ve->vector->reproduction.parametersCount);
	parameterTable->setColumnWidth(0, 55);
	parameterTable->setColumnWidth(1, 200);
	deviationTable->setRowCount(ve->vector->reproduction.parametersCount);
	deviationTable->setColumnWidth(0, 55);
	deviationTable->setColumnWidth(1, 200);
	functionTable->setRowCount(2);
	functionTable->setColumnWidth(0, 55);
	functionTable->setColumnWidth(1, 600);
	functionDeviationTable->setColumnWidth(0, 55);

	for (int i = 0; i < ve->vector->reproduction.parametersCount; i++) {
		parameterTable->setItem(i, 0, new QTableWidgetItem(
					ve->vector->reproduction.paremeterNames[i])
				);
		parameterTable->setItem(i, 1, new QTableWidgetItem(
					QString::number(ve->vector->reproduction.parameters[i], 'f', precision))
				);
		deviationTable->setItem(i, 0, new QTableWidgetItem(
					"D{" + ve->vector->reproduction.parametersDeviationNames[i] + "}")
				);
		deviationTable->setItem(i, 1, new QTableWidgetItem(
					QString::number(ve->vector->reproduction.parametersDeviation[i], 'f', precision))
				);
	}

	functionTable->setItem(0, 0, new QTableWidgetItem(
				"f(x)"));
	functionTable->setItem(0, 1, new QTableWidgetItem(
				ve->vector->reproduction.pdfString));
	functionTable->setItem(1, 0, new QTableWidgetItem(
				"F(x)"));
	functionTable->setItem(1, 1, new QTableWidgetItem(
				ve->vector->reproduction.cdfString));

	QStringList headers = {" "};
	QList<double> dispersions;

	double step = abs(ve->vector->max() - ve->vector->min())/500;
	for (ve->vector->reproduction.x = ve->vector->min();
			ve->vector->reproduction.x <= ve->vector->max();
			ve->vector->reproduction.x += step) {
		dispersions.append(ve->vector->reproduction.cdfDeviationExpression.value());
		headers.append("x = " + QString::number(ve->vector->reproduction.x, 'f', precision));
	}
	functionDeviationTable->setHorizontalHeaderLabels(headers);
		functionDeviationTable->setItem(0, 0, new QTableWidgetItem(
					"D{F(x)}")
				);
	for (int i = 1; i < dispersions.length()+1; i++) {
		functionDeviationTable->setItem(0, i, new QTableWidgetItem(
					QString::number(dispersions[i], 'f', precision + 4))
				);
		functionDeviationTable->setColumnWidth(i, 100);
	}
}

void DistributionReproducerDialog::vectorDeletedHandler(VectorEntry* vectorEntry) {
	if (ve == vectorEntry)
		this->close();
}
