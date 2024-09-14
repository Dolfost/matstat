#ifndef _VECTOR_PLOT_BASE_HPP_
#define _VECTOR_PLOT_BASE_HPP_

#include "qcustomplot.h"
#include "vector.hpp"

#include<plotBase.hpp>

class VectorPlotBase : public PlotBase {
	Q_OBJECT
public:
	VectorPlotBase(ss::Vector*, QWidget* parent = nullptr);

	ss::Vector* vector();
	void setVector(ss::Vector* v) { v_vector = v; };

public slots:
	virtual void fill() override;
	virtual void toggleLog(bool) override;

protected:
	ss::Vector* v_vector = nullptr;

	QSharedPointer<QCPAxisTickerFixed> xFixedTicker;
	QSharedPointer<QCPAxisTicker> xTicker;
	QSharedPointer<QCPAxisTicker> yTicker;
	QSharedPointer<QCPAxisTickerLog> yLogTicker;

	QCPScatterStyle scatterStyle;
	QPen scatterPen;
	QCPGraph* mean = nullptr;
	QCPGraph* standatrDeviation = nullptr;
	QCPGraph* med = nullptr;
	QCPGraph* walshMed = nullptr;
};

#endif // !VECTOR_PLOTASE_HPP_
