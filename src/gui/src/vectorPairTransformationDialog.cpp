#include "vectorPairTransformationDialog.hpp"

#include "Section.h"

#include <vector/exprtk_quantile.hpp>

VectorPairTransformationDialog::VectorPairTransformationDialog(
	QList<VectorPair*> vectors,
	QWidget *parent, Qt::WindowFlags f) 
: TransformationDialogBase(QList<VectorEntry*>(vectors.begin(), vectors.end()), parent, f) {
	this->setWindowTitle("Менеджер двовимірних трансформацій");

	QVBoxLayout* sublayout = new QVBoxLayout();
	sublayout->setContentsMargins(8,8,8,8);
	sublayout->setSpacing(8);

	varsTextEdit->setText(
		"x — довільний елемент векторa x\n"
		"y — довільний елемент векторa y\n"
		"xr — ранг відповідного елемента вектора x\n"
		"yr — ранг відповідного елемента вектора y\n"
		"r — ранг відповідного елемента вектора y y двовимірному векторі"
	);

	ui::Section* statisticsSection = new ui::Section("Функції (статистичні)", 100);
	statisticsTextEdit->setText(
		QString::fromStdString(ss::exprtk::functionNames) + 
		"\n\nФункції двовимірного веткора\n" + QString::fromStdString(ss::VectorPair::exprtkFunctions) +
		"\n\nФункції одновимірних векторів (префікс x та y відповідно)\n" + QString::fromStdString(ss::Vector::exprtkFuncitons)
	);

	auto x = new Formula("xᵢ", "Введіть формулу для xᵢ");
	formulaLayout->addWidget(x);
	xExpression = x->line();

	auto y = new Formula("yᵢ", "Введіть формулу для yᵢ");
	formulaLayout->addWidget(y);
	yExpression = y->line();
}

void VectorPairTransformationDialog::transform() {
	statusTextEdit->clear();
	for (auto const& v : v_vectorEntry) {
		ss::VectorPair* vec = static_cast<VectorPair*>(v)->vectorPair();
		VectorPair* newVector = new VectorPair;
		newVector->setVectorPair(new ss::VectorPair(*static_cast<VectorPair*>(v)->vectorPair()));
		QString res = QString::fromStdString(
			newVector->vectorPair()->transform(xExpression->text().toStdString(), yExpression->text().toStdString())
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
