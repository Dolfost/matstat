#include <distributionDialog.hpp>

DistributionDialog::DistributionDialog(VectorEntry* v, 
																			 QWidget* w, 
																			 Qt::WindowFlags f) :
	VectorDialog(v, w, f) {
	d_chart = new DistributionChart;
	v_mainLayout->addWidget(d_chart);
	setWindowTitle("Розподіл вектора " + v_vector->name);
	fill();
}

void DistributionDialog::fill() {
	d_chart->fill(v_vector->vector);
}
