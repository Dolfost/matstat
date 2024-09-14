#ifndef _VECTROR_PAIR_DENSITY_PLOT_HPP_
#define _VECTROR_PAIR_DENSITY_PLOT_HPP_

#include<vectorPairPlotBase.hpp>
#include<qcustomplot.h>

class VectorPairDensityPlot: public VectorPairPlotBase {
public:
	VectorPairDensityPlot(ss::VectorPair*, QWidget* = nullptr);

public slots:
	virtual void fill() override;
	void interpolate(bool);

protected:
	QCPColorMap* map;
	QCPColorScale* scale;
	const std::vector<std::vector<std::pair<unsigned long, double>>>* ser = &v_pair->cs.series();
};

#endif // !_VECTROR_PAIR_DENSITY_PLOT_HPP_
