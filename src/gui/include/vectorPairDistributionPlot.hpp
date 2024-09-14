#ifndef _VECTROR_PAIR_DISTRIBUTION_PLOT_HPP_
#define _VECTROR_PAIR_DISTRIBUTION_PLOT_HPP_

#include<vectorPairDensityPlot.hpp>
#include<qcustomplot.h>

class VectorPairDistributionPlot: public VectorPairDensityPlot {
public:
	VectorPairDistributionPlot(ss::VectorPair* vp, QWidget* p = nullptr)
	: VectorPairDensityPlot(vp, p) {
		map->setGradient(QCPColorGradient::gpCold);
		ser = &v_pair->cs.cumSeries();
		map->setName("Розподіл");
	};
	using VectorPairDensityPlot::fill;
};

#endif // !_VECTROR_PAIR_DISTRIBUTION_PLOT_HPP_
