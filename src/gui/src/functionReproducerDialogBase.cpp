#include <functionReproducerDialogBase.hpp>

FunctionReproducerDialogBase::FunctionReproducerDialogBase(
	VectorEntry* vectorEntry,
	QWidget *parent, Qt::WindowFlags f) 
: VectorEntryDialogBase(vectorEntry, parent, f) {

	connect(this->modelComboBox, &QComboBox::currentIndexChanged,
				 this, &FunctionReproducerDialogBase::distribute);

	QGridLayout* distributionLayout = new QGridLayout;
	distributionLayout->addWidget(reproductName, 0, 0);
	distributionLayout->addWidget(modelComboBox, 0, 1);

	infoWidget = new QWidget;
	infoWidget->setLayout(new QVBoxLayout());
	infoWidget->layout()->setContentsMargins(0,0,0,0);

	QGroupBox* groupBox;
	QVBoxLayout* boxLay;

	parameters->setTitle("Параметри");
	parameters->widget()->setHeaders({"Позначення", "Значення"});
	infoWidget->layout()->addWidget(parameters);

	parametersDeviation->setTitle("Відхилення");
	parametersDeviation->widget()->setHeaders({"Позначення", "Значення"});
	infoWidget->layout()->addWidget(parametersDeviation);

	v_mainLayout->addLayout(distributionLayout);
	v_mainLayout->addWidget(infoWidget);

	parametersTest->setTitle("Перевірка рівності параматрів і оцінок");
	parametersTest->layout()->addWidget(parametersTestInfoLabel);

	infoWidget->layout()->addWidget(parametersTest);

	this->resize(300, 400);
}


void FunctionReproducerDialogBase::distribute(int dist) {
	if (dist != 0) {
		fill();
		makeTtest();
		infoWidget->setVisible(true);
		this->adjustSize();
		this->resize(750, this->height());
	} else {
		infoWidget->setVisible(false);
		this->adjustSize();
	}

	emit modelSelected(v_vectorEntry);
}
