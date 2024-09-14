#ifndef _VECTOR_PAIR_CORELATION_PLOT_HPP_
#define _VECTOR_PAIR_CORELATION_PLOT_HPP_

#include<vectorPairPlotBase.hpp>

class VectoPairCorelationPlot: public VectorPairPlotBase {
public:
	VectoPairCorelationPlot(ss::VectorPair*, QWidget* = nullptr);

public slots:
	virtual void fill() override;

protected:
	QCPGraph* cor = nullptr;
	QCPScatterStyle corScatter;
	QPen scatterPen;
};

#endif // !_VECTOR_PAIR_CORELATION_PLOT_HPP_
