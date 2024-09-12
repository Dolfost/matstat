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
		Vector* vectorEntry,
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
		for (int i = 1; i < (int)ss::Vector::Distribution::Model::Count; i++) {
			distributionComboBox->insertItem(i,
					QString::fromStdString(ss::Vector::Distribution::distributionName[i]));
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
		for (int i = 0; i < (int)ss::Vector::Distribution::Method::Count; i++) {
			methodComboBox->insertItem(i,
					QString::fromStdString(ss::Vector::Distribution::methodName[i]));
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
								.arg(ve->name()));
			enabled = false;
		if (ve->vector()->dist.model != ss::Vector::Distribution::Model::Unknown) {
			title.append(ss::Vector::Distribution::distributionName[(int)ve->vector()->dist.model]);
			distributionComboBox->setCurrentIndex((int)ve->vector()->dist.model-1);
			params = ve->vector()->dist.parameters;
			countSpinBox->setValue(ve->vector()->size());
			minSpinBox->setValue(ve->vector()->min());
			maxSpinBox->setValue(ve->vector()->max());
			} else {
				title.append(ss::Vector::Distribution::distributionName
						[(int)ss::Vector::Distribution::Model::Unknown]);
			statusBar->showMessage("Розподіл " + ve->name() +
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
	ss::Vector* dv;
	ss::Vector::Distribution::Method m =
		ss::Vector::Distribution::Method(methodComboBox->currentIndex());
	size_t count = countSpinBox->value();
	double
		min = minSpinBox->value(),
		max = maxSpinBox->value();

	ss::Vector::Distribution::Model dist;
	std::vector<double> parameters;

	if (ve != nullptr and ve->vector()->dist.model != ss::Vector::Distribution::Model::Unknown) {
		dv = new ss::Vector(ve->vector()->dist.generateSet(m, count, min, max));
		dist = ve->vector()->dist.model;
		parameters = ve->vector()->dist.parameters;
	} else {
		ss::Vector::Distribution dr;
		dr.setDistribution(ss::Vector::Distribution::Model(distributionComboBox->currentIndex()+1),
				parametersWidget->parameters(), count);
		dv = new ss::Vector(dr.generateSet(m, count, min, max));
		dist = dr.model;
		parameters = dr.parameters;
	}

	Vector* newve = new Vector(dv);
	newve->setModel(dist, parameters, m);
	
	emit setGenerated(newve);
}

void SetGeneratorDialog::distributionSelected(int model) {
	if (parametersWidget != nullptr)
		parametersLayout->removeWidget(parametersWidget);
	delete parametersWidget;
	QStringList p;
	for (auto const& x : ss::Vector::Distribution::parameterName[model+1]) {
		p.push_back(QString::fromStdString(x));
	}
	
	parametersWidget = new ParametersWidget(p, params, enabled);
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

void SetGeneratorDialog::vectorDeletedHandler(Vector* vectorEntry) {
	if (ve == vectorEntry)
		this->close();
}
