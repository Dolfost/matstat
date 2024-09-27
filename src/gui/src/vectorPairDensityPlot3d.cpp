#include <vectorPairDensityPlot3d.hpp>

VectorPairDensityPlot3d::VectorPairDensityPlot3d(
	ss::VectorPair* v
): Plot3dBase(v) {
	axisX()->setTitle(QStringLiteral("X"));
	axisY()->setTitle(QStringLiteral("f(x)"));
	axisZ()->setTitle(QStringLiteral("Y"));
}

void VectorPairDensityPlot3d::fill() {
	QSurfaceDataArray dataArray;

	static const std::size_t n = 100;

	double stepX = s_vector->x.len()/(double)(n-1);
	double stepY = s_vector->y.len()/(double)(n-1);

	dataArray.reserve(n);
	for (int i = 0 ; i < n ; i++) {
		QSurfaceDataRow newRow = QSurfaceDataRow(n);
		double z = qMin(s_vector->y.max(), s_vector->y.min() + i*stepY);
		int index = 0;
		for (int j = 0; j < n; j++) {
			double x = qMin(s_vector->x.max(), s_vector->x.min() + j*stepX);
			newRow[index++].setPosition(
				QVector3D(
					x,
					s_vector->dist.pdf(x, z),
					z 
				)
			);
		}
		dataArray << newRow;
	}

	s_series->dataProxy()->resetArray(dataArray);
}
