#include "vectorTrimmerDialog.hpp"
#include <QGridLayout>
#include <QtCore/qlogging.h>
#include <QtWidgets/qboxlayout.h>

int VectorTrimmerDialog::trimIdx = 0;

VectorTrimmerDialog::VectorTrimmerDialog(
		VectorEntry* vectorEntry,
		QWidget *parent, Qt::WindowFlags f) 
	: QDialog(parent, f) {
		ve = vectorEntry;

		this->setWindowTitle("Менеджер обрізань " + ve->name);
		this->setAttribute(Qt::WA_DeleteOnClose, true);
		QVBoxLayout* mainLayout = new QVBoxLayout();
		mainLayout->setContentsMargins(0,0,0,0);
		mainLayout->setSpacing(0);
		this->setLayout(mainLayout);
		QVBoxLayout* uiLayout = new QVBoxLayout();
		uiLayout->setContentsMargins(10,10,10,10);
		uiLayout->setSpacing(8);
		mainLayout->addLayout(uiLayout);

		interval = std::abs(ve->vector->max()-ve->vector->min());
		double
			high = ve->vector->min() + interval*0.9,
			low = ve->vector->min() + interval*0.1;

		glow = low, ghigh = high;

		minSpinBox = new QDoubleSpinBox();
		minSpinBox->setRange(ve->vector->min(), ve->vector->max());
		minSpinBox->setSingleStep(interval/1000);
		minSpinBox->setValue(low);
		minSpinBox->setMinimumWidth(200);
		minSpinBox->setDecimals(5);
		maxSpinBox = new QDoubleSpinBox();
		maxSpinBox->setRange(ve->vector->min(), ve->vector->max());
		maxSpinBox->setSingleStep(interval/100);
		maxSpinBox->setMinimumWidth(200);
		maxSpinBox->setValue(high);
		maxSpinBox->setDecimals(5);

		QGridLayout* inputGrid = new QGridLayout();
		QLabel* xMinLabel = new QLabel(QString::number(ve->vector->min()) + " ≤ xₘᵢₙ");
		xMinLabel->setStyleSheet("font: 20pt;");
		QLabel* xMaxLabel = new QLabel("xₘₐₓ ≤ " + QString::number(ve->vector->max()));
		xMaxLabel->setStyleSheet("font: 20pt;");
		inputGrid->addWidget(xMinLabel, 0, 0, Qt::AlignCenter);
		inputGrid->addWidget(xMaxLabel, 0, 1, Qt::AlignCenter);
		inputGrid->addWidget(minSpinBox, 1, 0, Qt::AlignCenter);
		inputGrid->addWidget(maxSpinBox, 1, 1, Qt::AlignCenter);

		slider = new QDoubleRangeSlider();
		slider->setFixedHeight(40);
		slider->SetHeadRatio(0.1);
		slider->SetTailRatio(0.9);

		trimButton = new QPushButton("Обрізати");

		uiLayout->addLayout(inputGrid);
		uiLayout->addWidget(slider);
		uiLayout->addWidget(trimButton);

		statusBar = new QStatusBar();
		mainLayout->addWidget(statusBar);
		statusBar->show();

		connect(minSpinBox, &QDoubleSpinBox::valueChanged,
				this, &VectorTrimmerDialog::lowChanged); 
		connect(maxSpinBox, &QDoubleSpinBox::valueChanged,
				this, &VectorTrimmerDialog::highChanged); 
		connect(slider, &QDoubleRangeSlider::onRangeChanged,
				this, &VectorTrimmerDialog::boundsChanged);

		connect(trimButton, &QPushButton::pressed,
				this, &VectorTrimmerDialog::trim);

		boundsChanged(0, 0, glow, ghigh);

		this->adjustSize();
		this->show();
}

void VectorTrimmerDialog::trim() {
	VectorEntry* newEntry = new VectorEntry(new DataVector(ve->vector->vector()));
	size_t delta = newEntry->vector->trim(glow, ghigh);
	newEntry->name = "TRIM" + QString::number(++trimIdx) + "(" + ve->name + ")";

	emit vectorTrimmed(newEntry);

	statusBar->showMessage(QString(
				"N = %1 → N = %2 (ΔN = %3)")
			.arg(ve->vector->size())
			.arg(newEntry->vector->size())
			.arg(delta));
}

void VectorTrimmerDialog::lowChanged(double low) {
	boundsChanged(0, 0, low, ghigh);
}

void VectorTrimmerDialog::highChanged(double high) {
	boundsChanged(0, 0, glow, high);
}

void VectorTrimmerDialog::boundsChanged(int type, int b, double low, double high) {
	if (type != QDoubleRangeSlider::MoveType::None) {
		low = ve->vector->min() + low*interval;
		high = ve->vector->min() + high*interval;
	}

	if (low >= ghigh) {
		low = glow;
	} if (high <= glow) {
		high = ghigh;
	}

	ghigh = high;
	glow = low;

	minSpinBox->setValue(low);
	maxSpinBox->setValue(high);
	slider->SetHeadRatio(abs(low - ve->vector->min())/interval);
	slider->SetTailRatio(abs(high - ve->vector->min())/interval);
};

void VectorTrimmerDialog::vectorDeletedHandler(VectorEntry* vectorEntry) {
	if (ve == vectorEntry)
		this->close();
}
