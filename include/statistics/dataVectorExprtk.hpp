#ifndef _DATA_VECTOR_EXPRTK_HPP_
#include "exprtk.hpp"
#include "dataVector.hpp"

struct exprtkMean final : public exprtk::ifunction<double> {
	exprtkMean(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->mean();
	}
};

struct exprtkNormalDistributionCdf final : public exprtk::ifunction<double> {
	exprtkNormalDistributionCdf () : exprtk::ifunction<double>(1)  {
	}
	double operator()(const double& u) {
		return DataVector::normalDistributionCdf(u);
	}
};

struct exprtkMed final : public exprtk::ifunction<double> {
	exprtkMed(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->med();
	}
};

struct exprtkMad final : public exprtk::ifunction<double> {
	exprtkMad(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->mad();
	}
};

struct exprtkWalshAveragesMed final : public exprtk::ifunction<double> {
	exprtkWalshAveragesMed(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->walshAveragesMed();
	}
};

struct exprtkSize final : public exprtk::ifunction<double> {
	exprtkSize(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->size();
	}
};

struct exprtkVariationCoef final : public exprtk::igeneric_function<double> {
	exprtkVariationCoef(DataVector* vec) : exprtk::igeneric_function<double>("S")  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[0]);
		std::string mstr = m.begin();
		DataVector::Measure measure;
		if (mstr == "pop")
			measure = DataVector::Measure::PopulationM;
		else if (mstr == "spl")
			measure = DataVector::Measure::SampleM;
		else 
			measure = DataVector::Measure::UnknownM;
return dv->variationCoef(measure);
	}
};

struct exprtkKurtosis final : public exprtk::igeneric_function<double> {
	exprtkKurtosis(DataVector* vec) : exprtk::igeneric_function<double>("S")  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[0]);
		std::string mstr = m.begin();
		DataVector::Measure measure;
		if (mstr == "pop")
			measure = DataVector::Measure::PopulationM;
		else if (mstr == "spl")
			measure = DataVector::Measure::SampleM;
		else 
			measure = DataVector::Measure::UnknownM;

		return dv->kurtosis(measure);
	}
};

struct exprtkSkew final : public exprtk::igeneric_function<double> {
	exprtkSkew(DataVector* vec) : exprtk::igeneric_function<double>("S")  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[0]);
		std::string mstr = m.begin();
		DataVector::Measure measure;
		if (mstr == "pop")
			measure = DataVector::Measure::PopulationM;
		else if (mstr == "spl")
			measure = DataVector::Measure::SampleM;
		else 
			measure = DataVector::Measure::UnknownM;

		return dv->skew(measure);
	}
};

struct exprtkVariance final : public exprtk::igeneric_function<double> {
	exprtkVariance(DataVector* vec) : exprtk::igeneric_function<double>("S")  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[0]);
		std::string mstr = m.begin();
		DataVector::Measure measure;
		if (mstr == "pop")
			measure = DataVector::Measure::PopulationM;
		else if (mstr == "spl")
			measure = DataVector::Measure::SampleM;
		else 
			measure = DataVector::Measure::UnknownM;

		return dv->variance(measure);
	}
};

struct exprtkXmin final : public exprtk::ifunction<double> {
	exprtkXmin(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->min();
	}
};

struct exprtkXmax final : public exprtk::ifunction<double> {
	exprtkXmax(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->max();
	}
};

struct exprtkStandartDeviation final : public exprtk::igeneric_function<double> {
	exprtkStandartDeviation(DataVector* vec) : exprtk::igeneric_function<double>("S")  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[0]);
		std::string mstr = m.begin();
		DataVector::Measure measure;
		if (mstr == "pop")
			measure = DataVector::Measure::PopulationM;
		else if (mstr == "spl")
			measure = DataVector::Measure::SampleM;
		else 
			measure = DataVector::Measure::UnknownM;

		return dv->standardDeviation(measure);
	}
};

struct exprtkRawMoment final : public exprtk::ifunction<double> {
	exprtkRawMoment(DataVector* vec) : exprtk::ifunction<double>(1)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(const double& degree) {
		return dv->rawMoment(degree);
	}
};

struct exprtkCentralMoment final : public exprtk::igeneric_function<double> {
	exprtkCentralMoment(DataVector* vec) : exprtk::igeneric_function<double>("TS")  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::scalar_view scalar_t;
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[1]);
		std::string mstr = m.begin();
		DataVector::Measure measure;
		if (mstr == "pop")
			measure = DataVector::Measure::PopulationM;
		else if (mstr == "spl")
			measure = DataVector::Measure::SampleM;
		else 
			measure = DataVector::Measure::UnknownM;

		return dv->centralMoment(scalar_t(parameters[0]), measure);
	}
};

struct exprtkCounterKurtosis final : public exprtk::igeneric_function<double> {
	exprtkCounterKurtosis(DataVector* vec) : exprtk::igeneric_function<double>("S")  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(parameter_list_t parameters) {
		typedef typename generic_type::string_view string_t;
		string_t m(parameters[1]);
		std::string mstr = m.begin();
		DataVector::Measure measure;
		if (mstr == "pop")
			measure = DataVector::Measure::PopulationM;
		else if (mstr == "spl")
			measure = DataVector::Measure::SampleM;
		else 
			measure = DataVector::Measure::UnknownM;

		return dv->counterKurtosis(measure);
	}
};

struct exprtkTurncatedMean final : public exprtk::ifunction<double> {
	exprtkTurncatedMean(DataVector* vec) : exprtk::ifunction<double>(1)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(const double& k) {
		return dv->turncatedMean(k);
	}
};

struct exprtkNonparametricVariationCoef final : public exprtk::ifunction<double> {
	exprtkNonparametricVariationCoef(DataVector* vec) : exprtk::ifunction<double>(0)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()() {
		return dv->nonparametricVariationCoef();
	}
};

struct exprtkNormQuantile final : public exprtk::ifunction<double> {
	exprtkNormQuantile(DataVector* vec) : exprtk::ifunction<double>(1)  {
	}
	double operator()(const double& alpha) {
		return DataVector::normQuantile(alpha);
	}
};

struct exprtkStudQuantile final : public exprtk::ifunction<double> {
	exprtkStudQuantile(DataVector* vec) : exprtk::ifunction<double>(2)  {
	}
	double operator()(const double& alpha, const double& v) {
		return DataVector::studQuantile(alpha, v);
	}
};

struct exprtkPearQuantile final : public exprtk::ifunction<double> {
	exprtkPearQuantile(DataVector* vec) : exprtk::ifunction<double>(2)  {
	}
	double operator()(const double& alpha, const double& v) {
		return DataVector::pearQuantile(alpha, v);
	}
};

struct exprtkFishQuantile final : public exprtk::ifunction<double> {
	exprtkFishQuantile(DataVector* vec) : exprtk::ifunction<double>(3)  {
	}
	double operator()(const double& alpha, const double& v1, const double& v2) {
		return DataVector::fishQuantile(alpha, v1, v2);
	}
};

struct exprtkBeta final : public exprtk::ifunction<double> {
	exprtkBeta(DataVector* vec) : exprtk::ifunction<double>(1)  {
		dv = vec;
	}
	DataVector* dv;
	double operator()(const double& k) {
		return dv->beta(k);
	}
};

#endif // !_DATA_VECTOR_EXPRTK_HPP_
