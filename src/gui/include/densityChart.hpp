#ifndef _DENSITY_CHART_HPP_
#define _DENSITY_CHART_HPP_

#include "plotBase.hpp"

class DensityChart : public PlotBase {
	Q_OBJECT
public:
    DensityChart(QWidget* parent = nullptr);
	QCPBars* bars = nullptr;
	QCPGraph* density = nullptr;

	virtual void fill(ss::Vector*) override;
};

#endif // !_DENSITY_CHART_HPP_
