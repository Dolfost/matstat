#include <densityDialog.hpp>

DensityDialog::DensityDialog(VectorEntry* v, 
																			 QWidget* w, 
																			 Qt::WindowFlags f) :
	VectorDialog(v, w, f) {
	d_chart = new DensityChart;
	v_mainLayout->addWidget(d_chart);
	setWindowTitle("Щільність вектора " + v_vector->name);
	fill();
}

void DensityDialog::fill() {
	d_chart->fill(v_vector->vector);
}
