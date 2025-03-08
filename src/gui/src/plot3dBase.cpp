#include <plot3dBase.hpp>

#include <QVBoxLayout>

Plot3dBase::Plot3dBase(ss::VectorPair* v) {
	s_vector = v;
	setLayout(new QVBoxLayout);
}
