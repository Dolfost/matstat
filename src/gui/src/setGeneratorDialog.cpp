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
		sb->setRange(-1000, 1000);
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
	QWidget *parent, bool show, Qt::WindowFlags f) 
: DialogBase(parent, f) {
	this->setWindowTitle("Генератор вибірок");
	tabs = new QTabWidget;
	v_mainLayout->addWidget(tabs);
	v_mainLayout->setSpacing(5);

	setVectorTab();
	setVectorPairTab();

	generateButton = new QPushButton("Генерувати");
	connect(generateButton, &QPushButton::clicked,
				 this, &SetGeneratorDialog::generateHandler);
	QGridLayout* genLay = new QGridLayout;
	genLay->addWidget(new QLabel("Розмір вибірки"), 0, 0);
	genLay->setContentsMargins(5, 0, 5, 0);
	countSpinBox = new QSpinBox;
	countSpinBox->setRange(2, INT_MAX);
	countSpinBox->setValue(500);
	genLay->addWidget(countSpinBox, 0, 1);
	genLay->addWidget(generateButton, 0, 2);
	v_mainLayout->addLayout(genLay);

	statusBar = new QStatusBar();
	statusBar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	statusBar->setContentsMargins(0,0,0,0);
	v_mainLayout->addWidget(statusBar);

	this->adjustSize();
	this->resize(500, this->height());

	if (show)
		this->show();
}
void SetGeneratorDialog::setVectorPairTab() {
	vectorPairTab = new QWidget;
	tabs->addTab(vectorPairTab, "Двовимірні");

	QVBoxLayout* layout = new QVBoxLayout;
	layout->setContentsMargins(10,10,10,0);
	vectorPairTab->setLayout(layout);

	QGroupBox* parametersBox = new QGroupBox("Модель");
	parametersBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	vectorPairParametersLayout = new QVBoxLayout;
	vectorPairParametersLayout->setContentsMargins(1,1,1,1);
	parametersBox->setLayout(vectorPairParametersLayout);

	vectorPairModelComboBox = new QComboBox;
	vectorPairModelComboBox->addItems({"Нормальний розподіл"});
	for (int i = 1; i < (int)ss::VectorPair::Regression::Model::Count; i++) {
		vectorPairModelComboBox->insertItem(
			i,
			QString::fromStdString(ss::VectorPair::Regression::regressionName[i])
		);
	}
	connect(vectorPairModelComboBox, &QComboBox::currentIndexChanged,
				 this, &SetGeneratorDialog::vectorPairModelSelected);
	vectorPairParametersLayout->addWidget(vectorPairModelComboBox);

	layout->addWidget(parametersBox);

	vectorPairModelSelected(vectorPairModelComboBox->currentIndex());
}

void SetGeneratorDialog::setVectorTab() {
	vectorTab = new QWidget;
	tabs->addTab(vectorTab, "Одновимріні");

	QVBoxLayout* layout = new QVBoxLayout;
	layout->setContentsMargins(10,10,10,0);
	vectorTab->setLayout(layout);

	vectorDistributionComboBox = new QComboBox();
	for (int i = 1; i < (int)ss::Vector::Distribution::Model::Count; i++) {
		vectorDistributionComboBox->insertItem(
			i,
			QString::fromStdString(ss::Vector::Distribution::distributionName[i])
		);
	}
	QGroupBox* distributionBox = new QGroupBox("Розподіл");
	distributionBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QVBoxLayout* distributionLayout = new QVBoxLayout;
	distributionLayout->setContentsMargins(1,1,1,1);
	distributionBox->setLayout(distributionLayout);
	distributionLayout->addWidget(vectorDistributionComboBox);


	vectorParametersLayout = new QVBoxLayout;
	vectorParametersLayout->setContentsMargins(1,1,1,0);

	vectorMethodComboBox = new QComboBox;
	for (int i = 0; i < (int)ss::Vector::Distribution::Method::Count; i++) {
		vectorMethodComboBox->insertItem(i,
																	 QString::fromStdString(ss::Vector::Distribution::methodName[i]));
	}

	QGroupBox* methodBox = new QGroupBox("Метод відтворення");
	methodBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	QVBoxLayout* methodLayout = new QVBoxLayout;
	methodLayout->setContentsMargins(1,1,1,0);
	methodBox->setLayout(methodLayout);
	methodLayout->addWidget(vectorMethodComboBox);

	vectorBoundsBox = new QGroupBox("Межі реалізаці випадкової величини");
	QHBoxLayout* boundsLayout = new QHBoxLayout;
	boundsLayout->setContentsMargins(1,1,1,0);
	vectorBoundsBox->setLayout(boundsLayout);
	vectorMinSpinBox = new QDoubleSpinBox();
	vectorMinSpinBox->setMinimum(INT_MIN);
	vectorMinSpinBox->setDecimals(precision);
	vectorMaxSpinBox = new QDoubleSpinBox();
	vectorMaxSpinBox->setMaximum(INT_MAX);
	vectorMaxSpinBox->setDecimals(precision);
	boundsLayout->addWidget(vectorMinSpinBox);
	boundsLayout->addWidget(vectorMaxSpinBox);

	distributionLayout->addLayout(vectorParametersLayout);
	layout->addWidget(distributionBox);
	layout->addWidget(vectorBoundsBox);
	layout->addWidget(methodBox);

	connect(vectorDistributionComboBox, &QComboBox::currentIndexChanged,
				 this, &SetGeneratorDialog::vectorDistributionSelected);

	connect(vectorMethodComboBox, &QComboBox::currentIndexChanged,
				 this, &SetGeneratorDialog::vectorMethodSelected);

	connect(vectorMinSpinBox, &QDoubleSpinBox::valueChanged,
				 this, &SetGeneratorDialog::vectorMinBoundChanged);
	connect(vectorMaxSpinBox, &QDoubleSpinBox::valueChanged,
				 this, &SetGeneratorDialog::vectorMaxBoundChanged);

	vectorDistributionSelected(vectorDistributionComboBox->currentIndex());
	vectorMethodSelected(vectorMethodComboBox->currentIndex());
}

void SetGeneratorDialog::generateVector() {
	ss::Vector* dv;
	ss::Vector::Distribution::Method m =
		ss::Vector::Distribution::Method(vectorMethodComboBox->currentIndex());
	size_t count = countSpinBox->value();
	double
	min = vectorMinSpinBox->value(),
	max = vectorMaxSpinBox->value();

	ss::Vector::Distribution::Model dist;
	std::vector<double> parameters;

	ss::Vector::Distribution dr;
	dr.setModel(ss::Vector::Distribution::Model(vectorDistributionComboBox->currentIndex()+1),
										vectorParametersWidget->parameters(), count);
	dv = new ss::Vector(dr.generateSet(m, count, min, max));
	dist = dr.model;
	parameters = dr.parameters;

	Vector* newve = new Vector(dv);
	newve->setDistribuitonModel(dist, parameters, m);

	emit vectorGenerated(newve);
}

void SetGeneratorDialog::generateVectorPair() {
	ss::VectorPair* dv;
	size_t count = countSpinBox->value();
	std::vector<double> parameters;
	std::vector<double> p = vectorPairParametersWidget->parameters();
	int idx = vectorPairModelComboBox->currentIndex();
	std::pair<std::list<double>, std::list<double>> set;

	if (idx == 0) {
		ss::VectorPair::Distribution dr(nullptr);
		dr.setParameters(p, count);
		std::pair<std::list<double>, std::list<double>> set = dr.generateSet(count);
		dv = new ss::VectorPair(std::move(set.first), std::move(set.second));
		parameters = dr.parameters;
	} else {
		ss::VectorPair::Regression rr(nullptr);
		double xmax = p.back();
		p.pop_back();
		double xmin = p.back();
		p.pop_back();
		double sigma = p.back();
		p.pop_back();
		rr.setModel(ss::VectorPair::Regression::Model(idx), p);
		set = rr.generateSet(count, xmin, xmax, sigma);
		parameters = rr.parameters;
	}

	dv = new ss::VectorPair(std::move(set.first), std::move(set.second));
	VectorPair* newve = new VectorPair;
	newve->setVectorPair(dv);
	newve->setDistribuitonParameters(p);
	newve->setNormalDistribution(true);

	emit vectorPairGenerated(newve);
}

void SetGeneratorDialog::generateHandler() {
	switch (tabs->currentIndex()) {
		case 0: {
			generateVector();
			break;
		}
		case 1: {
			generateVectorPair();
			break;
		}
	}
}

void SetGeneratorDialog::vectorDistributionSelected(int model) {
	if (vectorParametersWidget != nullptr)
		vectorParametersLayout->removeWidget(vectorParametersWidget);
	delete vectorParametersWidget;
	QStringList p;
	for (auto const& x : ss::Vector::Distribution::parameterName[model+1]) {
		p.push_back(QString::fromStdString(x));
	}

	vectorParametersWidget = new ParametersWidget(p, params, enabled);
	vectorParametersLayout->addWidget(vectorParametersWidget);
}

void SetGeneratorDialog::vectorPairModelSelected(int model) {
	if (vectorPairParametersWidget != nullptr)
		vectorPairParametersLayout->removeWidget(vectorPairParametersWidget);
	delete vectorPairParametersWidget;
	QStringList p;
	if (model == 0)
		for (auto const& x : ss::VectorPair::Distribution::parameterName[0])
			p.push_back(QString::fromStdString(x));
	else  {
		for (auto const& x : ss::VectorPair::Regression::parameterName[model])
			p.push_back(QString::fromStdString(x));
		p.push_back("σ");
		p.push_back("xₘᵢₙ");
		p.push_back("xₘₐₓ");
	}

	vectorPairParametersWidget = new ParametersWidget(p, params, enabled);
	vectorPairParametersLayout->addWidget(vectorPairParametersWidget);
}

void SetGeneratorDialog::vectorMethodSelected(int method) {
	vectorBoundsBox->setVisible(method);
}

void SetGeneratorDialog::vectorMinBoundChanged(double val) {
	vectorMinSpinBox->blockSignals(true);
	vectorMaxSpinBox->blockSignals(true);

	vectorMaxSpinBox->setMinimum(val+0.001);

	vectorMinSpinBox->blockSignals(false);
	vectorMaxSpinBox->blockSignals(false);
}

void SetGeneratorDialog::vectorMaxBoundChanged(double val) {
	vectorMinSpinBox->blockSignals(true);
	vectorMaxSpinBox->blockSignals(true);

	vectorMinSpinBox->setMaximum(val-0.001);

	vectorMinSpinBox->blockSignals(false);
	vectorMaxSpinBox->blockSignals(false);
}
