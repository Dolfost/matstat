#ifndef _STATISTICS_HPP_
#define _STATISTICS_HPP_

class Statistics {
public:
	static double normQuantile(double);
	static double studQuantile(double, int);
	static double pearQuantile(double, int);
	static double fishQuantile(double, int, int);

	static double normalDistributionCdf(double);
};

#endif // !_STATISTICS_HPP_
