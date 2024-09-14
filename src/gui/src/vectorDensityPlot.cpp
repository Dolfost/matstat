#include <QDebug>

#include "vectorDensityPlot.hpp"
#include "vectorPlotBase.hpp"

VectorDensityPlot::VectorDensityPlot(ss::Vector*v, QWidget* parent) : VectorPlotBase(v, parent) {
	bars = new QCPBars(this->xAxis, this->yAxis);
	bars->setName("f(x) (класи)");
	bars->setWidthType(QCPBars::WidthType::wtPlotCoords);

	QPen barsPen;
	barsPen.setWidth(0);
	bars->setPen(Qt::NoPen);
	QBrush barsBrush;
	barsBrush.setStyle(Qt::SolidPattern);
	barsBrush.setColor("#2b8eff");
	bars->setBrush(barsBrush);

	density = new QCPGraph(this->xAxis2, this->yAxis2);
	density->setName("f(x) (відтв.)");
	this->yAxis2->setLabel("f(x) (відтворена)");
	this->xAxis2->setLabel("x (відтворена)");
	QPen densityPen;
	densityPen.setWidthF(1.3);
	densityPen.setColor("#0313fc");
	density->setPen(densityPen);

	this->yAxis->setLabel("f(x) (класи)");
}

void VectorDensityPlot::fill() {
	ss::Vector::ClassSeries& cs = v_vector->cs;

	bars->setWidth(cs.step());

	QVector<double> x, y;
	for (size_t i = 0; i < cs.count(); i++) {
		x.push_back(v_vector->min() + cs.step()*(i+0.5));
		y.push_back(cs.series()[i].second);
	}

	bars->setData(x, y, true);

	x.clear(), y.clear();

	if (v_vector->dist.model != ss::Vector::Distribution::Model::Unknown) {
		if (v_vector->dist.domain.first == v_vector->dist.domain.second)
			coordinatesLabelString = "${X}\n${Y} ${Y2}";
		else
			coordinatesLabelString = "${X} ${X2}\n${Y} ${Y2}";

		this->yAxis2->setTickLabels(true);
		this->yRange2 = QCPRange(0, v_vector->dist.pdfMax);
		double a, b;
		if (v_vector->dist.domain.first != v_vector->dist.domain.second) {
			a = v_vector->dist.domain.first;
			b = v_vector->dist.domain.second;
		} else {
			a = v_vector->min();
			b = v_vector->max();
		}

		double interval = abs(a - b)/2;
		for (double arg = a;
				arg <= b;
				arg += interval/350) {
			x.push_back(arg);
			y.push_back(v_vector->dist.pdf(arg));
		}

		density->setData(x, y);
	} else {
		coordinatesLabelString = "${X}\n${Y}";
		this->yAxis2->setTickLabels(false);
		density->data()->clear();
	};

	yRange = QCPRange(0, cs.maxProb());

	VectorPlotBase::fill();
}

