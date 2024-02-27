#include "transformationFormulaEditor.hpp"
#include "gui/Section.h"


TransformationFormulaEditor::TransformationFormulaEditor(
		int* i, DataVector* vec, QString name,
		QWidget *parent, Qt::WindowFlags f) 
	: QDialog(parent, f) {
		dv = vec;
		transformIdx = i;
		vecName = name;

		this->setWindowTitle("Менеджер трансформацій [" + vecName + "]");
		this->setMinimumSize(500,400);
		this->setAttribute(Qt::WA_DeleteOnClose, true);
		QVBoxLayout* mainLayout = new QVBoxLayout();
		this->setLayout(mainLayout);
		mainLayout->setContentsMargins(0,0,0,0);
		mainLayout->setSpacing(0);

		QVBoxLayout* sublayout = new QVBoxLayout();
		sublayout->setContentsMargins(8,8,8,8);
		sublayout->setSpacing(8);
		mainLayout->addLayout(sublayout);

		QGridLayout* inputGridLayout = new QGridLayout;


		ui::Section* varsSection = new ui::Section("Змінні", 50);
		QLabel* varsLabel = new QLabel("x — довільний елемент векторa");
		varsLabel->adjustSize();
		QVBoxLayout* varsSectionLay = new QVBoxLayout();
		varsSectionLay->addWidget(varsLabel);
		varsSection->setContentLayout(*varsSectionLay);

		ui::Section* statisticsSection = new ui::Section("Функції (статистичні)", 100);
		QLabel* statisticsLabel = new QLabel(
				"med() — медіана\n"
				"xmin() — наймешний xᵢ\n"
				"xmax() — найбільший xᵢ\n"
				"size() — розмір вектора\n"
				"variance() — варіабельніть\n"
				"skew() — коефіцієнт асиметрії\n"
				"wam() — медіана середніх Уолша\n"
				"kurtosis() —  коеіцієнт ексцесу\n"
				"mean() — математичне сподівання\n"
				"mad() — абсолютне відхилення медіани\n"
				"cv() — коефіцієнт варіації (Пірсона)\n"
				"standartDeviation() — середньоквадратичне відхилення\n"
				"turncatedMean(k) — усічене середнє (k ∈ (0;0.5])\n"
				"rawMoment(n) — початковий момент n-го порядку (n ∈ R)\n"
				"centralMoment(n) — центральний момент n-го порядку (n ∈ R)");
		statisticsLabel->adjustSize();
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
		generalLabel->adjustSize();
		QVBoxLayout* generalSectionLay = new QVBoxLayout();
		generalSectionLay->addWidget(generalLabel);
		generalSection->setContentLayout(*generalSectionLay);

		QLabel* inputLabel = new QLabel("xᵢ = ");

		formulaLineEdit = new QLineEdit();
		formulaLineEdit->setPlaceholderText("Введіть формулу для xᵢ відносно x...");

		transformButton = new QPushButton("Трансформувати вектор " + vecName);

		statusTextEdit = new QTextEdit();
		statusTextEdit->setReadOnly(true);

		sublayout->addWidget(varsSection);
		sublayout->addWidget(statisticsSection);
		sublayout->addWidget(generalSection);
		varsSection->toggle(true);
		statisticsSection->toggle(false);
		generalSection->toggle(false);

		inputGridLayout->addWidget(inputLabel, 0, 0);
		inputGridLayout->addWidget(formulaLineEdit, 0, 1);

		sublayout->addLayout(inputGridLayout);
		sublayout->addWidget(transformButton);
		mainLayout->addWidget(statusTextEdit);

		connect(transformButton, &QPushButton::clicked,
				this, &TransformationFormulaEditor::transform);

		this->show();
}

void TransformationFormulaEditor::transform() {
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

void TransformationFormulaEditor::vectorDeletedHandler(int idx, DataVector* vec) {
	if (dv == vec)
		this->close();
}

/* formula that uses all functions (for test purposes): 
 * x+med()+xmin()+xmax()+size()+variance()+skew()+wam()+kurtosis()+mean()+mad()+cv()+standartDeviation()+turncatedMean(0.25)+rawMoment(5)+centralMoment(5)
 */
