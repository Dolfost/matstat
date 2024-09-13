#include "transformationFormulaEditorDialog.hpp"

#include "Section.h"

int TransformationFormulaEditorDialog::trIdx = 0;

TransformationFormulaEditorDialog::TransformationFormulaEditorDialog(
	QList<Vector*> vectors,
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
	QLabel* statisticsLabel = new QLabel(
		"normQuantile(a) — квантиль нормального розподілу\n"
		"studQuantile(a,v) — квантиль розподілу Стьюдента\n"
		"pearQuantile(a,v) — квантиль розподілу Пірсона\n"
		"fishQuantile(a,v1,v2) — квантиль розподілу Фішера\n"
		"normCdf(u) — функція розподілу нормованого нормального розподілу"
		"\n" + QString::fromStdString(ss::Vector::exprtkFuncitons)
	);
	QVBoxLayout* statisticsSectionLay = new QVBoxLayout();
	statisticsSectionLay->addWidget(statisticsLabel);
	statisticsSection->setContentLayout(*statisticsSectionLay);

	ui::Section* generalSection = new ui::Section("Функції (загальні)", 75);
	QLabel* generalLabel = new QLabel(
		"abs(x), avg(…), ceil(x), clamp(r0,x,r1), equal(x,y), erf(x), erfc(x), exp(x),\n"
		"expm1(x), floor(x), hypot(x,y), iclamp(r0,x,r1), inrange(r0,x,r2), log(x),\n"
		"log10(x), log1p(x), log2(x), logn(x,n), max(…), min(…), mul(…), ncdf(x),\n"
		"not_equal(x,y), pow(x,n), root(x, n), round(x), roundn(x,n), sgn(x), sqrt(x),\n"
		"sum(…), swap(x,y), trunc(x), acos(x), ahosh(x), asin(x), asinh(x), atan(x),\n"
		"atan2(x,y), atanh(x), cos(x), cosh(x), cot(x), csc(x), sec(x), sin(x), sinc(c),\n"
		"sinh(x), tan(x), tanh(x), deg2rad(x), deg2grad(x), rad2deg(x), grad2deg(x)"
	);
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
		Vector* newVector = new Vector;
		newVector->setVector(new ss::Vector(*v->vector()));
		QString res = QString::fromStdString(
			newVector->vector()->transform(formulaLineEdit->text().toStdString())
		);
		if (res.length() != 0) {
			statusTextEdit->append("Трансформування " + v->name() + "\n" + res + "\n");
			delete newVector;
		} else {
			newVector->setName("TR" + QString::number(++trIdx) + "(" + v->name() + ")");
			statusTextEdit->append("Вектор " + v->name() + " перетворено вдало.\n" +
													"xᵢ = " + formulaLineEdit->text() + ".\n"
													"Новий вектор було збережено у " +
													newVector->name() + "\n");
			emit vectorTransformed(newVector);
		}
	}
}

void TransformationFormulaEditorDialog::makeVectorNames() {
	QString vectors;
	for (auto const& v : vecs) {
		vectors.append(v->name() + ", ");
	}
	vectors.chop(2);

	vectorNames->setText(vectors);
}

void TransformationFormulaEditorDialog::vectorDeletedHandler(Vector* vectorEntry) {
	if (vecs.removeAll(vectorEntry))
		makeVectorNames();

	if (vecs.isEmpty())
		this->close();
}

/* formula that uses all functions (for test purposes): 
x+med()+xmin()+xmax()+size()+variance()+skew()+wam()+kurtosis()+mean()+mad()+cv()+standartDeviation()+turncatedMean(0.25)+rawMoment(5)+centralMoment(5)
 */
