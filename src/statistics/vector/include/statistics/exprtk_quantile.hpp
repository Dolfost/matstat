#ifndef _VECTOR_EXPRTK_QUANTILE_HPP_
#define _VECTOR_EXPRTK_QUANTILE_HPP_

#include "exprtk.hpp"
#include "quantile.hpp"

namespace ss::exprtk {

struct NormQuantile final : public ::exprtk::ifunction<double> {
	NormQuantile() : ::exprtk::ifunction<double>(1) {}
	double operator()(const double& alpha);
};

struct StudQuantile final : public ::exprtk::ifunction<double> {
	StudQuantile() : ::exprtk::ifunction<double>(2) {}
	double operator()(const double& alpha, const double& v) {
		return studQuantile(alpha, v);
	}
};

struct PearQuantile final : public ::exprtk::ifunction<double> {
	PearQuantile() : ::exprtk::ifunction<double>(2) {}
	double operator()(const double& alpha, const double& v) {
		return pearQuantile(alpha, v);
	}
};

struct FishQuantile final : public ::exprtk::ifunction<double> {
	FishQuantile() : ::exprtk::ifunction<double>(3) {}
	double operator()(const double& alpha, const double& v1, const double& v2) {
		return fishQuantile(alpha, v1, v2);
	}
};
	
struct NormalDistributionCdf final : public ::exprtk::ifunction<double> {
	NormalDistributionCdf() : ::exprtk::ifunction<double>(1) {}
	double operator()(const double& u) {
		return normalDistributionCdf(u);
	}
};

}

#endif // !_VECTOR_EXPRTK_QUANTILE_HPP_
