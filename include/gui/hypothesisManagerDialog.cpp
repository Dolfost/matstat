#include "hypothesisManagerDialog.hpp"
#include <QGroupBox>
#include <QtCore/qstring.h>
#include <cstdlib>

HypothesisManagerDialog::HypothesisManagerDialog(
		QList<VectorEntry*> v,
		DataVectorSet::Procedure proc,
		QWidget* parent,
		Qt::WindowFlags flags
		) : QDialog(parent, flags) {
	vectors = v;

	for (auto const& vec : vectors) {
		vectorSet.push_back(vec->vector);
	}

	this->setWindowTitle("Менеджер гіпотез");
	mainLayout = new QVBoxLayout;
	mainLayout->setContentsMargins(0,0,0,0);
	this->setLayout(mainLayout);
	QVBoxLayout* secondaryLayout = new QVBoxLayout;
	secondaryLayout->setContentsMargins(5,5,5,5);

	QGroupBox* procedureGroupBox = new QGroupBox("Процедура:");
	procedureGroupBox->setLayout(new QHBoxLayout);
	procedureGroupBox->layout()->setContentsMargins(1,1,1,1);
	procedureComboBox = new QComboBox();
	for (int i = DataVectorSet::Procedure::tTestDependentP; i < DataVectorSet::Procedure::Count; i++) {
		procedureComboBox->addItem(DataVectorSet::procedureName[i]);
	}
	procedureGroupBox->layout()->addWidget(procedureComboBox);

	QGroupBox* vectorsGroupBox = new QGroupBox("Вектори:");
	vectorsGroupBox->setLayout(new QHBoxLayout);
	vectorsGroupBox->layout()->setContentsMargins(1,1,1,1);
	vectorsLineEdit = new QLineEdit;
	vectorsLineEdit->setReadOnly(true);
	vectorsGroupBox->layout()->addWidget(vectorsLineEdit);
	makeVectorList();

	levelSpinBox = new QDoubleSpinBox;
	levelSpinBox->setRange(0.001, 0.999);
	levelSpinBox->setDecimals(3);
	levelSpinBox->setSingleStep(0.05);
	levelSpinBox->setValue(0.95);
	QGridLayout* spinBoxLayout = new QGridLayout;
	spinBoxLayout->addWidget(new QLabel("Критичний рівень значущості:"), 0, 0);
	spinBoxLayout->addWidget(levelSpinBox, 0, 1);

	resTextEdit = new QTextEdit;
	resTextEdit->setReadOnly(true);

	secondaryLayout->addWidget(procedureGroupBox);
	secondaryLayout->addWidget(vectorsGroupBox);
	secondaryLayout->addLayout(spinBoxLayout);
	mainLayout->addLayout(secondaryLayout);
	mainLayout->addWidget(resTextEdit);

	connect(levelSpinBox, &QDoubleSpinBox::valueChanged,
			this, &HypothesisManagerDialog::compute);
	connect(procedureComboBox, &QComboBox::currentTextChanged,
			this, &HypothesisManagerDialog::compute);

	procedureComboBox->setCurrentIndex(proc);

	this->compute();
	this->show();
}

void HypothesisManagerDialog::compute() {
	QString res, cond, implies;
	bool accepted = false;
	double critLevel = levelSpinBox->value();
	double criteria;
	double quantile;

	try {
		switch (procedureComboBox->currentIndex()) {
			case DataVectorSet::Procedure::tTestDependentP:
				{
					criteria = vectorSet.tTestDependent();
					quantile = Statistics::studQuantile(1-critLevel/2, vectorSet[0]->size()-2);
					cond = QString("|%1| < t(%2,%3) = %4")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel/2, 3, 'f')
						.arg(vectorSet[0]->size()-2)
						.arg(quantile, 3, 'f');
					accepted = std::abs(criteria) < quantile;
					implies = accepted ? "середні збігаються" : "середні не збігаються";
					break;
				}
			case DataVectorSet::Procedure::tTestIndependentP:
				{
					criteria = vectorSet.tTestIndependent();
					quantile = Statistics::studQuantile(1-critLevel/2,
							vectorSet[0]->size() + vectorSet[1]->size() - 2);
					cond = QString("%1 < t(%2,%3) = %4")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel/2, 3, 'f')
						.arg(vectorSet[0]->size() + vectorSet[1]->size() - 2)
						.arg(quantile, 3, 'f');
					accepted = criteria < quantile;
					implies = accepted ? "середні збігаються" : "середні не збігаються";
					break;
				}
			case DataVectorSet::Procedure::fTestP:
				{
					criteria = vectorSet.fTest();
					quantile = Statistics::fishQuantile(1-critLevel,
							vectorSet[0]->size()-1, vectorSet[1]->size() - 1);
					cond = QString("|%1| < f(%2,%3,%4) = %5")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel, 3, 'f')
						.arg(vectorSet[0]->size() - 1)
						.arg(vectorSet[1]->size() - 1)
						.arg(quantile, 3, 'f');
					accepted = std::abs(criteria) < quantile;
					implies = accepted ? "дисперсії збігаються" : "дисперсії не збігаються";
					break;
				}
			case DataVectorSet::Procedure::fTestBartlettP:
				{
					criteria = vectorSet.fTestBartlett();
					quantile = Statistics::pearQuantile(1-critLevel,
							vectorSet.size()-1);
					cond = QString("%1 < 𝜒(%2,%3) = %4")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel, 3, 'f')
						.arg(vectorSet.size() - 1)
						.arg(quantile, 3, 'f');
					accepted = criteria < quantile;
					implies = accepted ? "дисперсії збігаються" : "дисперсії не збігаються";
					break;
				}
			case DataVectorSet::Procedure::oneWayANOVAP:
				{
					criteria = vectorSet.oneWayANOVA();
					double v1 = vectorSet.size() - 1,
						   v2 = vectorSet.overallSize() - vectorSet.size();
					quantile = Statistics::fishQuantile(1-critLevel,
							v1, v2);
					cond = QString("%1 < f(%2,%3,%4) = %5")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel, 3, 'f')
						.arg(v1)
						.arg(v2)
						.arg(quantile, 3, 'f');
					accepted = criteria < quantile;
					implies = accepted ? "середні збігаються" : "середні не збігаються";
					break;
				}
			case DataVectorSet::Procedure::testKSP:
				{
					criteria = 1 - vectorSet.testKS();
					quantile = critLevel;
					cond = QString("%1 < %2")
						.arg(criteria, 3, 'f')
						.arg(critLevel, 3, 'f');
					accepted = criteria > quantile;
					implies = accepted ? "вибірки однорідні" : "вибірки не однорідні";
					break;
				}
			case DataVectorSet::Procedure::testWilcoxonP:
				{
					criteria = vectorSet.testWilcoxon();
					quantile = Statistics::normQuantile(1-critLevel/2);
					cond = QString("%1 < u(%2) = %3")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel/2, 3, 'f')
						.arg(quantile, 3, 'f');
					accepted = criteria < quantile;
					implies = accepted ? "вибірки однорідні" : "вибірки не однорідні";
					break;
				}
			case DataVectorSet::Procedure::criteriaUP:
				{
					criteria = vectorSet.criteriaU();
					quantile = Statistics::normQuantile(1-critLevel/2);
					cond = QString("%1 < u(%2) = %3")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel/2, 3, 'f')
						.arg(quantile, 3, 'f');
					accepted = criteria < quantile;
					implies = accepted ? "вибірки однорідні" : "вибірки не однорідні";
					break;
				}
		}
	} catch (const char* msg) {
		resTextEdit->setText("Помилка: " + QString(msg));
		return;
	}

	res = QString("Умова: %1\n")
		.arg(cond);

	if (accepted)
		res.append(QString("Головна гіпотеза прийнята — %1")
			.arg(implies));
	else
		res.append(QString("Головна гіпотеза відхилена — %1")
			.arg(implies));

	resTextEdit->setText(res);
}

void HypothesisManagerDialog::makeVectorList() {
	QString vecs;
	for (auto const& v : vectors) {
		vecs.append(v->name + ", ");
	}
	vecs.chop(2);

	vectorsLineEdit->setText(vecs);
};

void HypothesisManagerDialog::vectorDeletedHandler(VectorEntry* vec) {
	if (vectors.removeAll(vec)) {
		makeVectorList();
		compute();
	}

	vectorSet.erase(std::remove_if(vectorSet.begin(), 
                              vectorSet.end(),
                              [=](DataVector* x) { return x == vec->vector; }),
               vectorSet.end());

	if (!vectors.size())
		this->close();
}
