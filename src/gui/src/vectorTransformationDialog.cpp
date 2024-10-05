#include "vectorTransformationDialog.hpp"

#include "Section.h"
#include <namedWidget.hpp>

#include <vector/exprtk_quantile.hpp>

VectorTransformationDialog::VectorTransformationDialog(
	QList<Vector*> vectors,
	QWidget *parent, Qt::WindowFlags f) 
: TransformationDialogBase(QList<VectorEntry*>(vectors.begin(), vectors.end()), parent, f) {
	this->setWindowTitle("Менеджер одновимірних трансформацій");

	QVBoxLayout* sublayout = new QVBoxLayout();
	sublayout->setContentsMargins(8,8,8,8);
	sublayout->setSpacing(8);

	varsTextEdit->setText(
		"x — довільний елемент векторa\n"
		"xr — ранг відповідного елемента вектора\n"
	);

	ui::Section* statisticsSection = new ui::Section("Функції (статистичні)", 100);
	statisticsTextEdit->setText(
		QString::fromStdString(ss::exprtk::functionNames) + 
		"\n" + QString::fromStdString(ss::Vector::exprtkFuncitons)
	);

	auto x = new Formula("xᵢ", "Введіть формулу для xᵢ");
	formulaLayout->addWidget(x);
	xExpression = x->line();
}

void VectorTransformationDialog::transform() {
	statusTextEdit->clear();
	for (auto const& v : v_vectorEntry) {
		Vector* newVector = new Vector;
		newVector->setVector(new ss::Vector(*static_cast<Vector*>(v)->vector()));
		QString res = QString::fromStdString(
			newVector->vector()->transform(xExpression->text().toStdString())
		);
		if (res.length() != 0) {
			statusTextEdit->append("Трансформування " + v->name() + "\n" + res + "\n");
			delete newVector;
		} else {
			newVector->setName("TR" + QString::number(++trIdx) + "(" + v->name() + ")");
			statusTextEdit->append("Вектор " + v->name() + " перетворено вдало.\n" +
													"xᵢ = " + xExpression->text() + ".\n"
													"Новий вектор було збережено у " +
													newVector->name() + "\n");
			emit vectorTransformed(newVector);
		}
	}
}

/* formula that uses all functions (for test purposes): 
x+med()+xmin()+xmax()+size()+variance()+skew()+wam()+kurtosis()+mean()+mad()+cv()+standartDeviation()+turncatedMean(0.25)+rawMoment(5)+centralMoment(5)
 */
