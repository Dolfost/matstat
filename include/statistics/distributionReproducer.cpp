#include "distributionReproducer.hpp"

#include "exprtk.hpp"
#include "dataVectorExprtk.hpp"
#include <QString>
#include <vector>

DistributionReproducer::DistributionReproducer() {
	symbolTable.add_variable("x", x);
	exprtkNormalDistributionCdf* eNormalDistributionCdf = new exprtkNormalDistributionCdf();

	symbolTable.add_function("normCdf", *eNormalDistributionCdf);
	cdfExpression.register_symbol_table(symbolTable);
	pdfExpression.register_symbol_table(symbolTable);
	cdfDeviationExpression.register_symbol_table(symbolTable);
}

exprtk::parser<double> DistributionReproducer::parser;

void DistributionReproducer::setDistribution(Distribution type, std::vector<double> p, size_t s) {
	model = type;
	size = s;

	paremeterNames.clear();
	parameters.clear();
	parametersDeviation.clear();

	switch (model) {
		case Distribution::NormalD:
			{
				parametersCount = 2;
				paremeterNames = {
					"m", "σ"
				};
				parametersDeviationNames =
					paremeterNames;
				pdfMax = 1/(p[1]*2.5066282746);
				parametersDeviation.push_back(
						std::pow(parameters[1], 2)/size);
				parametersDeviation.push_back(parameters[0]/2);

				pdfString = QString(
						"1/(%2*2.5066282746)*exp(-((x-%1)^2)/(2*(%2)^2))")
					.arg(parameters[0])
					.arg(parameters[1]);
				parser.compile(pdfString.toStdString(),pdfExpression);

				cdfString = QString(
						"normCdf((x-(%1))/(%2))")
					.arg(parameters[0])
					.arg(parameters[1]);
				parser.compile(cdfString.toStdString(),cdfExpression);

				parametersCv = 0;
				QString cdfDeviation = QString(
						"(%1)^2*(%3)+(%2)^2*(%4) + 2*(%1)(%2)(%5)")
					.arg(QString("-1/(%2*2.5066282746)*exp(-((x-%1)^2)/(2(%2)^2))")
							.arg(parameters[0])
							.arg(parameters[1])
						)
					.arg(QString("-(x-%1)/((%2)^2*2.5066282746)*exp(-((x-%1)^2)/(2(%2)^2))")
							.arg(parameters[0])
							.arg(parameters[1])
						)
					.arg(parameters[0])
					.arg(parameters[1])
					.arg(parametersCv);
				parser.compile(cdfDeviation.toStdString(), cdfDeviationExpression);
				break;
			}
		case Distribution::ExponentialD:
			{
				parametersCount = 1;
				paremeterNames = {
					"λ",
				};
				parametersDeviationNames =
					paremeterNames;
				parameters = p;
				pdfMax = parameters[0];
				parametersDeviation.push_back(
						std::pow(parameters[0], 2)/2);

				pdfString = QString(
						"(%1)(exp(-(%1)x))")
					.arg(parameters[0], 0, 'f', 6);
				parser.compile(pdfString.toStdString(), pdfExpression);

				cdfString = QString(
						"1-exp(-(%1)x)")
					.arg(parameters[0]);
				parser.compile(cdfString.toStdString(), cdfExpression);

				parametersCv = 0;
				QString cdfDeviation = QString(
						"x^2*exp(-2(%1)x)%2")
					.arg(parameters[0])
					.arg(parametersDeviation[0]);
				parser.compile(cdfDeviation.toStdString(), cdfDeviationExpression);
				break;
			}
		case Distribution::WeibullD:
			{
				parametersCount = 2;
				paremeterNames = {
					"𝛼",
					"β"
				};
				parametersDeviationNames =
					paremeterNames;
				parameters = p;
				pdfMax = parameters[0];
				parametersDeviation.push_back(
						std::pow(parameters[0], 2)/2);

				pdfString = QString(
						"(%1)(exp(-(%1)x))")
					.arg(parameters[0], 0, 'f', 6);
				parser.compile(pdfString.toStdString(), pdfExpression);

				cdfString = QString(
						"1-exp(-(%1)x)")
					.arg(parameters[0]);
				parser.compile(cdfString.toStdString(), cdfExpression);

				parametersCv = 0;
				QString cdfDeviation = QString(
						"x^2*exp(-2(%1)x)%2")
					.arg(parameters[0])
					.arg(parametersDeviation[0]);
				parser.compile(cdfDeviation.toStdString(), cdfDeviationExpression);
				break;
			}
		case Distribution::LogNormalD:
			{
				parametersCount = 2;
				paremeterNames = {
					"m", "σ"
				};
				parametersDeviationNames = {
					"m", "σ²"
				};
				parameters = p;
				pdfMax = 1/(p[2]*2.5066282746);
				parametersDeviation.push_back(
						(exp(4*std::pow(parameters[1],2)) - 
							 8*std::exp(2*std::pow(parameters[0],2) + 
								 16*std::exp(std::pow(parameters[0],2)) - 1)) /
							 (4*size));
				parametersDeviation.push_back(
						(exp(4*std::pow(parameters[1],2)) - 
							 4*std::exp(2*std::pow(parameters[0],2) + 
								 4*std::exp(std::pow(parameters[0],2)) - 1)) /
							 (4*size*std::pow(parameters[0],2)));

				pdfString = QString(
						"1/(x(%2)*2.5066282746)*exp(-((log(x)-%1)^2)/(2*(%2)^2))")
					.arg(parameters[0])
					.arg(parameters[1]);
				parser.compile(pdfString.toStdString(), pdfExpression);

				cdfString = QString(
						"normCdf((log(x)-(%1))/(%2))")
					.arg(parameters[0])
					.arg(parameters[1]);
				parser.compile(cdfString.toStdString(), cdfExpression);

				parametersCv = 
					(-exp(4*std::pow(parameters[1],2)) + 
					 6*std::exp(2*std::pow(parameters[0],2) - 
						 8*std::exp(std::pow(parameters[0],2)) + 3)) /
					(4*size*std::pow(parameters[0],2));
				QString cdfDeviation = QString(
						"(%1)^2*(%3)+(%2)^2*(%4) + 2*(%1)(%2)(%5)")
					.arg(QString("-1/(%2*2.5066282746)*(1-exp(-((log(x)-%1)^2)/(2(%2)^2)))")
							.arg(parameters[0])
							.arg(parameters[1])
						)
					.arg(QString("normCdf((log(x)-%1)/(%2))(1-1/(%2))-1/((%2)*2.5066282746)*((log(x)-%1)/(%2))*exp(-((log(x)-%1)^2)/(2(%2)^2))")
							.arg(parameters[0])
							.arg(parameters[1])
						)
					.arg(parameters[0])
					.arg(parameters[1])
					.arg(parametersCv);
				parser.compile(cdfDeviation.toStdString(), cdfDeviationExpression);
				break;
			}
	}
}

// DistributionReproducer::~DistributionReproducer() {
// 	delete eNormalDistributionCdf;
// }

const QStringList DistributionReproducer::distributionName = {
	"Невідомий",
	"Нормальний",
	"Екпоненціальний",
	"Вейбула",
	"Логнормальний"
};
