#include <transformationDialogBase.hpp>

#include "Section.h"

int TransformationDialogBase::trIdx = 0;

TransformationDialogBase::TransformationDialogBase(
	QList<VectorEntry*> vectors,
	QWidget *parent, Qt::WindowFlags f) 
: SetDialogBase(vectors, parent, f) {
	this->setWindowTitle("Менеджер трансформацій");

	QVBoxLayout* sublayout = new QVBoxLayout();
	sublayout->setContentsMargins(8,8,8,8);
	sublayout->setSpacing(8);

	QGroupBox* tipsGroup = new QGroupBox("Підказки");
	tipsGroup->setLayout(new QVBoxLayout);
	tipsGroup->layout()->setContentsMargins(2,2,2,2);

	ui::Section* varsSection = new ui::Section("Змінні", 50);
	varsTextEdit = new QTextEdit();
	varsTextEdit->setReadOnly(true);
	QVBoxLayout* varsSectionLay = new QVBoxLayout();
	varsSectionLay->setContentsMargins(0,0,0,0);
	varsSectionLay->addWidget(varsTextEdit);
	varsSection->setContentLayout(*varsSectionLay);

	ui::Section* statisticsSection = new ui::Section("Функції (статистичні)", 100);
	statisticsTextEdit = new QTextEdit;
	statisticsTextEdit->setReadOnly(true);
	QVBoxLayout* statisticsSectionLay = new QVBoxLayout();
	statisticsSectionLay->setContentsMargins(0,0,0,0);
	statisticsSectionLay->addWidget(statisticsTextEdit);
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
	generalLabel->setWordWrap(true);
	QVBoxLayout* generalSectionLay = new QVBoxLayout();
	generalSectionLay->setContentsMargins(0,0,0,0);
	generalSectionLay->addWidget(generalLabel);
	generalSection->setContentLayout(*generalSectionLay);

	transformButton = new QPushButton("Трансформувати вектор(и)");

	statusTextEdit = new QTextEdit();
	statusTextEdit->setReadOnly(true);

	tipsGroup->layout()->addWidget(varsSection);
	tipsGroup->layout()->addWidget(statisticsSection);
	tipsGroup->layout()->addWidget(generalSection);
	varsSection->toggle(true);
	statisticsSection->toggle(false);
	generalSection->toggle(false);

	formulaLayout = new QVBoxLayout;

	sublayout->addWidget(s_vectorsGroupBox);
	sublayout->addWidget(tipsGroup);
	sublayout->addLayout(formulaLayout);
	sublayout->addWidget(transformButton);

	v_mainLayout->addLayout(sublayout);
	v_mainLayout->addWidget(statusTextEdit);

	connect(transformButton, &QPushButton::clicked,
				 this, &TransformationDialogBase::transform);
}

Formula::Formula(const QString& n, const QString& p) {
	setName(n);
	f_lineEdit->setPlaceholderText(p);

	setLayout(new QHBoxLayout);
	layout()->addWidget(f_name);
	layout()->addWidget(f_lineEdit);
	setContentsMargins(0,0,0,0);
	layout()->setContentsMargins(0,0,0,0);
}

/* formula that uses all functions (for test purposes): 
x+med()+xmin()+xmax()+size()+variance()+skew()+wam()+kurtosis()+mean()+mad()+cv()+standartDeviation()+turncatedMean(0.25)+rawMoment(5)+centralMoment(5)
 */
