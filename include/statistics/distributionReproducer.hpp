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
	double x = 0;

	double confidence = 0.95;

	exprtk::symbol_table<double> symbolTable;
	exprtk::expression<double> pdfExpression; // probability density function
	exprtk::expression<double> cdfExpression; // cummulative density function
	exprtk::expression<double> invCdfExpression;
	exprtk::expression<double> cdfDeviationExpression;

	std::pair<double, double> cdfDeviation(double = 0.95);

	QString cdfString;
	QString pdfString;
	QString invCdfString;
	
	size_t size = 0;
	size_t parametersCount = 0;
	std::vector<QString> paremeterNames;
	std::vector<QString> parametersDeviationNames;
	std::vector<double> parameters{0};
	std::vector<double> parametersDeviation{0};
	double parametersCv = 0;
	double pdfMax = 0;

private:
	static exprtk::parser<double> parser;
	exprtkNormalDistributionCdf* eNormalDistributionCdf = nullptr;
};

#endif //!_DISTRIBUTION_REPRODUCER_HPP_
