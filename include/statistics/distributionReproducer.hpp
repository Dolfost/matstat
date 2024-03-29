#ifndef _DISTRIBUTION_REPRODUCER_HPP_
#define _DISTRIBUTION_REPRODUCER_HPP_

#include "exprtk.hpp"
#include "statisticsExprtk.hpp"
#include <QString>
#include <vector>

class DistributionReproducer {
public:
	DistributionReproducer();
	~DistributionReproducer();

	enum Distribution {
		UnknownD,
		NormalD,
		ExponentialD,
		WeibullD,
		LogNormalD,
		UniformD,
		CountD,
	} model = UnknownD;

	enum Method {
		InverseM,
		PlaneM,
		CountM,
	};

	void setDistribution(Distribution, std::vector<double>, size_t);
	static const QStringList distributionName;
	static const QStringList methodName;
	static const QList<QStringList> parameterName;

	std::list<double> generateSet(Method, size_t = 0, double = 0, double = 1);

public:
	double confidence = 0.95;

	std::pair<double, double> cdfDeviation(double = 0.95);

	QString cdfString;
	QString pdfString;
	QString invCdfString;

	double pdf(double);
	double cdf(double);
	double cdfDev(double);
	double invCdf(double);
	
	size_t size = 0;
	size_t parametersCount = 0;
	std::vector<QString> paremeterNames;
	std::vector<QString> parametersDeviationNames;
	std::vector<double> parameters{0};
	std::vector<double> parametersDeviation{0};
	double parametersCv = 0;
	double pdfMax = 0;

private:
	exprtk::symbol_table<double> symbolTable;
	exprtk::expression<double> pdfExpression; // probability density function
	exprtk::expression<double> cdfExpression; // cummulative density function
	exprtk::expression<double> invCdfExpression;
	exprtk::expression<double> cdfDeviationExpression;

	double x = 0;
	static exprtk::parser<double> parser;
	exprtkNormalDistributionCdf* eNormalDistributionCdf = nullptr;
	exprtkNormQuantile* eNormQuantile = nullptr;
};

#endif //!_DISTRIBUTION_REPRODUCER_HPP_
