#include <densityDialog.hpp>

DensityDialog::DensityDialog(Vector* v, 
																			 QWidget* w, 
																			 Qt::WindowFlags f) :
	PlotDialog(new DensityChart(v->vector()), v, w, f) {
	p_plot->setSaveFilename("2d-density");
	setWindowTitle("Щільність вектора " + v_vector->name());
	p_plot->fill();
}
