#include <distributionDialog.hpp>

DistributionDialog::DistributionDialog(
	Vector* v, 
	QWidget* w, 
	Qt::WindowFlags f) 
: PlotDialog(new DistributionChart(v->vector()), v, w, f) {
	p_plot->setSaveFilename("distribution");
	setWindowTitle("Розподіл вектора " + v_vector->name());
	p_plot->fill();
}
