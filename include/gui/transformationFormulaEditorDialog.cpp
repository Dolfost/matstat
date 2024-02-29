#include "transformationFormulaEditorDialog.hpp"
#include "gui/Section.h"


TransformationFormulaEditorDialog::TransformationFormulaEditorDialog(
		int* i, DataVector* vec, QString name,
		QWidget *parent, Qt::WindowFlags f) 
	: QDialog(parent, f) {
		dv = vec;
		transformIdx = i;
		vecName = name;

		this->setWindowTitle("Менеджер трансформацій [" + vecName + "]");
		this->setAttribute(Qt::WA_DeleteOnClose, true);
		QVBoxLayout* mainLayout = new QVBoxLayout();
		this->setLayout(mainLayout);
		mainLayout->setContentsMargins(0,0,0,0);
		mainLayout->setSpacing(0);

		QVBoxLayout* sublayout = new QVBoxLayout();
		sublayout->setContentsMargins(8,8,8,8);
		sublayout->setSpacing(8);

		QGroupBox* tipsGroup = new QGroupBox("Підказки");
		tipsGroup->setLayout(new QVBoxLayout);

		ui::Section* varsSection = new ui::Section("Змінні", 50);
		QLabel* varsLabel = new QLabel("x — довільний елемент векторa");
		QVBoxLayout* varsSectionLay = new QVBoxLayout();
		varsSectionLay->addWidget(varsLabel);
		varsSection->setContentLayout(*varsSectionLay);

		ui::Section* statisticsSection = new ui::Section("Функції (статистичні)", 100);
		QLabel* statisticsLabel = new QLabel(DataVector::exprtkFuncitons);
		QVBoxLayout* statisticsSectionLay = new QVBoxLayout();
		statisticsSectionLay->addWidget(statisticsLabel);
		statisticsSection->setContentLayout(*statisticsSectionLay);

		ui::Section* generalSection = new ui::Section("Функції (загальні)", 75);
		QLabel* generalLabel = new QLabel(exprtkGeneralFunctions);
		QVBoxLayout* generalSectionLay = new QVBoxLayout();
		generalSectionLay->addWidget(generalLabel);
		generalSection->setContentLayout(*generalSectionLay);

		QLabel* inputLabel = new QLabel("xᵢ = ");

		formulaLineEdit = new QLineEdit();
		formulaLineEdit->setPlaceholderText("Введіть формулу для xᵢ відносно x...");

		transformButton = new QPushButton("Трансформувати вектор " + vecName);

		statusTextEdit = new QTextEdit();
		statusTextEdit->setReadOnly(true);

		tipsGroup->layout()->addWidget(varsSection);
		tipsGroup->layout()->addWidget(statisticsSection);
		tipsGroup->layout()->addWidget(generalSection);
		varsSection->toggle(true);
		statisticsSection->toggle(false);
		generalSection->toggle(false);

		QGridLayout* inputGridLayout = new QGridLayout;
		inputGridLayout->addWidget(inputLabel, 0, 0);
		inputGridLayout->addWidget(formulaLineEdit, 0, 1);

		sublayout->addWidget(tipsGroup);
		sublayout->addLayout(inputGridLayout);
		sublayout->addWidget(transformButton);

		mainLayout->addLayout(sublayout);
		mainLayout->addWidget(statusTextEdit);

		connect(transformButton, &QPushButton::clicked,
				this, &TransformationFormulaEditorDialog::transform);

		this->resize(500, 350);
		this->show();
}

void TransformationFormulaEditorDialog::transform() {
	DataVector tmpdv(*dv);
	QString res = tmpdv.transform(formulaLineEdit->text());
	if (res.length() != 0) {
		statusTextEdit->setText(res);
	} else {
		QString name = "TR" + QString::number(++(*transformIdx)) + "(" + vecName + ")";
		statusTextEdit->setText("Вектор перетворено вдало.\n"
				"Новий вектор було збережено у " +
				name + "\n\nxᵢ = " + formulaLineEdit->text() + ".");
		emit vectorTransformed(&tmpdv.vector(), name);
	}
}

void TransformationFormulaEditorDialog::vectorDeletedHandler(int idx, DataVector* vec) {
	if (dv == vec)
		this->close();
}

/* formula that uses all functions (for test purposes): 
 * x+med()+xmin()+xmax()+size()+variance()+skew()+wam()+kurtosis()+mean()+mad()+cv()+standartDeviation()+turncatedMean(0.25)+rawMoment(5)+centralMoment(5)
 */
