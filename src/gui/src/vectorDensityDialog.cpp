#include <vectorDensityDialog.hpp>

VectorDensityDialog::VectorDensityDialog(Vector* v, 
																			 QWidget* w, 
																			 Qt::WindowFlags f) :
	PlotDialogBase(new VectorDensityPlot(v->vector()), v, w, f) {
	p_plot->setSaveFilename("2d-density");
	setWindowTitle("Щільність вектора " + v_vector->name());
}
