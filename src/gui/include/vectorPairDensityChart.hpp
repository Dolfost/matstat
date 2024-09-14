#ifndef _VECTROR_PAIR_DENSITY_CHART_HPP_
#define _VECTROR_PAIR_DENSITY_CHART_HPP_

#include<vectorPairPlotBase.hpp>
#include<qcustomplot.h>

class VectorPairDensityChart: public VectorPairPlotBase {
public:
	VectorPairDensityChart(ss::VectorPair*, QWidget* = nullptr);

public slots:
	virtual void fill() override;
	void interpolate(bool);

protected:
	QCPColorMap* map;
	QCPColorScale* scale;
};

#endif // !_VECTROR_PAIR_DENSITY_CHART_HPP_
