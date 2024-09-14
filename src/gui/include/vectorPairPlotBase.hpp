#ifndef _VECTOR_PAIR_PLOT_BASE_HPP_
#define _VECTOR_PAIR_PLOT_BASE_HPP_

#include<plotBase.hpp>
#include<vectorPair.hpp>

class VectorPairPlotBase: public PlotBase {
public:
	VectorPairPlotBase(ss::VectorPair*, QWidget*);

	ss::VectorPair* vector() { return v_pair; };
	void setVector(ss::VectorPair* v) { v_pair = v; };

public slots:
	virtual void fill() override;
	virtual void toggleLog(bool) override;

protected:
	ss::VectorPair* v_pair;

	QSharedPointer<QCPAxisTickerFixed> xFixedTicker = QSharedPointer<QCPAxisTickerFixed>(new QCPAxisTickerFixed);
	QSharedPointer<QCPAxisTickerFixed> yFixedTicker = QSharedPointer<QCPAxisTickerFixed>(new QCPAxisTickerFixed);
	QSharedPointer<QCPAxisTickerLog> yLogTicker = QSharedPointer<QCPAxisTickerLog>(new QCPAxisTickerLog);

	QCPGraph* mean = nullptr;
	QCPGraph* sd = nullptr;
	QCPGraph* med = nullptr;
};

#endif // !_VECTOR_PAIR_PLOT_BASE_HPP_
