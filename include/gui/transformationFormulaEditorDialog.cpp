#include "transformationFormulaEditorDialog.hpp"

#include "statistics/statistics.hpp"
#include "gui/Section.h"

int TransformationFormulaEditorDialog::trIdx = 0;

TransformationFormulaEditorDialog::TransformationFormulaEditorDialog(
		QList<VectorEntry*> vectors,
		QWidget *parent, Qt::WindowFlags f) 
	: QDialog(parent, f) {
		vecs = vectors;

		this->setWindowTitle("Менеджер трансформацій");
		this->setAttribute(Qt::WA_DeleteOnClose, true);
		QVBoxLayout* mainLayout = new QVBoxLayout();
		this->setLayout(mainLayout);
		mainLayout->setContentsMargins(0,0,0,0);
		mainLayout->setSpacing(0);

		QVBoxLayout* sublayout = new QVBoxLayout();
		sublayout->setContentsMargins(8,8,8,8);
		sublayout->setSpacing(8);

		QGroupBox* activeGroup = new QGroupBox("Вектори, які будуть перетворені");
		activeGroup->setLayout(new QVBoxLayout);
		vectorNames = new QLineEdit;
		vectorNames->setReadOnly(true);
		activeGroup->layout()->addWidget(vectorNames);
		activeGroup->layout()->setContentsMargins(2,2,2,2);

		QGroupBox* tipsGroup = new QGroupBox("Підказки");
		tipsGroup->setLayout(new QVBoxLayout);
		tipsGroup->layout()->setContentsMargins(2,2,2,2);

		ui::Section* varsSection = new ui::Section("Змінні", 50);
		QLabel* varsLabel = new QLabel("x — довільний елемент векторa");
		QVBoxLayout* varsSectionLay = new QVBoxLayout();
		varsSectionLay->addWidget(varsLabel);
		varsSection->setContentLayout(*varsSectionLay);

		ui::Section* statisticsSection = new ui::Section("Функції (статистичні)", 100);
		QLabel* statisticsLabel = new QLabel(DataVector::exprtkFuncitons +
				"\n" + Statistics::exprtkFuncitons);
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

		transformButton = new QPushButton("Трансформувати вектор(и)");

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

		sublayout->addWidget(activeGroup);
		sublayout->addWidget(tipsGroup);
		sublayout->addLayout(inputGridLayout);
		sublayout->addWidget(transformButton);

		mainLayout->addLayout(sublayout);
		mainLayout->addWidget(statusTextEdit);

		makeVectorNames();

		connect(transformButton, &QPushButton::clicked,
				this, &TransformationFormulaEditorDialog::transform);

		this->resize(500, 350);
		this->show();
}

void TransformationFormulaEditorDialog::transform() {
	statusTextEdit->clear();
	for (auto const& v : vecs) {
		VectorEntry* newVectorEntry = new VectorEntry;
		newVectorEntry->vector = new DataVector(v->vector->vector());
		QString res = newVectorEntry->vector->transform(formulaLineEdit->text());
		if (res.length() != 0) {
			statusTextEdit->append("Трансформування " + v->name + "\n" + res + "\n");
			delete newVectorEntry;
		} else {
			newVectorEntry->name = "TR" + QString::number(++trIdx) + "(" + v->name + ")";
			statusTextEdit->append("Вектор " + v->name + " перетворено вдало.\n" +
					"xᵢ = " + formulaLineEdit->text() + ".\n"
					"Новий вектор було збережено у " +
					newVectorEntry->name + "\n");
			emit vectorTransformed(newVectorEntry);
		}
	}
}

void TransformationFormulaEditorDialog::makeVectorNames() {
		QString vectors;
		for (auto const& v : vecs) {
			vectors.append(v->name + ", ");
		}
		vectors.chop(2);

		vectorNames->setText(vectors);
}

void TransformationFormulaEditorDialog::vectorDeletedHandler(VectorEntry* vectorEntry) {
	if (vecs.removeAll(vectorEntry))
		makeVectorNames();

	if (vecs.isEmpty())
		this->close();
}

/* formula that uses all functions (for test purposes): 
x+med()+xmin()+xmax()+size()+variance()+skew()+wam()+kurtosis()+mean()+mad()+cv()+standartDeviation()+turncatedMean(0.25)+rawMoment(5)+centralMoment(5)
 */
