#ifndef _PLOT_3D_BASE_HPP
#define _PLOT_3D_BASE_HPP

#include <QWidget>
#include <Q3DSurface>

#include "vectorPair.hpp"
#include "vectorChain.hpp"

class Plot3dBase: public QWidget {
public:
	Plot3dBase(ss::VectorPair*);
	Plot3dBase(ss::VectorChain*);

	ss::VectorPair* vector() { return s_vector; };
	void setVector(ss::VectorPair* v) { s_vector = v; };

public slots:
	virtual void fill() = 0;

protected:
	ss::VectorPair* s_vector = nullptr;
	ss::VectorChain* s_vectorChain = nullptr;

	QAbstract3DGraph* s_graph = nullptr;
	QAbstract3DSeries* s_series = nullptr;
};

#endif // !_PLOT_3D_BASE_HPP
