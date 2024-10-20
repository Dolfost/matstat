#include "vectorDistributionReproducerDialog.hpp"
#include <QLabel>
#include <vector>

VectorDistributionReproducerDialog::VectorDistributionReproducerDialog(
	Vector* vectorEntry,
	QWidget *parent, Qt::WindowFlags f) 
: FunctionReproducerDialogBase(vectorEntry, parent, f) {
	v_vector = dynamic_cast<Vector*>(vectorEntry);
	this->setWindowTitle("Інформація про відтворення розподілу " + v_vectorEntry->name());
	v_mainLayout->setContentsMargins(10,10,10,10);

	reproductName->setText("Відтворюваний розподіл: ");
	for (int i = 0; i < (int)ss::Vector::Distribution::Model::Count; i++)
		modelComboBox->insertItem(i, QString::fromStdString(ss::Vector::Distribution::distributionName[i]));
	modelComboBox->setCurrentIndex((int)v_vector->vector()->dist.model);

	distribute(modelComboBox->currentIndex());
}

void VectorDistributionReproducerDialog::fill() {
	QList<QStringList> p, d;
	for (int i = 0; i < v_vector->vector()->dist.parametersCount; i++) {
		p.push_back(
			{
				QString::fromStdString(v_vector->vector()->dist.paremeterNames[i]),
				n(v_vector->vector()->dist.parameters[i])
			}
		);
		d.push_back(
			{
			"D{" + QString::fromStdString(v_vector->vector()->dist.parametersDeviationNames[i]) + "}",
			n(v_vector->vector()->dist.parametersDeviation[i])
			}
		);
	}

	if (v_vector->vector()->dist.parametersCount == 2) {
		d.push_back(
			{
				"cov{" + QString::fromStdString(v_vector->vector()->dist.paremeterNames[0]) + "," +
				QString::fromStdString(v_vector->vector()->dist.paremeterNames[1]) + "}",
				n(v_vector->vector()->dist.parametersCv)
			}
		);
	}

	parameters->widget()->fill(p);
	parametersDeviation->widget()->fill(d);
}

void VectorDistributionReproducerDialog::distribute(int dist) {
	v_vector->vector()->reproduceDistribution(ss::Vector::Distribution::Model(dist));
	FunctionReproducerDialogBase::distribute(dist);
}

void VectorDistributionReproducerDialog::makeTtest() {
	if (v_vector->distribuitonModel() != ss::Vector::Distribution::Model::Unknown) {
		ss::Vector::Distribution& rep = (v_vector->vector()->dist);

		if (v_vector->model()!= rep.model) {
			parametersTest->widget()->setVisible(false);
			parametersTestInfoLabel->setVisible(true);
			parametersTestInfoLabel->setText(
				"Відтворюваний розподіл не збігається "
				"з розподілом за яким буо згенеровано вибірку"
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
					(v_vector->distributionParameters()[i]-rep.parameters[i]) / 
					std::sqrt(rep.parametersDeviation[i])
				}
			);
		}

		parametersTest->widget()->fill(t, v_vector->vector()->size());
	} else {
			parametersTest->widget()->setVisible(false);
			parametersTestInfoLabel->setVisible(true);
			parametersTestInfoLabel->setText(
				"Вибірка не згенерована у програмі"
			);
	}
}
