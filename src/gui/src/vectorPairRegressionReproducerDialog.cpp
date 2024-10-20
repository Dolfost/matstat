#include "vectorPairRegressionReproducerDialog.hpp"
#include <QLabel>
#include <vector>

VectorPairRegressionReproducerDialog::VectorPairRegressionReproducerDialog(
	VectorPair* vectorEntry,
	QWidget *parent, Qt::WindowFlags f) 
: FunctionReproducerDialogBase(vectorEntry, parent, f) {
	v_vectorPair = dynamic_cast<VectorPair*>(vectorEntry);
	this->setWindowTitle("Інформація про відтворення регрісії " + v_vectorEntry->name());
	v_mainLayout->setContentsMargins(10,10,10,10);

	reproductName->setText("Відтворювана регресія: ");
	for (int i = 0; i < (int)ss::VectorPair::Regression::Model::Count; i++)
		modelComboBox->insertItem(i, QString::fromStdString(ss::VectorPair::Regression::regressionName[i]));
	modelComboBox->setCurrentIndex((int)v_vectorPair->vectorPair()->reg.model);

	distribute(modelComboBox->currentIndex());
}

void VectorPairRegressionReproducerDialog::fill() {
	QList<QStringList> p, d;
	for (int i = 0; i < v_vectorPair->vectorPair()->reg.parametersCount; i++) {
		p.push_back(
			{
				QString::fromStdString(v_vectorPair->vectorPair()->reg.paremeterNames[i]),
				n(v_vectorPair->vectorPair()->reg.parameters[i])
			}
		);
		d.push_back(
			{
			"D{" + QString::fromStdString(v_vectorPair->vectorPair()->reg.parametersDeviationNames[i]) + "}",
			n(v_vectorPair->vectorPair()->reg.parametersDeviation[i])
			}
		);
	}

	parameters->widget()->fill(p);
	parametersDeviation->widget()->fill(d);
}

void VectorPairRegressionReproducerDialog::distribute(int reg) {
	v_vectorPair->vectorPair()->reproduceRegression(ss::VectorPair::Regression::Model(reg));
	FunctionReproducerDialogBase::distribute(reg);
}

void VectorPairRegressionReproducerDialog::makeTtest() {
	if (v_vectorPair->regressionModel() != ss::VectorPair::Regression::Model::Unknown) {
		ss::VectorPair::Regression& rep = (v_vectorPair->vectorPair()->reg);

		if (v_vectorPair->regressionModel() != rep.model) {
			parametersTest->widget()->setVisible(false);
			parametersTestInfoLabel->setVisible(true);
			parametersTestInfoLabel->setText(
				"Відтворювана регресія не збігається "
				"з регресією за якою було згенеровано вибірку"
			);
			return;
		}
		parametersTest->widget()->setVisible(true);
		parametersTestInfoLabel->setVisible(false);

		QList<std::pair<QString, double>> t;
		for (int i = 0; i < rep.parameters.size(); i++) {
			t.push_back(
				{
					QString::fromStdString(rep.paremeterNames[i]),
					(v_vectorPair->regressionParameters()[i]-rep.parameters[i]) / 
					std::sqrt(rep.parametersDeviation[i])
				}
			);
		}

		parametersTest->widget()->fill(t, v_vectorPair->vectorPair()->size());
	} else {
			parametersTest->widget()->setVisible(false);
			parametersTestInfoLabel->setVisible(true);
			parametersTestInfoLabel->setText(
				"Вибірка не згенерована у програмі/через регресію"
			);
	}
}
