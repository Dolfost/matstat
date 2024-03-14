#include "distributionReproducer.hpp"

#include "exprtk.hpp"
#include "statisticsExprtk.hpp"

#include <QStringList>
#include <QDebug>
#include <QtCore/qalgorithms.h>
#include <QtCore/qlogging.h>
#include <vector>

DistributionReproducer::DistributionReproducer() {
  symbolTable.add_variable("x", x);
  eNormalDistributionCdf = new exprtkNormalDistributionCdf();

  symbolTable.add_function(
      "normCdf", *eNormalDistributionCdf);
  cdfExpression.register_symbol_table(symbolTable);
  pdfExpression.register_symbol_table(symbolTable);
  cdfDeviationExpression.register_symbol_table(symbolTable);
}

exprtk::parser<double> DistributionReproducer::parser;

std::pair<double, double> DistributionReproducer::cdfDeviation(double alpha) {
  return Statistics::thetaDeviation(cdfExpression.value(),
                                    cdfDeviationExpression.value(),
									alpha,
									61,
									true);
}

void DistributionReproducer::setDistribution(Distribution type,
		std::vector<double> p, size_t s) {
	model = type;
	size = s;

	paremeterNames.clear();
	parameters.clear();
	parametersDeviation.clear();

	switch (model) {
		case Distribution::NormalD: 
			{
				parametersCount = 2;
				paremeterNames = {"m", "σ"};
				parametersDeviationNames = paremeterNames;
				parameters = p;
				pdfMax = 1 / (p[1] * 2.5066282746);
				parametersDeviation.push_back(std::pow(parameters[1], 2) / size);
				parametersDeviation.push_back(parameters[0] / 2);

				pdfString = QString("1/(%2*2.5066282746)*exp(-((x-%1)^2)/(2*(%2)^2))")
					.arg(parameters[0])
					.arg(parameters[1]);
				parser.compile(pdfString.toStdString(), pdfExpression);

				cdfString =
					QString("normCdf((x-(%1))/(%2))").arg(parameters[0]).arg(parameters[1]);
				parser.compile(cdfString.toStdString(), cdfExpression);

				parametersCv = 0;
				QString cdfDeviation =
					QString("(%1)^2*(%3)+(%2)^2*(%4) + 2*(%1)(%2)(%5)")
					.arg(QString("-1/(%2*2.5066282746)*exp(-((x-%1)^2)/(2(%2)^2))")
							.arg(parameters[0])
							.arg(parameters[1]))
					.arg(QString(
								"-(x-%1)/((%2)^2*2.5066282746)*exp(-((x-%1)^2)/(2(%2)^2))")
							.arg(parameters[0])
							.arg(parameters[1]))
					.arg(parametersDeviation[0])
					.arg(parametersDeviation[1])
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
				parametersDeviationNames = paremeterNames;
				parameters = p;
				pdfMax = parameters[0];
				parametersDeviation.push_back(std::pow(parameters[0], 2) / 2);

				pdfString = QString("(%1)(exp(-(%1)x))").arg(parameters[0], 0, 'f', 6);
				parser.compile(pdfString.toStdString(), pdfExpression);

				cdfString = QString("1-exp(-(%1)x)").arg(parameters[0], 0, 'f', 6);
				parser.compile(cdfString.toStdString(), cdfExpression);

				parametersCv = 0;
				QString cdfDeviation = QString("x^2*exp(-2(%1)x)%2")
					.arg(parameters[0])
					.arg(parametersDeviation[0]);
				parser.compile(cdfDeviation.toStdString(), cdfDeviationExpression);
				break;
			}
		case Distribution::WeibullD:
			{
				parametersCount = 2;
				paremeterNames = {"𝛼", "β"};
				parametersDeviationNames = paremeterNames;
				parameters.push_back(p[0]);
				parameters.push_back(p[1]);
				// pdfMax = std::pow(parameters[1] / parameters[0], 1 / parameters[1]) *
				// 	std::pow(parameters[1] - 1, (parameters[1] - 1) / parameters[1]) *
				// 	std::exp(-(parameters[1] - 1) / parameters[1]);
				parametersDeviation.push_back(std::pow(parameters[0], 2) / 2);

				pdfString = QString("((%2)/(%1))(x^(%2-1))exp(-(x^(%2))/(%1))")
				// pdfString = QString("((%2)/(%1))((x/%1)^(%2-1))exp(-((x/(%1))^(%2)))")
					.arg(parameters[0], 0, 'f', 20)
					.arg(parameters[1], 0, 'f', 20);
				parser.compile(pdfString.toStdString(), pdfExpression);

				cdfString = QString("1-exp(-(x^(%2))/(%1))")
					.arg(parameters[0], 0, 'f', 6)
					.arg(parameters[1], 0, 'f', 6);
				parser.compile(cdfString.toStdString(), cdfExpression);

				if (p.size() == 2)
					break;

				double DA = (p[6] * p[3]) / (p[4] * p[6] - std::pow(p[5], 2));

				parametersDeviation.push_back(std::exp(-2 * p[2]) * DA);
				parametersDeviation.push_back((p[4] * p[3]) /
						(p[4] * p[6] - std::pow(p[5], 2)));

				double covAb = -(p[5] * p[3]) / (p[4] * p[6] - std::pow(p[5], 2));
				parametersCv = -std::exp(p[2]) * covAb;
				QString cdfDeviation =
					QString("(%1)^2*(%3)+(%2)^2*(%4) + 2*(%1)(%2)(%5)")
					.arg(QString("-((x^(%2))/((%1)^2))*exp(-(x^(%2))/(%1))")
							.arg(parameters[0])
							.arg(parameters[1]))
					.arg(QString("((x^(%2))/(%1))*log(x)*exp(-(x^(%2))/(%1))")
							.arg(parameters[0])
							.arg(parameters[1]))
					.arg(parametersDeviation[0])
					.arg(parametersDeviation[1])
					.arg(parametersCv);
				parser.compile(cdfDeviation.toStdString(), cdfDeviationExpression);

				x = std::pow(abs(parameters[0]*(parameters[1]-1))/parameters[1],
						1/parameters[1]);
				pdfMax = pdfExpression.value();
				break;
			}
		case Distribution::LogNormalD:
			{
				parametersCount = 2;
				paremeterNames = {"m", "σ"};
				parametersDeviationNames = {"m", "σ²"};
				parameters = p;
				double sigma = std::pow(parameters[1], 2);
				parametersDeviation.push_back(
						(exp(4*sigma) -
						 8 * std::exp(2*sigma) +
							 16 * std::exp(sigma) - 9) /
						(4 * size));
				parametersDeviation.push_back(
						(exp(4*sigma) -
						 4 * std::exp(2*sigma) +
							 4 * std::exp(sigma) - 1) /
						(4 * size * sigma));

				pdfString =
					QString("1/(x(%2)*2.5066282746)*exp(-((log(x)-%1)^2)/(2*(%2)^2))")
					.arg(parameters[0])
					.arg(parameters[1]);
				parser.compile(pdfString.toStdString(), pdfExpression);

				cdfString = QString("normCdf((log(x)-(%1))/(%2))")
					.arg(parameters[0])
					.arg(parameters[1]);
				parser.compile(cdfString.toStdString(), cdfExpression);

				parametersCv =
					(-exp(4 * sigma) +
					 6 * std::exp(2 * sigma) -
						 8 * std::exp(sigma) + 3) /
					(4 * size * sigma);
				QString cdfDeviation =
					QString("(%1)^2*(%3)+(%2)^2*(%4) + 2*(%1)(%2)(%5)")
					.arg(QString(
								"(1/((%2)*2.5066282746))*(1-exp(-((log(x)-(%1))^2)/(2(%2)^2)))")
							.arg(parameters[0])
							.arg(parameters[1]))
					.arg(QString("normCdf((log(x)-%1)/(%2))*(1-1/(%2))-(1/"
								"((%2)*2.5066282746))*((log(x)-%1)/"
								"(%2))*exp(-((log(x)-(%1))^2)/(2(%2)^2))")
							.arg(parameters[0])
							.arg(parameters[1]))
					.arg(parametersDeviation[0])
					.arg(parametersDeviation[1])
					.arg(parametersCv);
				parser.compile(cdfDeviation.toStdString(), cdfDeviationExpression);

				x = std::exp(parameters[0] - std::pow(parameters[1], 2));
				pdfMax = pdfExpression.value();
				break;
			}
		case Distribution::UniformD: 
			{
				parametersCount = 2;
				paremeterNames = {"a", "b"};
				parametersDeviationNames = paremeterNames;
				parameters = p;
				pdfMax = 1.25 / (parameters[1]-parameters[0]);
				double
					h1x = 1+3*(parameters[0] + parameters[1]) /
					(parameters[1] - parameters[0]),
					h1x2 = -3/(parameters[1] - parameters[0]),
					h2x = 1-3*(parameters[0] + parameters[1]) /
					(parameters[1] - parameters[0]),
					h2x2 = 3/(parameters[1] - parameters[0]),
					dx = std::pow(parameters[1]-parameters[0], 2)/(12*size),
					covxx2 = (parameters[0] + parameters[1]) * 
						std::pow(parameters[1]-parameters[0], 2)/(12*size),
					dx2 = (std::pow(parameters[1] - parameters[0], 4) + 15*
							std::pow(parameters[0]+parameters[1], 2)*
							std::pow(parameters[1] - parameters[0], 2)) /
						(180*size);

				parametersDeviation.push_back(
						std::pow(h1x, 2)*dx + std::pow(h1x2, 2)*dx2 + 
						2*h1x*h1x2*covxx2
						);
				parametersDeviation.push_back(
						std::pow(h2x, 2)*dx + std::pow(h2x2, 2)*dx2 + 
						2*h2x*h2x2*covxx2
						);

				parametersCv = (h1x*h2x2 + h1x2*h2x)*covxx2;

				pdfString = QString("1/(%2-%1)")
					.arg(parameters[0])
					.arg(parameters[1]);
				parser.compile(pdfString.toStdString(), pdfExpression);

				cdfString =
					QString("(x-%1)/(%2-%1)").arg(parameters[0]).arg(parameters[1]);
				parser.compile(cdfString.toStdString(), cdfExpression);

				QString cdfDeviation =
					QString("((x-%2)^2)/((%2-%1)^4)*%3 + ((x-%1)^2)/((%2-%1)^4)*%4 "
							"- (2((x-%1)(x-%2))/((%2-%1)^4))*%5")
						.arg(parameters[0])
						.arg(parameters[1])
						.arg(parametersDeviation[0])
						.arg(parametersDeviation[1])
						.arg(parametersCv);
				parser.compile(cdfDeviation.toStdString(), cdfDeviationExpression);
				break;
			}
	}
}

DistributionReproducer::~DistributionReproducer() {
  delete eNormalDistributionCdf;
}

const QStringList DistributionReproducer::distributionName = {
    "Невідомий",
	"Нормальний",
	"Екпоненціальний",
	"Вейбула",
	"Логнормальний",
	"Рівномірний",
};
