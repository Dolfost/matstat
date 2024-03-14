#ifndef _STATISTICS_HPP_
#define _STATISTICS_HPP_

#include <QString>

class Statistics {
public:
	static const QString exprtkFuncitons;
	static double normQuantile(double);
	static double studQuantile(double, int);
	static double pearQuantile(double, int);
	static double fishQuantile(double, int, int);

	static double normalDistributionCdf(double);

	static std::pair<double, double> 
		thetaDeviation(
				double theta,
				double deviation,
				double alpha = 0.95,
				size_t size = 61);
};

#endif // !_STATISTICS_HPP_
