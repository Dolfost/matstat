#ifndef _STATISTICS_EXPRTK_HPP_
#define _STATISTICS_EXPRTK_HPP_

#include "exprtk.hpp"
#include "statistics.hpp"

struct exprtkNormQuantile final : public exprtk::ifunction<double> {
	exprtkNormQuantile() : exprtk::ifunction<double>(1)  {
	}
	double operator()(const double& alpha) {
		return Statistics::normQuantile(alpha);
	}
};

struct exprtkStudQuantile final : public exprtk::ifunction<double> {
	exprtkStudQuantile() : exprtk::ifunction<double>(2)  {
	}
	double operator()(const double& alpha, const double& v) {
		return Statistics::studQuantile(alpha, v);
	}
};

struct exprtkPearQuantile final : public exprtk::ifunction<double> {
	exprtkPearQuantile() : exprtk::ifunction<double>(2)  {
	}
	double operator()(const double& alpha, const double& v) {
		return Statistics::pearQuantile(alpha, v);
	}
};

struct exprtkFishQuantile final : public exprtk::ifunction<double> {
	exprtkFishQuantile() : exprtk::ifunction<double>(3)  {
	}
	double operator()(const double& alpha, const double& v1, const double& v2) {
		return Statistics::fishQuantile(alpha, v1, v2);
	}
};
	
struct exprtkNormalDistributionCdf final : public exprtk::ifunction<double> {
	exprtkNormalDistributionCdf () : exprtk::ifunction<double>(1)  {
	}
	double operator()(const double& u) {
		return Statistics::normalDistributionCdf(u);
	}
};

#endif // !_STATISTICS_EXPRTK_HPP_
