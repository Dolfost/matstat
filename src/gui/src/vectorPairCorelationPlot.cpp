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

	QPen pen;
	pen.setColor(Qt::red);
	pen.setWidthF(2);
	regression = new QCPGraph(xAxis, yAxis);
	regression->setName("Регресія");
	regression->setPen(pen);

	pen.setColor(Qt::gray);
	pen.setWidthF(1.5);
	tolerance = new QCPGraph(xAxis, yAxis);
	tolerance->setName("Тол. межі");
	tolerance->setPen(pen);

	pen.setColor(Qt::yellow);
	pen.setWidthF(1.8);
	confidence = new QCPGraph(xAxis, yAxis);
	confidence->setName("Дов. інтервал");
	confidence->setPen(pen);

	pen.setColor(Qt::magenta);
	pen.setWidthF(1.5);
	pen.setDashPattern({3, 5});
	forecast = new QCPGraph(xAxis, yAxis);
	forecast->setName("Передбачення");
	forecast->setPen(pen);
}

void VectoPairCorelationPlot::fill() {
	cor->setData(
		QList<double>(v_pair->x.begin(), v_pair->x.end()), 
		QList<double>(v_pair->y.begin(), v_pair->y.end())
	);

	if (v_pair->reg.model != ss::VectorPair::Regression::Model::Unknown) {
		double step = v_pair->x.len()/300;
		QList<double> x, r, tl, tu, cl, cu, fl, fu;
		for (int i = 0; i <= 300; i++) {
			double s = v_pair->x.min() + i*step;
			x.push_back(s);
			r.push_back(v_pair->reg.regression(s));
			std::pair<double, double> p;
			p = v_pair->reg.tolerance(s);
			tl.push_back(p.first), tu.push_back(p.second);
			p = v_pair->reg.confidence(s);
			cl.push_back(p.first), cu.push_back(p.second);
			p = v_pair->reg.forecast(s);
			fl.push_back(p.first), fu.push_back(p.second);
		}
		regression->setData(x, r, true);

		x.push_back(qQNaN());
		x.append(x);
		x.pop_back();
		tl.push_back(qQNaN());
		tl.append(tu);
		cl.push_back(qQNaN());
		cl.append(cu);
		fl.push_back(qQNaN());
		fl.append(fu);

		tolerance->setData(x, tl, true);
		confidence->setData(x, cl, true);
		forecast->setData(x, fl, true);
	} else {
		regression->data()->clear();
		tolerance->data()->clear();
		confidence->data()->clear();
		forecast->data()->clear();
	}

	VectorPairPlotBase::fill();
}

void VectoPairCorelationPlot::setAdaptiveSampling(bool state) {
	cor->setAdaptiveSampling(state);
	replot();
}
