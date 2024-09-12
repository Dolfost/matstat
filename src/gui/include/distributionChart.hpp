#ifndef _DISTRIBUTION_CHART_HPP_
#define _DISTRIBUTION_CHART_HPP_

#include "plotBase.hpp"

class DistributionChart : public PlotBase {
	Q_OBJECT
public:
    DistributionChart(QWidget* parent = nullptr);

	QCPGraph* graph = nullptr;
	QCPGraph* distribution = nullptr;
	QCPGraph* distributionDeviation = nullptr;

	virtual void fill(ss::Vector*) override;
};

#endif // !_DISTRIBUTION_CHART_HPP_
