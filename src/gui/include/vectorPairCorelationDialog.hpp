#ifndef _VECTOR_PAIR_CORELATION_DIALOG_HPP_
#define _VECTOR_PAIR_CORELATION_DIALOG_HPP_

#include<plotDialogBase.hpp>
#include<vectorPairCorelationPlot.hpp>

class VectorPairCorelationDialog: public PlotDialogBase {
public:
	VectorPairCorelationDialog(
		VectorPair* vp, 
		QWidget* p = nullptr,
		Qt::WindowFlags f = Qt::WindowFlags()
	): PlotDialogBase(new VectoPairCorelationPlot(vp->vectorPair()), vp, p, f) {
		setWindowTitle("Кореляційне поле вектора " + vp->name());
		p_plot->setSaveFilename("2d-corelation");
	}
};

#endif // !_VECTOR_PAIR_CORELATION_DIALOG_HPP_
