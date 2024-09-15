#ifndef __EXPRTK_VECTOR__
#define __EXPRTK_VECTOR__

#include "exprtk.hpp"
#include "vector.hpp"
#include <random>

namespace ss {

struct exprtkMean final : public ::exprtk::ifunction<double> {
	exprtkMean(ss::Vector* vec) : ::exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()() {
		return dv->mean();
	}
};

struct exprtkUniformRandom final : public ::exprtk::ifunction<double> {
	exprtkUniformRandom(): ::exprtk::ifunction<double>(2) {};
	double operator()(const double& f, const double& t) {
		std::default_random_engine generator;
		generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
		std::uniform_real_distribution<double> dist(f, t);
		return dist(generator);
	};

};
struct exprtkMed final : public ::exprtk::ifunction<double> {
	exprtkMed(ss::Vector* vec) : ::exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()() {
		return dv->med();
	}
};

struct exprtkMad final : public ::exprtk::ifunction<double> {
	exprtkMad(ss::Vector* vec) : ::exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()() {
		return dv->mad();
	}
};

struct exprtkWalshAveragesMed final : public ::exprtk::ifunction<double> {
	exprtkWalshAveragesMed(ss::Vector* vec) : ::exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()() {
		return dv->walshAveragesMed();
	}
};

struct exprtkSize final : public ::exprtk::ifunction<double> {
	exprtkSize(ss::Vector* vec) : ::exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()() {
		return dv->size();
	}
};

struct exprtkVariationCoef final : public ::exprtk::igeneric_function<double> {
	exprtkVariationCoef(ss::Vector* vec) : ::exprtk::igeneric_function<double>("S")  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[0]);
		std::string mstr = m.begin();
		ss::Measure measure;
		if (mstr == "pop")
			measure = ss::Measure::Population;
		else if (mstr == "spl")
			measure = ss::Measure::Sample;
		else 
			measure = ss::Measure::Unknown;
return dv->cv(measure);
	}
};

struct exprtkKurtosis final : public ::exprtk::igeneric_function<double> {
	exprtkKurtosis(ss::Vector* vec) : ::exprtk::igeneric_function<double>("S")  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[0]);
		std::string mstr = m.begin();
		ss::Measure measure;
		if (mstr == "pop")
			measure = ss::Measure::Population;
		else if (mstr == "spl")
			measure = ss::Measure::Sample;
		else 
			measure = ss::Measure::Unknown;

		return dv->kurtosis(measure);
	}
};

struct exprtkSkew final : public ::exprtk::igeneric_function<double> {
	exprtkSkew(ss::Vector* vec) : ::exprtk::igeneric_function<double>("S")  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[0]);
		std::string mstr = m.begin();
		ss::Measure measure;
		if (mstr == "pop")
			measure = ss::Measure::Population;
		else if (mstr == "spl")
			measure = ss::Measure::Sample;
		else 
			measure = ss::Measure::Unknown;

		return dv->skew(measure);
	}
};

struct exprtkVariance final : public ::exprtk::igeneric_function<double> {
	exprtkVariance(ss::Vector* vec) : ::exprtk::igeneric_function<double>("S")  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[0]);
		std::string mstr = m.begin();
		ss::Measure measure;
		if (mstr == "pop")
			measure = ss::Measure::Population;
		else if (mstr == "spl")
			measure = ss::Measure::Sample;
		else 
			measure = ss::Measure::Unknown;

		return dv->variance(measure);
	}
};

struct exprtkXmin final : public ::exprtk::ifunction<double> {
	exprtkXmin(ss::Vector* vec) : ::exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()() {
		return dv->min();
	}
};

struct exprtkXmax final : public ::exprtk::ifunction<double> {
	exprtkXmax(ss::Vector* vec) : ::exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()() {
		return dv->max();
	}
};

struct exprtkStandartDeviation final : public ::exprtk::igeneric_function<double> {
	exprtkStandartDeviation(ss::Vector* vec) : ::exprtk::igeneric_function<double>("S")  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[0]);
		std::string mstr = m.begin();
		ss::Measure measure;
		if (mstr == "pop")
			measure = ss::Measure::Population;
		else if (mstr == "spl")
			measure = ss::Measure::Sample;
		else 
			measure = ss::Measure::Unknown;

		return dv->sd(measure);
	}
};

struct exprtkRawMoment final : public ::exprtk::ifunction<double> {
	exprtkRawMoment(ss::Vector* vec) : ::exprtk::ifunction<double>(1)  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()(const double& degree) {
		return dv->rawMoment(degree);
	}
};

struct exprtkCentralMoment final : public ::exprtk::igeneric_function<double> {
	exprtkCentralMoment(ss::Vector* vec) : ::exprtk::igeneric_function<double>("TS")  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::scalar_view scalar_t;
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[1]);
		std::string mstr = m.begin();
		ss::Measure measure;
		if (mstr == "pop")
			measure = ss::Measure::Population;
		else if (mstr == "spl")
			measure = ss::Measure::Sample;
		else 
			measure = ss::Measure::Unknown;

		return dv->centralMoment(scalar_t(parameters[0]), measure);
	}
};

struct exprtkCounterKurtosis final : public ::exprtk::igeneric_function<double> {
	exprtkCounterKurtosis(ss::Vector* vec) : ::exprtk::igeneric_function<double>("S")  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[1]);
		std::string mstr = m.begin();
		ss::Measure measure;
		if (mstr == "pop")
			measure = ss::Measure::Population;
		else if (mstr == "spl")
			measure = ss::Measure::Sample;
		else 
			measure = ss::Measure::Unknown;

		return dv->counterKurtosis(measure);
	}
};

struct exprtkTurncatedMean final : public ::exprtk::ifunction<double> {
	exprtkTurncatedMean(ss::Vector* vec) : ::exprtk::ifunction<double>(1)  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()(const double& k) {
		return dv->tmean(k);
	}
};

struct exprtkNonparametricVariationCoef final : public ::exprtk::ifunction<double> {
	exprtkNonparametricVariationCoef(ss::Vector* vec) : ::exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()() {
		return dv->ncv();
	}
};

struct exprtkBeta final : public ::exprtk::ifunction<double> {
	exprtkBeta(ss::Vector* vec) : ::exprtk::ifunction<double>(1)  {
		dv = vec;
	}
	ss::Vector* dv;
	double operator()(const double& k) {
		return dv->beta(k);
	}
};

}

#endif // !__EXPRTK_VECTOR__
