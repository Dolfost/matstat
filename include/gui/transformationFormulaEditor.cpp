#include "transformationFormulaEditor.hpp"
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qtextedit.h>

TransformationFormulaEditor::TransformationFormulaEditor(
		int i, DataVector* vec, QString vecname,
		QWidget *parent, Qt::WindowFlags f) 
	: QDialog(parent, f) {
		dv = vec;
		idx = i;

		this->setWindowTitle("Менеджер трансформацій [" + vecname + "]");
		this->setMinimumSize(600,400);
		this->setAttribute(Qt::WA_DeleteOnClose, true);
		QVBoxLayout* mainLayout = new QVBoxLayout();
		this->setLayout(mainLayout);
		mainLayout->setContentsMargins(0,0,0,0);
		mainLayout->setSpacing(0);

		QVBoxLayout* sublayout = new QVBoxLayout();
		sublayout->setContentsMargins(8,8,8,8);
		sublayout->setSpacing(8);
		mainLayout->addLayout(sublayout);

		tipsLabel = new QLabel();
		tipsLabel->setText(
				"Змінні:\n"
				"    x — довільний елемент векторa\n"
				"Функції (конкретні):\n"
				"    med() — медіана\n"
				"    xmin() — наймешний xᵢ\n"
				"    xmax() — найбільший xᵢ\n"
				"    size() — розмір вектора\n"
				"    variance() — варіабельніть\n"
				"    skew() — коефіцієнт асиметрії\n"
				"    wam() — медіана середніх Уолша\n"
				"    kurtosis() —  коеіцієнт ексцесу\n"
				"    mean() — математичне сподівання\n"
				"    mad() — абсолютне відхилення медіани\n"
				"    cv() — коефіцієнт варіації (Пірсона)\n"
				"    standartDeviation() — середньоквадратичне відхилення\n"
				"    turncatedMean(k) — усічене середнє (k ∈ (0;0.5])\n"
				"    rawMoment(n) — початковий момент n-го порядку (n ∈ R)\n"
				"    centralMoment(n) — центральний момент n-го порядку (n ∈ R)\n"
				"Функції (загальні):"
				);

		formulaLineEdit = new QLineEdit();
		formulaLineEdit->setPlaceholderText("Введіть формулу для xₙ...");

		transformButton = new QPushButton("Трансформувати вектор " + vecname);

		statusTextEdit = new QTextEdit();
		statusTextEdit->setReadOnly(true);

		sublayout->addWidget(tipsLabel);
		sublayout->addWidget(formulaLineEdit);
		sublayout->addWidget(transformButton);
		mainLayout->addWidget(statusTextEdit);

		connect(transformButton, &QPushButton::clicked,
				this, &TransformationFormulaEditor::transform);

		this->show();
}

void TransformationFormulaEditor::transform() {
	QString res = dv->transform(formulaLineEdit->text());
	if (res.length() != 0) {
		statusTextEdit->setText(res);
	} else {
		statusTextEdit->setText("Вектор перетворено!\n\nxᵢ = " + formulaLineEdit->text());
		emit vectorTransformed(idx, dv);
	}
}
