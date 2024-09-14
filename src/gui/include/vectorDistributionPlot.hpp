#ifndef _DISTRIBUTION_CHART_HPP_
#define _DISTRIBUTION_CHART_HPP_

#include "vectorPlotBase.hpp"

class VectorDistributionPlot : public VectorPlotBase {
	Q_OBJECT
public:
    VectorDistributionPlot(ss::Vector*, QWidget* parent = nullptr);

	QCPGraph* graph = nullptr;
	QCPGraph* distribution = nullptr;
	QCPGraph* distributionDeviation = nullptr;

public slots:
	virtual void fill() override;
};

#endif // !_DISTRIBUTION_CHART_HPP_
