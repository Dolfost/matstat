#include <densityDialog.hpp>

DensityDialog::DensityDialog(Vector* v, 
																			 QWidget* w, 
																			 Qt::WindowFlags f) :
	PlotDialog(new DensityChart, v, w, f) {
	p_plot->setSaveFilename("distribution");
	setWindowTitle("Щільність вектора " + v_vector->name());
	fill();
}
