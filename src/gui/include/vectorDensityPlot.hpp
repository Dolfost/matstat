#ifndef _DENSITY_CHART_HPP_
#define _DENSITY_CHART_HPP_

#include "vectorPlotBase.hpp"

class VectorDensityPlot : public VectorPlotBase {
	Q_OBJECT
public:
    VectorDensityPlot(ss::Vector*, QWidget* parent = nullptr);
	QCPBars* bars = nullptr;
	QCPGraph* density = nullptr;

public slots:
	virtual void fill() override;
};

#endif // !_DENSITY_CHART_HPP_
