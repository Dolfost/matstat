#include <vectorPairDensityPlot3d.hpp>


void VectorPair3dDensity::fill() {
	QSurfaceDataRow data;
	QSurfaceDataArray dataArray;

	static const std::size_t n = 500;

	double stepX = s_vector->x.size()/(double)n;
	double stepY = s_vector->y.size()/(double)n;

	for (std::size_t x = 0; x < n; x++)
		for (std::size_t y = 0; y < n; y++) {
			data << QSurfaceDataItem(
				x, y,
				s_vector->dist.pdf(x, y)
			);
		}

	dataArray << data;
	s_series->dataProxy()->resetArray(dataArray);
}
