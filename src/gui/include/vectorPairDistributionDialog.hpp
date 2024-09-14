#ifndef _VECTOR_PAIR_DISTRIBUTION_DIALOG_HPP_
#define _VECTOR_PAIR_DISTRIBUTION_DIALOG_HPP_

#include<plotDialogBase.hpp>
#include<vectorPairDistributionPlot.hpp>

class VectorPairDistributionDialog: public PlotDialogBase {
public:
	VectorPairDistributionDialog(
		VectorPair* v,
		QWidget* p = nullptr,
		Qt::WindowFlags f = Qt::WindowFlags())
	: PlotDialogBase(new VectorPairDistributionPlot(v->vectorPair()), v, p, f) {
		p_plot->setSaveFilename("distribution");
		setWindowTitle("Розподіл двовимірного вектора " + v_vector->name());

		QAction* interpolate = p_viewMenu->addAction("Інтерполяція");
		interpolate->setCheckable(true);
		connect(interpolate, &QAction::triggered,
					static_cast<VectorPairDensityPlot*>(p_plot) , &VectorPairDensityPlot::interpolate);
	}

protected:

};

#endif // !_VECTOR_PAIR_DISTRIBUTION_DIALOG_HPP_
