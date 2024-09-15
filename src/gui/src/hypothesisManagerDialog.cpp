#include "hypothesisManagerDialog.hpp"
#include "vector/quantile.hpp"
#include <QGroupBox>
#include <QtCore/qstring.h>
#include <cstdlib>
#include <functional>

VectorHypothesisDialog::VectorHypothesisDialog(
		QList<Vector*> v,
		ss::VectorChain::Procedure proc,
		QWidget* parent,
		Qt::WindowFlags flags
		) : QDialog(parent, flags) {
	vectors = v;

	for (auto const& vec : vectors) {
		vectorSet.push_back(vec->vector());
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
	for (int i = ss::VectorChain::Procedure::tTestDependentP; i < ss::VectorChain::Procedure::Count; i++) {
		procedureComboBox->addItem(QString::fromStdString(ss::VectorChain::procedureName[i]));
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
	resTextEdit->setMaximumHeight(90);

	pmTable = new QTableWidget;
	pmTable->setMaximumHeight(80);

	secondaryLayout->addWidget(procedureGroupBox);
	secondaryLayout->addWidget(vectorsGroupBox);
	secondaryLayout->addLayout(spinBoxLayout);
	mainLayout->addLayout(secondaryLayout);
	mainLayout->addWidget(resTextEdit);
	mainLayout->addWidget(pmTable);

	connect(levelSpinBox, &QDoubleSpinBox::valueChanged,
			this, &VectorHypothesisDialog::compute);
	connect(procedureComboBox, &QComboBox::currentTextChanged,
			this, &VectorHypothesisDialog::compute);

	procedureComboBox->setCurrentIndex(proc);

	this->compute();
	this->resize(645, this->height());
	this->show();
}

void VectorHypothesisDialog::compute() {
	QString res, cond, implies;
	bool accepted = false;
	double critLevel = levelSpinBox->value();
	double criteria;
	double quantile;
	std::function<bool(double)> qf;

	try {
		switch (procedureComboBox->currentIndex()) {
			case ss::VectorChain::Procedure::tTestDependentP:
				{
					criteria = vectorSet.tTestDependent();
					quantile = ss::studQuantile(1-critLevel/2, vectorSet[0]->size()-2);
					cond = QString("|%1| < t(%2,%3) = %4")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel/2, 3, 'f')
						.arg(vectorSet[0]->size()-2)
						.arg(quantile, 3, 'f');
					accepted = std::abs(criteria) <= quantile;
					implies = accepted ? "середні збігаються" : "середні не збігаються";
					qf = [=](double a) { 
						return std::abs(criteria) <= ss::studQuantile(1-a/2, vectorSet[0]->size()-2); 
					};
					break;
				}
			case ss::VectorChain::Procedure::tTestIndependentP:
				{
					criteria = vectorSet.tTestIndependent();
					quantile = ss::studQuantile(1-critLevel/2,
							vectorSet[0]->size() + vectorSet[1]->size() - 2);
					cond = QString("%1 < t(%2,%3) = %4")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel/2, 3, 'f')
						.arg(vectorSet[0]->size() + vectorSet[1]->size() - 2)
						.arg(quantile, 3, 'f');
					accepted = criteria <= quantile;
					implies = accepted ? "середні збігаються" : "середні не збігаються";
					qf = [=](double a) { 
						return criteria <= ss::studQuantile(1-a/2,
							vectorSet[0]->size() + vectorSet[1]->size() - 2);
					};
					break;
				}
			case ss::VectorChain::Procedure::fTestP:
				{
					criteria = vectorSet.fTest();
					quantile = ss::fishQuantile(1-critLevel,
							vectorSet[0]->size()-1, vectorSet[1]->size() - 1);
					cond = QString("|%1| < f(%2,%3,%4) = %5")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel, 3, 'f')
						.arg(vectorSet[0]->size() - 1)
						.arg(vectorSet[1]->size() - 1)
						.arg(quantile, 3, 'f');
					accepted = std::abs(criteria) <= quantile;
					implies = accepted ? "дисперсії збігаються" : "дисперсії не збігаються";
					qf = [=](double a) { 
						return std::abs(criteria) <= ss::fishQuantile(1-a,
							vectorSet[0]->size()-1, vectorSet[1]->size() - 1);
					};
					break;
				}
			case ss::VectorChain::Procedure::fTestBartlettP:
				{
					criteria = vectorSet.fTestBartlett();
					quantile = ss::pearQuantile(1-critLevel,
							vectorSet.size()-1);
					cond = QString("%1 < 𝜒(%2,%3) = %4")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel, 3, 'f')
						.arg(vectorSet.size() - 1)
						.arg(quantile, 3, 'f');
					accepted = criteria <= quantile;
					implies = accepted ? "дисперсії збігаються" : "дисперсії не збігаються";
					qf = [=](double a) { 
						return criteria <= ss::pearQuantile(1-a,
							vectorSet.size()-1);
					};
					break;
				}
			case ss::VectorChain::Procedure::oneWayANOVAP:
				{
					criteria = vectorSet.oneWayANOVA();
					double v1 = vectorSet.size() - 1,
						   v2 = vectorSet.overallSize() - vectorSet.size();
					quantile = ss::fishQuantile(1-critLevel,
							v1, v2);
					cond = QString("%1 < f(%2,%3,%4) = %5")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel, 3, 'f')
						.arg(v1)
						.arg(v2)
						.arg(quantile, 3, 'f');
					accepted = criteria <= quantile;
					implies = accepted ? "середні збігаються" : "середні не збігаються";
					qf = [=](double a) { 
						return criteria <= ss::fishQuantile(1-a,
							v1, v2);
					};
					break;
				}
			case ss::VectorChain::Procedure::testKSP:
				{
					criteria = 1 - vectorSet.testKS();
					quantile = critLevel;
					cond = QString("%1 < %2")
						.arg(criteria, 3, 'f')
						.arg(critLevel, 3, 'f');
					accepted = criteria >= quantile;
					implies = accepted ? "вибірки однорідні" : "вибірки не однорідні";
					qf = [=](double a) { 
						return criteria >= a;
					};
					break;
				}
			case ss::VectorChain::Procedure::testWilcoxonP:
				{
					criteria = vectorSet.testWilcoxon();
					quantile = ss::normQuantile(1-critLevel/2);
					cond = QString("%1 < u(%2) = %3")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel/2, 3, 'f')
						.arg(quantile, 3, 'f');
					accepted = criteria <= quantile;
					implies = accepted ? "вибірки однорідні" : "вибірки не однорідні";
					qf = [=](double a) { 
						return criteria <= ss::normQuantile(1-a/2);
					};
					break;
				}
			case ss::VectorChain::Procedure::criteriaUP:
				{
					criteria = vectorSet.criteriaU();
					quantile = ss::normQuantile(1-critLevel/2);
					cond = QString("%1 < u(%2) = %3")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel/2, 3, 'f')
						.arg(quantile, 3, 'f');
					accepted = criteria <= quantile;
					implies = accepted ? "вибірки однорідні" : "вибірки не однорідні";
					qf = [=](double a) { 
						return criteria <= ss::normQuantile(1-a/2);
					};
					break;
				}
			case ss::VectorChain::Procedure::rankAveragesDifferenceP:
				{
					criteria = vectorSet.rankAveragesDifference();
					quantile = ss::normQuantile(1-critLevel/2);
					cond = QString("|%1| < u(%2) = %3")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel/2, 3, 'f')
						.arg(quantile, 3, 'f');
					accepted = std::abs(criteria) <= quantile;
					implies = accepted ? "вибірки однорідні" : "вибірки не однорідні";
					qf = [=](double a) { 
						return std::abs(criteria) <= ss::normQuantile(1-a/2);
					};
					break;
				}
			case ss::VectorChain::Procedure::hTestP:
				{
					criteria = vectorSet.hTest();
					quantile = ss::pearQuantile(1-critLevel, vectorSet.size()-1);
					cond = QString("%1 < 𝜒(%2,%3) = %4")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel, 3, 'f')
						.arg(vectorSet.size()-1)
						.arg(quantile, 3, 'f');
					accepted = criteria <= quantile;
					implies = accepted ? "вибірки однорідні" : "вибірки не однорідні";
					qf = [=](double a) { 
						return criteria <= ss::pearQuantile(1-a, vectorSet.size()-1);
					};
					break;
				}
			case ss::VectorChain::Procedure::signTestP:
				{
					criteria = vectorSet.signTest();
					quantile = ss::normQuantile(1-critLevel);
					cond = QString("%1 < u(%2) = %3")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel, 3, 'f')
						.arg(quantile, 3, 'f');
					accepted = criteria < quantile;
					implies = accepted ? "вибірки однорідні" : 
						"вибірки не однорідні (F(x) < G(y))";
					qf = [=](double a) { 
						return criteria < ss::normQuantile(1-a);
					};
					break;
				}
			case ss::VectorChain::Procedure::qTestP:
				{
					criteria = vectorSet.qTest();
					quantile = ss::pearQuantile(1-critLevel, vectorSet.size() - 1);
					cond = QString("%1 ≤ 𝜒(%2, %3) = %4")
						.arg(criteria, 3, 'f')
						.arg(1-critLevel, 3, 'f')
						.arg(vectorSet.size() - 1)
						.arg(quantile, 3, 'f');
					accepted = criteria <= quantile;
					implies = accepted ? "всі способи мають однакову імовірність" : 
						"всі способи мають різну імовірність" ;
					qf = [=](double a) { 
						return criteria <= ss::pearQuantile(1-a, vectorSet.size() - 1);
					};
					break;
				}
			case ss::VectorChain::Procedure::testAbbeP:
				{
					criteria = vectorSet.testAbbe();
					quantile = ss::normQuantile(critLevel);
					cond = QString("%1 ≤ n(%2) = %3")
						.arg(criteria, 3, 'f')
						.arg(critLevel, 3, 'f')
						.arg(quantile, 3, 'f');
					accepted = criteria > quantile;
					implies = accepted ? "спостереження незалежні" : 
						"спостереження залежні" ;
					qf = [=](double a) { 
						return criteria > ss::normQuantile(a);
					};
					break;
				}
			default:
				throw "How we got there...?";
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

	pmTable->clear();
	QList<double> probs = 
		{0.01, 0.03, 0.05, 0.1, 0.15, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.85,
			0.9, 0.95, 0.97, 0.99};
	pmTable->setRowCount(1);
	pmTable->setColumnCount(probs.size());

	QStringList vHeader, hHeader;
	for (int j = 0; j < probs.size(); j++) {
		pmTable->setItem(0, j, new QTableWidgetItem(
			qf(probs[j]) ? "+" : "-"));
	}

	for (int i = 0; i < probs.size(); i++) {
		hHeader.append(QString::number(probs[i]));
	}

	vHeader.append("H");

	pmTable->setHorizontalHeaderLabels(hHeader);
	pmTable->setVerticalHeaderLabels(vHeader);

	for (int i = 0; i < probs.size(); i++) {
		pmTable->setColumnWidth(i, 35);
	}

}

void VectorHypothesisDialog::makeVectorList() {
	QString vecs;
	for (auto const& v : vectors) {
		vecs.append(v->name() + ", ");
	}
	vecs.chop(2);

	vectorsLineEdit->setText(vecs);
};

void VectorHypothesisDialog::vectorDeletedHandler(Vector* vec) {
	if (vectors.removeAll(vec)) {
		makeVectorList();
		compute();
	}

	vectorSet.erase(std::remove_if(vectorSet.begin(), 
                              vectorSet.end(),
																[=](ss::Vector* x) { return x == vec->vector(); }),
               vectorSet.end());

	if (!vectors.size())
		this->close();
}
