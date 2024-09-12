#include <distributionDialog.hpp>

DistributionDialog::DistributionDialog(VectorEntry* v, 
																			 QWidget* w, 
																			 Qt::WindowFlags f) :
	PlotDialog(new DistributionChart, v, w, f) {
	p_plot->setSaveFilename("distribution");
	setWindowTitle("Розподіл вектора " + v_vector->name);
	fill();
}
