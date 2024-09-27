#ifndef _VECTOR_PAIR_DENSITY_PLOT_3D_HPP_
#define _VECTOR_PAIR_DENSITY_PLOT_3D_HPP_

#include <plot3dBase.hpp>

class VectorPairDensityPlot3d: public Plot3dBase {
public:
	VectorPairDensityPlot3d(ss::VectorPair*);
	virtual void fill() override;
};

#endif // !_VECTOR_PAIR_DENSITY_PLOT_3D_HPP_
