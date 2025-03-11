#ifndef _VECTOR_CHAIN_FILED_PLOT_3D_HPP_
#define _VECTOR_CHAIN_FILED_PLOT_3D_HPP_

#include <plot3dBase.hpp>

class VectorChainFieldPlot3d: public Plot3dBase {
public:
	VectorChainFieldPlot3d(ss::VectorChain*);
	virtual void fill() override;
};

#endif // !_VECTOR_PAIR_DENSITY_PLOT_3D_HPP_
