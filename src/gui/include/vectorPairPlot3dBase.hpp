#ifndef _VECTOR_PAIR_3D_PLOT_
#define _VECTOR_PAIR_3D_PLOT_

#include <Q3DSurface>

#include "vectorPair.hpp"

class VectorPair3dPlotBase: Q3DSurface {
public:
	VectorPair3dPlotBase(ss::VectorPair*);

	ss::VectorPair* vector() { return s_vector; };
	void setVector(ss::VectorPair* v) { s_vector = v; };

public slots:
	virtual void fill() = 0;

protected:
	ss::VectorPair* s_vector = nullptr;

	QSurface3DSeries* s_series = nullptr;
};

#endif // !_VECTOR_PAIR_3D_PLOT_
