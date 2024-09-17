#include<vector.hpp>

namespace ss {

double normQuantile(double alpha) {
	double quantile = 0;

	const double 
		c0 = 2.515517,
		c1 = 0.802853,
		c2 = 0.010328,
		d1 = 1.432788,
		d2 = 0.1892659,
		d3 = 0.001308,
		t = std::sqrt(std::log(1/std::pow(alpha, 2)));

	quantile = t - (c0 + c1*t + c2*std::pow(t, 2)) /
		(1 + d1*t + d2*std::pow(t, 2) + d3*std::pow(t, 3));
	
	return -quantile;
}

double pearQuantile(double alpha, int v) {
	double quantile = 0;

	quantile = v*pow(1 - 2.0/(9*v) + normQuantile(alpha)*sqrt(2.0/(9*v)), 3);
	
	return quantile;
}

double studQuantile(double alpha, int v) {
	double quantile = 0;

	const double
		nq = normQuantile(alpha),
		nq2 = nq*nq,
		nq3 = nq2*nq,
		nq5 = nq3*nq2,
		nq7 = nq5*nq2,
		nq9 = nq7*nq2,
		g1 = (nq3 + nq)/4,
		g2 = (5*nq5 + 16*nq3 + 3*nq)/96,
		g3 = (3*nq7 + 19*nq5 + 17*nq3 - 15*nq)/384,
		g4 = (79*nq9 + 779*nq7 + 1482*nq5 - 1920*nq3 - 945*nq)/92160;

	quantile = nq + g1/v + g2/pow(v, 2) + g3/pow(v, 3) + g4/pow(v, 4);

	return quantile;
}

double fishQuantile(double alpha, int v1, int v2) {
	double quantile = 0;

	const double
		sigma = 1.0/v1 + 1.0/v2,
		delta = 1.0/v1 - 1.0/v2,
		sigmaSqrtBy2 = sqrt(sigma/2),
		nq = normQuantile(alpha),
		nq2 = nq*nq,
		nq3 = nq2*nq,
		nq4 = nq3*nq4,
		nq5 = nq4*nq,
		z = nq*sigmaSqrtBy2 - delta*(nq*nq+2)/6 + 
			sigmaSqrtBy2*((sigma*(nq2 + 3*nq)/24 + 
			(pow(delta, 2)*(nq3 +11*nq))/(72*sigma))) -
			(delta*sigma*(nq4+9*nq2+8))/120 +
			(pow(delta, 3)*(3*nq4 + 7*nq2 - 16))/(3240*sigma) +
			sigmaSqrtBy2*(pow(sigma, 2)*(nq5 + 20*nq3 +15*nq)/1920 + 
			pow(delta, 4)*(nq5 + 44*nq3 + 183*nq)/2880 + 
			pow(delta, 4)*(9*nq5 - 284*nq3 - 1513*nq)/(155520 * pow(sigma, 2)));

	quantile = exp(2*z);

	return quantile;
}

double normalDistributionCdf(double u) {
	double x = abs(u);
	double 
		p = 0.2316419,
		b1 = 0.31938153,
		b2 = -0.356563782,
		b3 = 1.781477937,
		b4 = -1.821255978,
		b5 = 1.330274429,
		t1 = 1/(1+p*x),
		t2 = t1*t1,
		t3 = t2*t1,
		t4 = t3*t1,
		t5 = t4*t1;

	double f = 1-0.3989422804*std::exp(-(std::pow(x, 2))/2) * 
		(b1*t1 + b2*t2 + b3*t3 + b4*t4 + b5*t5);

	if (u < 0)
		f = 1 - f;

	return f;
}

std::pair<double, double> thetaDeviation(
				double theta,
				double deviation,
				double alpha,
				size_t size,
				bool stdDev) {

	if (!stdDev)
		deviation = std::sqrt(deviation);

	std::pair<double, double> interval;

	double quantile;
	if (size > 60) {
		quantile = normQuantile(1-alpha/2);
	} else {
		quantile = studQuantile(1-alpha/2, size-1);
	}

	// NOTE: Be aware that signs are inverted
	interval.first = theta + quantile *
		deviation;
	interval.second = theta - quantile *
		deviation;

	return interval;
}

}
