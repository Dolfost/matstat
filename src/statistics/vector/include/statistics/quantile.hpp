#ifndef _VECTOR_QUANTILE_HPP_
#define _VECTOR_QUANTILE_HPP_

#include<utility>

namespace ss {
double normQuantile(double);
double studQuantile(double, int);
double pearQuantile(double, int);
double fishQuantile(double, int, int);

double normalDistributionCdf(double);

std::pair<double, double> 
thetaDeviation(
	double theta,
	double deviation,
	double alpha = 0.95,
	size_t size = 61,
	bool stdDev = true
);

}

#endif // !_VECTOR_QUANTILE_HPP_
