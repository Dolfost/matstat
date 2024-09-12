#include "distributionChart.hpp"
#include "plotBase.hpp"

DistributionChart::DistributionChart(QWidget* parent) : PlotBase(parent) {
	graph = new QCPGraph(this->xAxis, this->yAxis);
	graph->setName("F(x) (класи)");
	QPen graphPen;
	graphPen.setWidthF(1.3);
	graphPen.setColor("#2b8eff");
	graph->setPen(graphPen);

	distribution = new QCPGraph(this->xAxis2, this->yAxis2);
	distribution->setName("F(x) (відтв.)");
	this->xAxis2->setLabel("x (відтворена)");
	QPen distributionPen;
	distributionPen.setWidthF(1.3);
	distributionPen.setColor("#0313fc");
	distribution->setPen(distributionPen);

	distributionDeviation = new QCPGraph(this->xAxis2, this->yAxis2);
	distributionDeviation->setName("СКВ F(x)");
	QPen distributionDeviationPen;
	distributionDeviationPen.setWidthF(1.1);
	distributionDeviationPen.setColor("#fc0303");
	distributionDeviationPen.setDashPattern({5, 3});
	distributionDeviation->setPen(distributionDeviationPen);

	this->yAxis2->setTickLabels(false);

	enableMed();
	enableWalshMed();

	yRange = QCPRange(0,1);
	this->yAxis->setLabel("F(x)");
}

void DistributionChart::fill(ss::Vector* dataVector) {
	dv = dataVector;
	ss::Vector::ClassSeries& cs = dataVector->cs;

	QVector<double> x, y;
	for (size_t i = 0; i < cs.count(); i++) {
		x.push_back(dataVector->min() + cs.step()*i);
		x.push_back(dataVector->min() + cs.step()*(i+1));

		y.push_back(cs.cumSeries()[i].second);
		y.push_back(cs.cumSeries()[i].second);

		x.push_back(qQNaN());
		x.push_back(qQNaN());
		y.push_back(qQNaN());
		y.push_back(qQNaN());
	}

	graph->setData(x, y, true);

	if (dataVector->dist.model != ss::Vector::Distribution::Model::Unknown) {
		if (dataVector->dist.domain.first == dataVector->dist.domain.second)
			coordinatesLabelString = "${X}\n${Y}";
		else
			coordinatesLabelString = "${X} ${X2}\n${Y}";
		x.clear(), y.clear();
		QList<double> yDev1, yDev2;

		double a, b;
		if (dataVector->dist.domain.first != dataVector->dist.domain.second) {
			a = dataVector->dist.domain.first;
			b = dataVector->dist.domain.second;
		} else {
			a = dataVector->min();
			b = dataVector->max();
		}

		double interval = abs(a - b)/2;
		for (double arg = a;
				arg <= b;
				arg += interval/350) {
			x.push_back(arg);
			y.push_back(dataVector->dist.cdf(arg));
			std::pair<double, double> dev =
				dataVector->dist.cdfConfidence(arg, dataVector->dist.confidence);
			yDev1.push_back(dev.first);
			yDev2.push_back(dev.second);
		}
		
		distribution->setData(x, y, true);

		yDev1.push_back(qQNaN());
		x.push_back(qQNaN());
		x.append(x);
		x.pop_back();
		yDev1.append(yDev2);

		distributionDeviation->setData(x, yDev1, true);
	} else {
		coordinatesLabelString = "${X}\n${Y}";
		distribution->data()->clear();
		distributionDeviation->data()->clear();
	}


	plotMed();
	plotWalshMed();

	this->yAxis->setRange(yRange);

	PlotBase::fill(dv);
}

