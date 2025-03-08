#include <vectorPairDensityPlot3d.hpp>

#include <QVBoxLayout>

VectorPairDensityPlot3d::VectorPairDensityPlot3d(
	ss::VectorPair* v
): Plot3dBase(v) {
	auto series = new QSurface3DSeries;
	s_series = series;
	auto surface = new Q3DSurface;
	s_graph = surface;
	layout()->addWidget(QWidget::createWindowContainer(s_graph));
	surface->addSeries(series);
	surface->axisX()->setTitleVisible(true);
	surface->axisY()->setTitleVisible(true);
	surface->axisZ()->setTitleVisible(true);
	surface->axisX()->setTitle(QStringLiteral("X"));
	surface->axisY()->setTitle(QStringLiteral("f(x)"));
	surface->axisZ()->setTitle(QStringLiteral("Y"));

	surface->axisX()->setSegmentCount(
		15
	);
	surface->axisZ()->setSegmentCount(
		15
	);
	surface->axisY()->setSegmentCount(
		15
	);
}

void VectorPairDensityPlot3d::fill() {
	auto dataArray = new QSurfaceDataArray ;

	static const std::size_t n = 100;

	double stepX = s_vector->x.len()/(double)(n-1);
	double stepY = s_vector->y.len()/(double)(n-1);

	dataArray->reserve(n);
	for (int i = 0 ; i < n ; i++) {
		auto newRow = new QSurfaceDataRow(n);
		double z = qMin(s_vector->y.max(), s_vector->y.min() + i*stepY);
		int index = 0;
		for (int j = 0; j < n; j++) {
			double x = qMin(s_vector->x.max(), s_vector->x.min() + j*stepX);
			(*newRow)[index++].setPosition(
				QVector3D(
					x,
					s_vector->dist.pdf(x, z),
					z 
				)
			);
		}
		(*dataArray) << newRow;
	}


	static_cast<QSurface3DSeries*>(s_series)->dataProxy()->resetArray(dataArray);
}
