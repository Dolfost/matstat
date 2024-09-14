#ifndef _VECTOR_PAIR_CORELATION_DIALOG_HPP_
#define _VECTOR_PAIR_CORELATION_DIALOG_HPP_

#include<plotDialog.hpp>
#include<vectorPairCorelationPlot.hpp>

class VectorPairCorelationDialog: public PlotDialog {
public:
	VectorPairCorelationDialog(
		VectorPair* vp, 
		QWidget* p = nullptr,
		Qt::WindowFlags f = Qt::WindowFlags()
	): PlotDialog(new VectoPairCorelationPlot(vp->vectorPair()), vp, p, f) {
		setWindowTitle("Кореляційне поле вектора " + vp->name());
		p_plot->setSaveFilename("2d-corelation");
	}
};

#endif // !_VECTOR_PAIR_CORELATION_DIALOG_HPP_
