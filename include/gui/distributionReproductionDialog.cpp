#include "distributionReproductionDialog.hpp"
#include "gui/Section.h"
#include <QtWidgets/qlabel.h>

DistributionReproductionDialog::DistributionReproductionDialog(
		VectorEntry* vectorEntry,
		QWidget *parent, Qt::WindowFlags f) 
	: QDialog(parent, f) {
		ve = vectorEntry;

		this->setWindowTitle("Інформація про відтворення розподілу " + ve->name);
		this->setAttribute(Qt::WA_DeleteOnClose, true);
		QVBoxLayout* mainLayout = new QVBoxLayout();
		this->setLayout(mainLayout);
		// mainLayout->setSpacing(0);

		distributionComboBox = new QComboBox();
		for (int i = 0; i < DataVector::Distribution::CountD; i++) {
			distributionComboBox->insertItem(i, DataVector::distributionName[i]);
		}

		distributionComboBox->setCurrentIndex(ve->vector->distribution());

		connect(this->distributionComboBox, &QComboBox::currentIndexChanged,
				this, &DistributionReproductionDialog::distribute);

		QGridLayout* distributionLayout = new QGridLayout;
		distributionLayout->addWidget(new QLabel("Відтворюваний розподіл: "), 0, 0);
		distributionLayout->addWidget(distributionComboBox, 0, 1);


		tablesWidget = new QWidget;
		tablesLayout = new QVBoxLayout();
		tablesWidget->setLayout(tablesLayout);
		parameterTable = new QTableWidget();
		dispersionTable = new QTableWidget();
		functionTable = new QTableWidget();

		QGroupBox* groupBox;
		QVBoxLayout* boxLay;

		groupBox = new QGroupBox("Параметри");
		boxLay = new QVBoxLayout();
		groupBox->setLayout(boxLay);
		boxLay->addWidget(parameterTable);
		tablesLayout->addWidget(groupBox);

		groupBox = new QGroupBox("Відхилення");
		boxLay = new QVBoxLayout();
		groupBox->setLayout(boxLay);
		boxLay->addWidget(dispersionTable);
		tablesLayout->addWidget(groupBox);

		groupBox = new QGroupBox("Функції");
		boxLay = new QVBoxLayout();
		groupBox->setLayout(boxLay);
		boxLay->addWidget(functionTable);
		tablesLayout->addWidget(groupBox);

		parameterTable->setColumnCount(2);
		parameterTable->verticalHeader()->setVisible(false);
		parameterTable->setHorizontalHeaderLabels({"Назва", "Значення"});

		dispersionTable->setColumnCount(2);
		dispersionTable->verticalHeader()->setVisible(false);
		dispersionTable->setHorizontalHeaderLabels({"Назва", "Значення"});

		functionTable->setColumnCount(2);
		functionTable->verticalHeader()->setVisible(false);
		functionTable->setHorizontalHeaderLabels({"Назва", "Значення"});

		mainLayout->addLayout(distributionLayout);
		mainLayout->addWidget(tablesWidget);

		distribute(DataVector::Distribution(distributionComboBox->currentIndex()));

		this->resize(500, 350);
		this->show();
}

void DistributionReproductionDialog::distribute(int dist) {
	ve->vector->setDistribution(DataVector::Distribution(dist));

	if (dist != DataVector::Distribution::UnknownD) {
		tablesWidget->setVisible(true);
		refill();
	} else {
		tablesWidget->setVisible(false);
	}
}

void DistributionReproductionDialog::refill() {

}

void DistributionReproductionDialog::vectorDeletedHandler(VectorEntry* vectorEntry) {
	if (ve == vectorEntry)
		this->close();
}
