#ifndef _PLOT_3D_BASE_HPP
#define _PLOT_3D_BASE_HPP

#include <Q3DSurface>

#include "vectorPair.hpp"

class Plot3dBase: public Q3DSurface {
public:
	Plot3dBase(ss::VectorPair*);

	ss::VectorPair* vector() { return s_vector; };
	void setVector(ss::VectorPair* v) { s_vector = v; };

public slots:
	virtual void fill() = 0;

protected:
	ss::VectorPair* s_vector = nullptr;

	QSurface3DSeries* s_series = nullptr;
};

#endif // !_PLOT_3D_BASE_HPP
