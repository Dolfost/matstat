#ifndef _VECTOR_PAIR_3D_DENSITY_HPP_
#define _VECTOR_PAIR_3D_DENSITY_HPP_

#include <vectorPairPlot3dBase.hpp>

class VectorPair3dDensity: VectorPair3dPlotBase {
public:
	using VectorPair3dPlotBase::VectorPair3dPlotBase;
	virtual void fill() override;
};

#endif // !_VECTOR_PAIR_3D_DENSITY_HPP_
