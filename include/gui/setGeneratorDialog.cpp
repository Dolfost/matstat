#include "setGeneratorDialog.hpp"
#include <QtWidgets/qgridlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>

ParametersWidget::ParametersWidget(QStringList params, std::vector<double> val, bool en) : QWidget() {
	size = params.length();
	if (val.size() < size)
		val.resize(size);

	layout = new QGridLayout;
	layout->setContentsMargins(0,0,0,0);

	for (int i = 0; i < size; i++) {
		layout->addWidget(new QLabel(params[i]), i, 0);
		QDoubleSpinBox* sb = new QDoubleSpinBox;
		sb->setEnabled(en);
		sb->setValue(val[i]);
		sb->setDecimals(precision);
		layout->addWidget(sb, i, 1);
	}

	this->setLayout(layout);
}

std::vector<double> ParametersWidget::parameters() {
	std::vector<double> p;
	for (int i = 0; i < size; i++) {
		p.push_back(
				static_cast<QDoubleSpinBox*>(
					layout->itemAtPosition(i, 1)->widget())
				->value());
	}

	return p;
}

SetGeneratorDialog::SetGeneratorDialog(
		VectorEntry* vectorEntry,
		QWidget *parent, bool show, Qt::WindowFlags f) 
	: QDialog(parent, f) {
		ve = vectorEntry;

		this->setAttribute(Qt::WA_DeleteOnClose, true);
		QVBoxLayout* mainLayout = new QVBoxLayout();
		this->setLayout(mainLayout);
		mainLayout->setContentsMargins(0,0,0,0);

		QVBoxLayout* layout = new QVBoxLayout;
		layout->setContentsMargins(10,10,10,0);
		mainLayout->addLayout(layout);

		distributionComboBox = new QComboBox();
		for (int i = 1; i < DistributionReproducer::Distribution::CountD; i++) {
			distributionComboBox->insertItem(i,
					DistributionReproducer::distributionName[i]);
		}
		QGroupBox* distributionBox = new QGroupBox("Розподіл");
		QVBoxLayout* distributionLayout = new QVBoxLayout;
		distributionLayout->setContentsMargins(1,1,1,1);
		distributionBox->setLayout(distributionLayout);
		distributionLayout->addWidget(distributionComboBox);

		QGridLayout* countLayout = new QGridLayout;
		countLayout->addWidget(new QLabel("Розмір вибірки"), 0, 0);
		countSpinBox = new QSpinBox;
		countSpinBox->setRange(2, INT_MAX);
		countSpinBox->setValue(500);
		countLayout->addWidget(countSpinBox, 0, 1);

		parametersLayout = new QVBoxLayout;
		parametersLayout->setContentsMargins(1,1,1,0);

		methodComboBox = new QComboBox;
		for (int i = 0; i < DistributionReproducer::Method::CountM; i++) {
			methodComboBox->insertItem(i,
					DistributionReproducer::methodName[i]);
		}

		QGroupBox* methodBox = new QGroupBox("Метод відтворення");
		QVBoxLayout* methodLayout = new QVBoxLayout;
		methodLayout->setContentsMargins(1,1,1,0);
		methodBox->setLayout(methodLayout);
		methodLayout->addWidget(methodComboBox);

		boundsBox = new QGroupBox("Межі реалізаці випадкової величини");
		QHBoxLayout* boundsLayout = new QHBoxLayout;
		boundsLayout->setContentsMargins(1,1,1,0);
		boundsBox->setLayout(boundsLayout);
		minSpinBox = new QDoubleSpinBox();
		minSpinBox->setMinimum(INT_MIN);
		minSpinBox->setDecimals(precision);
		maxSpinBox = new QDoubleSpinBox();
		maxSpinBox->setMaximum(INT_MAX);
		maxSpinBox->setDecimals(precision);
		boundsLayout->addWidget(minSpinBox);
		boundsLayout->addWidget(maxSpinBox);

		generateButton = new QPushButton("Генерувати");
		connect(generateButton, &QPushButton::clicked,
				this, &SetGeneratorDialog::generate);

		statusBar = new QStatusBar();
		statusBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		statusBar->setContentsMargins(0,0,0,0);
		
		distributionLayout->addLayout(parametersLayout);
		layout->addWidget(distributionBox);
		layout->addLayout(countLayout);
		layout->addWidget(boundsBox);
		layout->addWidget(methodBox);
		layout->addWidget(generateButton);

		mainLayout->addWidget(statusBar);

		connect(distributionComboBox, &QComboBox::currentIndexChanged,
				this, &SetGeneratorDialog::distributionSelected);

		connect(methodComboBox, &QComboBox::currentIndexChanged,
				this, &SetGeneratorDialog::methodSelected);

		connect(minSpinBox, &QDoubleSpinBox::valueChanged,
				this, &SetGeneratorDialog::minBoundChanged);
		connect(maxSpinBox, &QDoubleSpinBox::valueChanged,
				this, &SetGeneratorDialog::maxBoundChanged);

		QString title = QString("Генератор вибірок");

		if (ve != nullptr) {
			title.append(QString(" згідно розподілу вектора %1 — ")
						.arg(ve->name));
			enabled = false;
			if (ve->vector->rep.model != DistributionReproducer::UnknownD) {
				title.append(DistributionReproducer::distributionName[ve->vector->rep.model]);
				distributionComboBox->setCurrentIndex(ve->vector->rep.model-1);
				params = ve->vector->rep.parameters;
				countSpinBox->setValue(ve->vector->size());
				minSpinBox->setValue(ve->vector->min());
				maxSpinBox->setValue(ve->vector->max());
			} else {
				title.append(DistributionReproducer::distributionName
						[DistributionReproducer::UnknownD]);
				statusBar->showMessage("Розподіл " + ve->name +
						" не був відтворений");
				minSpinBox->setEnabled(enabled);
				maxSpinBox->setEnabled(enabled);
				countSpinBox->setEnabled(enabled);
				methodComboBox->setEnabled(enabled);
				generateButton->setEnabled(enabled);
			}

			distributionComboBox->setEnabled(enabled);
		}

		this->setWindowTitle(title);

		distributionSelected(distributionComboBox->currentIndex());
		methodSelected(methodComboBox->currentIndex());

		this->adjustSize();
		this->resize(500, this->height());
		if (show)
			this->show();
}

void SetGeneratorDialog::generate() {
	DataVector* dv;
	DistributionReproducer::Method m =
		DistributionReproducer::Method(methodComboBox->currentIndex());
	size_t count = countSpinBox->value();
	double
		min = minSpinBox->value(),
		max = maxSpinBox->value();

	if (ve != nullptr and ve->vector->rep.model != DistributionReproducer::UnknownD)
		dv = new DataVector(ve->vector->rep.generateSet(m, count, min, max));
	else {
		DistributionReproducer dr;
		dr.setDistribution(DistributionReproducer::Distribution(distributionComboBox->currentIndex()+1),
				parametersWidget->parameters(), count);
		dv = new DataVector(dr.generateSet(m, count, min, max));
	}

	VectorEntry* ve = new VectorEntry(dv);
	ve->setModel(dv->rep.model, dv->rep.parameters, m);
	
	emit setGenerated(ve);
}

void SetGeneratorDialog::distributionSelected(int model) {
	if (parametersWidget != nullptr)
		parametersLayout->removeWidget(parametersWidget);
	delete parametersWidget;
	parametersWidget = new ParametersWidget(DistributionReproducer::parameterName[model+1], params, enabled);
	parametersLayout->addWidget(parametersWidget);
}

void SetGeneratorDialog::methodSelected(int method) {
	boundsBox->setVisible(method);
}

void SetGeneratorDialog::minBoundChanged(double val) {
	minSpinBox->blockSignals(true);
	maxSpinBox->blockSignals(true);

	maxSpinBox->setMinimum(val+0.001);

	minSpinBox->blockSignals(false);
	maxSpinBox->blockSignals(false);
}

void SetGeneratorDialog::maxBoundChanged(double val) {
	minSpinBox->blockSignals(true);
	maxSpinBox->blockSignals(true);

	minSpinBox->setMaximum(val-0.001);

	minSpinBox->blockSignals(false);
	maxSpinBox->blockSignals(false);
}

void SetGeneratorDialog::vectorDeletedHandler(VectorEntry* vectorEntry) {
	if (ve == vectorEntry)
		this->close();
}
