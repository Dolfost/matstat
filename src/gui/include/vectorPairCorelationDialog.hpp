#ifndef _VECTOR_PAIR_CORELATION_DIALOG_HPP_
#define _VECTOR_PAIR_CORELATION_DIALOG_HPP_

#include<plot2dDialogBase.hpp>
#include<vectorPairCorelationPlot.hpp>

class VectorPairCorelationDialog: public Plot2dDialogBase {
public:
	VectorPairCorelationDialog(
		VectorPair* vp, 
		QWidget* p = nullptr,
		Qt::WindowFlags f = Qt::WindowFlags()
	): Plot2dDialogBase(new VectoPairCorelationPlot(vp->vectorPair()), vp, p, f) {
		setWindowTitle("Кореляційне поле вектора " + vp->name());
		p_plot->setSaveFilename("2d-corelation");

		QAction* adaptiveSamling = p_viewMenu->addAction("Адаптивне семплування");
		adaptiveSamling->setCheckable(true);
		connect(
			adaptiveSamling, 
			&QAction::triggered,
			dynamic_cast<VectoPairCorelationPlot*>(p_plot), 
			&VectoPairCorelationPlot::setAdaptiveSampling
		);
	}
};

#endif // !_VECTOR_PAIR_CORELATION_DIALOG_HPP_
