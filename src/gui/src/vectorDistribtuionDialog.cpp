#include <vectorDistributionDialog.hpp>

VectorDistributionDialog::VectorDistributionDialog(
	Vector* v, 
	QWidget* w, 
	Qt::WindowFlags f) 
: PlotDialog(new VectorDistributionPlot(v->vector()), v, w, f) {
	p_plot->setSaveFilename("distribution");
	setWindowTitle("Розподіл вектора " + v_vector->name());
	p_plot->fill();
}
