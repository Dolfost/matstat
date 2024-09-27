#include <vectorPairPlot3dBase.hpp>

VectorPair3dPlotBase::VectorPair3dPlotBase(ss::VectorPair* v) {
	s_vector = v;
	s_series = new QSurface3DSeries;
	addSeries(s_series);
}
