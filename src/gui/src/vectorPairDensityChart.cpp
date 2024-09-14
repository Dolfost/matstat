#include<vectorPairDensityChart.hpp>

VectorPairDensityChart::VectorPairDensityChart(
	ss::VectorPair* v, QWidget* p): VectorPairPlotBase(v, p) {
	map = new QCPColorMap(xAxis, yAxis);
	map->setName("Щільність");
	map->setInterpolate(false);
	map->setGradient(QCPColorGradient::gpJet);

	scale = new QCPColorScale(this);
	QCPMarginGroup *group = new QCPMarginGroup(this);
	scale->setMarginGroup(QCP::msTop | QCP::msBottom, group);
	scale->axis()->ticker()->setTickCount(9);
	plotLayout()->addElement(0, 1, scale);
	axisRect()->setMarginGroup(QCP::msTop|QCP::msBottom, group);
}

void VectorPairDensityChart::fill() {
	ss::Vector &x = v_pair->x, &y = v_pair->y;
	ss::VectorPair::ClassSeries& cs = v_pair->cs;

	map->setDataRange({0, cs.maxProb()});
	map->data()->setSize(
		cs.countX(), cs.countY()
	);
	map->data()->setRange(
		QCPRange(x.min() + cs.stepX()/2, x.max() - cs.stepX()/2), 
		QCPRange(y.min() + cs.stepY()/2, y.max() - cs.stepY()/2)
	);
	for (std::size_t i = 0; i < cs.countX(); ++i)
		for (std::size_t j = 0; j < cs.countY(); ++j) {
			map->data()->setCell(i, j, cs.series()[i][j].second);
		}

	scale->setGradient(map->gradient());
	scale->setDataRange(map->dataRange());

	VectorPairPlotBase::fill();
}

void VectorPairDensityChart::interpolate(bool state) {
	map->setInterpolate(state);
	replot();
}
