#ifndef _AXIS_TICKER_EXP_HPP_
#define _AXIS_TICKER_EXP_HPP_

#include "qcustomplot.h"

class AxisTickerExp : public QCPAxisTicker
{
	public:
		AxisTickerExp();

		// getters:
		double logBase() const { return mLogBase; }
		int subTickCount() const { return mSubTickCount; }

		// setters:
		void setLogBase(double base);
		void setSubTickCount(int subTicks);

	protected:
		// property members:
		double mLogBase;
		int mSubTickCount;

		// non-property members:
		double mLogBaseLnInv;

		// reimplemented virtual methods:
		virtual int getSubTickCount(double tickStep) Q_DECL_OVERRIDE;
		virtual QVector<double> createTickVector(double tickStep, const QCPRange &range) Q_DECL_OVERRIDE;
};

#endif // !_AXIS_TICKER_EXP_HPP_
