#ifndef _DISTRIBUTION_REPRODUCER_HPP_
#define _DISTRIBUTION_REPRODUCER_HPP_

#include "exprtk.hpp"
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
		CountD,
	} model = UnknownD;

	void setDistribution(Distribution, std::vector<double>, size_t);
	static const QStringList distributionName;

	double x = 0;

	exprtk::symbol_table<double> symbolTable;
	exprtk::expression<double> pdfExpression; // probability density function
	exprtk::expression<double> cdfExpression; // cummulative density function
	exprtk::expression<double> cdfDeviationExpression;

	QString cdfString;
	QString pdfString;
	
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
	int* eNormalDistributionCdf = nullptr;
};

#endif //!_DISTRIBUTION_REPRODUCER_HPP_
