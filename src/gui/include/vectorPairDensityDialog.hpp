#ifndef _VECTOR_PAIR_DENSITY_DIALOG_HPP_
#define _VECTOR_PAIR_DENSITY_DIALOG_HPP_

#include<plotDialog.hpp>
#include<vectorPairDensityChart.hpp>
#include<vectorPair.hpp>

class VectorPairDensityDialog: public PlotDialog {
public:
	VectorPairDensityDialog(
		VectorPair* v,
		QWidget* p = nullptr,
		Qt::WindowFlags f = Qt::WindowFlags())
	: PlotDialog(new VectorPairDensityChart(v->vectorPair()), v, p, f) {
		p_plot->setSaveFilename("distribution");
		setWindowTitle("Розподіл двовимірного вектора " + v_vector->name());
		p_plot->fill();

		QAction* interpolate = p_viewMenu->addAction("Інтерполяція");
		interpolate->setCheckable(true);
		connect(interpolate, &QAction::triggered,
					static_cast<VectorPairDensityChart*>(p_plot) , &VectorPairDensityChart::interpolate);
	}

protected:

};

#endif // !_VECTOR_PAIR_DENSITY_DIALOG_HPP_
