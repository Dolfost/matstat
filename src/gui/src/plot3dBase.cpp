#include <plot3dBase.hpp>

Plot3dBase::Plot3dBase(ss::VectorPair* v) {
	s_vector = v;
	s_series = new QSurface3DSeries;
	addSeries(s_series);
	axisX()->setTitleVisible(true);
	axisY()->setTitleVisible(true);
	axisZ()->setTitleVisible(true);
}
