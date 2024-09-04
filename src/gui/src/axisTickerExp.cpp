#include "axisTickerExp.hpp"
#include <QtCore/qlogging.h>

AxisTickerExp::AxisTickerExp() :
	mLogBase(10.0),
	mSubTickCount(8), // generates 10 intervals
	mLogBaseLnInv(1.0/qLn(mLogBase))
{
}

void AxisTickerExp::setLogBase(double base)
{
	if (base > 0)
	{
		mLogBase = base;
		mLogBaseLnInv = 1.0/qLn(mLogBase);
	} else
		qDebug() << Q_FUNC_INFO << "log base has to be greater than zero:" << base;
}

void AxisTickerExp::setSubTickCount(int subTicks)
{
  if (subTicks >= 0)
    mSubTickCount = subTicks;
  else
    qDebug() << Q_FUNC_INFO << "sub tick count can't be negative:" << subTicks;
}

int AxisTickerExp::getSubTickCount(double tickStep)
{
  Q_UNUSED(tickStep)
  return mSubTickCount;
}

// QVector<double> AxisTickerExp::createTickVector(double tickStep, const QCPRange &range)
// {
//   QVector<double> result;
//   if (range.lower > 0 && range.upper > 0) // positive range
//   {
// 	  qDebug() << range;
// 	for (double y = range.lower; y < range.upper; y += range.size()/8) {
// 		result.append(qLn(1/(1-y)));
// 	}
//     // while (currentTick < range.upper && currentTick > 0) // currentMag might be zero for ranges ~1e-300, just cancel in that case
//     // {
//     //   currentTick *= newLogBase;
//     //   result.append(currentTick);
//     // }
//   // } else if (range.lower < 0 && range.upper < 0) // negative range
//   // {
//   //   const double baseTickCount = qLn(range.lower/range.upper)*mLogBaseLnInv;
//   //   if (baseTickCount < 1.6) // if too few log ticks would be visible in axis range, fall back to regular tick vector generation
//   //     return QCPAxisTicker::createTickVector(tickStep, range);
//   //   const double exactPowerStep =  baseTickCount/double(mTickCount+1e-10);
//   //   const double newLogBase = qPow(mLogBase, qMax(int(cleanMantissa(exactPowerStep)), 1));
//   //   double currentTick = -qPow(newLogBase, qCeil(qLn(-range.lower)/qLn(newLogBase)));
//   //   result.append(currentTick);
//   //   while (currentTick < range.upper && currentTick < 0) // currentMag might be zero for ranges ~1e-300, just cancel in that case
//   //   {
//   //     currentTick /= newLogBase;
//   //     result.append(currentTick);
//   //   }
//   } else // invalid range for logarithmic scale, because lower and upper have different sign
//   {
//     qDebug() << Q_FUNC_INFO << "Invalid range for logarithmic plot: " << range.lower << ".." << range.upper;
//   }
//   
//   return result;
// }


QVector<double> AxisTickerExp::createTickVector(double tickStep, const QCPRange &range)
{
  QVector<double> result;
  if (range.lower > 0 && range.upper > 0) // positive range
  {
    const double baseTickCount = qLn(range.upper/range.lower)*mLogBaseLnInv;
    if (baseTickCount < 1.6) // if too few log ticks would be visible in axis range, fall back to regular tick vector generation
      return QCPAxisTicker::createTickVector(tickStep, range);
    const double exactPowerStep =  baseTickCount/double(mTickCount+1e-10);
    const double newLogBase = qPow(mLogBase, qMax(int(cleanMantissa(exactPowerStep)), 1));
    double currentTick = qPow(newLogBase, qFloor(qLn(range.lower)/qLn(newLogBase)));
    result.append(currentTick);
    while (currentTick < range.upper && currentTick > 0) // currentMag might be zero for ranges ~1e-300, just cancel in that case
    {
      currentTick *= newLogBase;
      result.append(currentTick);
    }
  } else if (range.lower < 0 && range.upper < 0) // negative range
  {
    const double baseTickCount = qLn(range.lower/range.upper)*mLogBaseLnInv;
    if (baseTickCount < 1.6) // if too few log ticks would be visible in axis range, fall back to regular tick vector generation
      return QCPAxisTicker::createTickVector(tickStep, range);
    const double exactPowerStep =  baseTickCount/double(mTickCount+1e-10);
    const double newLogBase = qPow(mLogBase, qMax(int(cleanMantissa(exactPowerStep)), 1));
    double currentTick = -qPow(newLogBase, qCeil(qLn(-range.lower)/qLn(newLogBase)));
    result.append(currentTick);
    while (currentTick < range.upper && currentTick < 0) // currentMag might be zero for ranges ~1e-300, just cancel in that case
    {
      currentTick /= newLogBase;
      result.append(currentTick);
    }
  } else // invalid range for logarithmic scale, because lower and upper have different sign
  {
    qDebug() << Q_FUNC_INFO << "Invalid range for logarithmic plot: " << range.lower << ".." << range.upper;
  }
  
  return result;
}
