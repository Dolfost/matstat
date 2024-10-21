#ifndef _VECTOR_EXPRTK_QUANTILE_HPP_
#define _VECTOR_EXPRTK_QUANTILE_HPP_

#include "exprtk.hpp"
#include "quantile.hpp"

#include <random>

namespace ss::exprtk {

static const std::string functionNames = 
	"normQuantile(a) — квантиль нормального розподілу\n"
	"studQuantile(a,v) — квантиль розподілу Стьюдента\n"
	"pearQuantile(a,v) — квантиль розподілу Пірсона\n"
	"fishQuantile(a,v1,v2) — квантиль розподілу Фішера\n"
	"normCdf(u) — функція розподілу нормованого нормального розподілу\n"
	"uRand(a,b) — рівномірно розподілена випадкова величина";

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

struct exprtk_uniform_real_distribution final: public ::exprtk::ifunction<double> {
	exprtk_uniform_real_distribution(): ::exprtk::ifunction<double>(2) {}
	double operator()(const double& f, const double& t) {
		std::default_random_engine generator;
		generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
		std::uniform_real_distribution<double> distrib(f, t);
		return distrib(generator);
	};
};

struct exprtk_normal_distribution final: public ::exprtk::ifunction<double> {
	exprtk_normal_distribution(): ::exprtk::ifunction<double>(2) {}
	double operator()(const double& m, const double& sigma) {
		std::default_random_engine generator;
		generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
		std::normal_distribution<double> distrib(m, sigma);
		return distrib(generator);
	};
};

}

#endif // !_VECTOR_EXPRTK_QUANTILE_HPP_
