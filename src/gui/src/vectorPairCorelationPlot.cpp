#include <vectorPairCorelationPlot.hpp>

VectoPairCorelationPlot::VectoPairCorelationPlot(
	ss::VectorPair* vp, QWidget* p): VectorPairPlotBase(vp, p) {

	cor = new QCPGraph(this->xAxis, this->yAxis);
	cor->setName("Кореляція");
	cor->setLineStyle(QCPGraph::lsNone);
	cor->setAdaptiveSampling(false);

	corScatter.setShape(QCPScatterStyle::ssCircle);
	corScatter.setSize(6);
	scatterPen.setWidthF(0.8);
	scatterPen.setColor(Qt::blue);
	corScatter.setPen(scatterPen);

	cor->setScatterStyle(corScatter);
}

void VectoPairCorelationPlot::fill() {
	cor->setData(
		QList<double>(v_pair->x.begin(), v_pair->x.end()), 
		QList<double>(v_pair->y.begin(), v_pair->y.end())
	);
	VectorPairPlotBase::fill();
}
