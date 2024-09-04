#include "distributionReproducer.hpp"

#include "exprtk.hpp"
#include "statistics/exprtk_utils.hpp"
#include <vector.hpp>

#include <QDebug>
#include <QStringList>
#include <QtCore/qalgorithms.h>
#include <QtCore/qlogging.h>
#include <vector>

#include <random>

namespace ss {

DistributionReproducer::DistributionReproducer() {
  symbolTable.add_variable("x", x);
  eNormalDistributionCdf = new ss::exprtk::NormalDistributionCdf();
  eNormQuantile = new ss::exprtk::NormQuantile();

  symbolTable.add_function("normCdf", *eNormalDistributionCdf);
  symbolTable.add_function("normQuantile", *eNormQuantile);
  cdfExpression.register_symbol_table(symbolTable);
  pdfExpression.register_symbol_table(symbolTable);
  invCdfExpression.register_symbol_table(symbolTable);
  cdfDeviationExpression.register_symbol_table(symbolTable);
}

::exprtk::parser<double> DistributionReproducer::parser;

std::pair<double, double> DistributionReproducer::cdfConfidence(double x1, double alpha) {
	x = x1;
	return thetaDeviation(
			cdfExpression.value(), cdfDeviationExpression.value(), alpha, 61, true);
}

void DistributionReproducer::setDistribution(Distribution type,
                                             std::vector<double> p, size_t s) {
  model = type;
  size = s;
  domain = {1,1};

  paremeterNames.clear();
  parametersDeviationNames.clear();
  parameters.clear();
  parametersDeviation.clear();

  switch (model) {
  case Distribution::NormalD: {
    parametersCount = 2;
    paremeterNames = {"m", "σ"};
    parametersDeviationNames = paremeterNames;
    parameters = p;
    pdfMax = 1 / (p[1] * 2.5066282746);
    parametersDeviation.push_back(std::pow(parameters[1], 2) / size);
    parametersDeviation.push_back(std::pow(parameters[1], 2) / (2 * size));

    pdfString = QString("1/(%2*2.5066282746)*exp(-((x-%1)^2)/(2*(%2)^2))")
                    .arg(parameters[0])
                    .arg(parameters[1]);
    parser.compile(pdfString.toStdString(), pdfExpression);

    cdfString =
        QString("normCdf((x-(%1))/(%2))").arg(parameters[0]).arg(parameters[1]);
    parser.compile(cdfString.toStdString(), cdfExpression);

    invCdfString = QString("%1 + %2*normQuantile(x)")
                       .arg(parameters[0], 0, 'f', 6)
                       .arg(parameters[1], 0, 'f', 6);
    parser.compile(invCdfString.toStdString(), invCdfExpression);

    parametersCv = 0;
    QString cdfDeviation =
        QString("((%1)^2)*(%3)+((%2)^2)*(%4)") // + 0 
            .arg(QString("(-1/(%2*2.5066282746))*exp(-((x-%1)^2)/(2(%2)^2))")
                     .arg(parameters[0])
                     .arg(parameters[1]))
            .arg(QString("(-(x-%1)/(((%2)^2)*2.5066282746))*exp(-((x-%1)^2)/"
                         "(2(%2)^2))")
                     .arg(parameters[0])
                     .arg(parameters[1]))
            .arg(parametersDeviation[0])
            .arg(parametersDeviation[1]);
    parser.compile(cdfDeviation.toStdString(), cdfDeviationExpression);
    break;
  }
  case Distribution::ExponentialD: {
    parametersCount = 1;
    paremeterNames = {
        "λ",
    };
    parametersDeviationNames = paremeterNames;
    parameters = p;
    pdfMax = parameters[0];
    parametersDeviation.push_back(std::pow(parameters[0], 2) / size);

    pdfString = QString("if (x >= 0) (%1)(exp(-(%1)x)); else 0;")
                    .arg(parameters[0], 0, 'f', 6);
    parser.compile(pdfString.toStdString(), pdfExpression);

    cdfString = QString("if (x >= 0) 1-exp(-(%1)x); else 0;")
                    .arg(parameters[0], 0, 'f', 6);
    parser.compile(cdfString.toStdString(), cdfExpression);

    invCdfString = QString("(1/%1)log(1/(1-x))").arg(parameters[0], 0, 'f', 6);
    parser.compile(invCdfString.toStdString(), invCdfExpression);

	domain.first = 0;
    parametersCv = 0;
    QString cdfDeviation = QString("(x^2)*exp(-2(%1)x)(%2)")
                               .arg(parameters[0])
                               .arg(parametersDeviation[0]);
    parser.compile(cdfDeviation.toStdString(), cdfDeviationExpression);
    break;
  }
  case Distribution::WeibullD: {
    parametersCount = 2;
    paremeterNames = {"𝛼", "β"};
    parametersDeviationNames = paremeterNames;
    parameters.push_back(p[0]);
    parameters.push_back(p[1]);
    // pdfMax = std::pow(parameters[1] / parameters[0], 1 / parameters[1]) *
    // 	std::pow(parameters[1] - 1, (parameters[1] - 1) / parameters[1]) *
    // 	std::exp(-(parameters[1] - 1) / parameters[1]);

    pdfString =
        QString("if (x >= 0) ((%2)/(%1))(x^(%2-1))exp(-(x^(%2))/(%1)); else 0;")
            // pdfString =
            // QString("((%2)/(%1))((x/%1)^(%2-1))exp(-((x/(%1))^(%2)))")
            .arg(parameters[0], 0, 'f', 20)
            .arg(parameters[1], 0, 'f', 20);
    parser.compile(pdfString.toStdString(), pdfExpression);

    cdfString = QString("if (x >= 0) 1-exp(-(x^(%2))/(%1)); else 0;")
                    .arg(parameters[0], 0, 'f', 6)
                    .arg(parameters[1], 0, 'f', 6);
    parser.compile(cdfString.toStdString(), cdfExpression);

    invCdfString = QString("(-%1*log(1-x))^(1/%2)")
                       .arg(parameters[0], 0, 'f', 6)
                       .arg(parameters[1], 0, 'f', 6);
    parser.compile(invCdfString.toStdString(), invCdfExpression);

    x = std::pow(abs(parameters[0] * (parameters[1] - 1)) / parameters[1],
                 1 / parameters[1]);
    pdfMax = pdfExpression.value();
	domain.first = 0;

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

    break;
  }
  case Distribution::LogNormalD: {
    parametersCount = 2;
    paremeterNames = {"m", "σ"};
    parametersDeviationNames = {"m", "σ²"};
    parameters = p;
    double sigma = std::pow(parameters[1], 2);
    parametersDeviation.push_back(
        (exp(4 * sigma) - 8 * std::exp(2 * sigma) + 16 * std::exp(sigma) - 9) /
        (4 * size));
    parametersDeviation.push_back(
        (exp(4 * sigma) - 4 * std::exp(2 * sigma) + 4 * std::exp(sigma) - 1) /
        (4 * size * sigma));

    pdfString =
        QString(
            "if (x > 0) "
            "1/(x(%2)*2.5066282746)*exp(-((log(x)-%1)^2)/(2*(%2)^2)); else 0;")
            .arg(parameters[0])
            .arg(parameters[1]);
    parser.compile(pdfString.toStdString(), pdfExpression);

    cdfString = QString("if (x > 0) normCdf((log(x)-(%1))/(%2)); else 0;")
                    .arg(parameters[0])
                    .arg(parameters[1]);
    parser.compile(cdfString.toStdString(), cdfExpression);

    invCdfString = QString("if (x > 0) exp(%1 + %2*normQuantile(x)); else 0;")
                       .arg(parameters[0], 0, 'f', 6)
                       .arg(parameters[1], 0, 'f', 6);
    parser.compile(invCdfString.toStdString(), invCdfExpression);

    parametersCv =
        (-exp(4 * sigma) + 6 * std::exp(2 * sigma) - 8 * std::exp(sigma) + 3) /
        (4 * size * sigma);
    QString cdfDeviation =
        QString("(%1)^2*(%3)+(%2)^2*(%4) + 2*(%1)(%2)(%5)")
            .arg(QString("(1/((%2)*2.5066282746))*(1-exp(-((log(x)-(%1))^2)/"
                         "(2(%2)^2)))")
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
  case Distribution::UniformD: {
    parametersCount = 2;
    paremeterNames = {"a", "b"};
    parametersDeviationNames = paremeterNames;
    parameters = p;
    pdfMax = 2 / (parameters[1] - parameters[0]);
    double h1x = 1 + 3 * (parameters[0] + parameters[1]) /
                         (parameters[1] - parameters[0]),
           h1x2 = -3 / (parameters[1] - parameters[0]),
           h2x = 1 - 3 * (parameters[0] + parameters[1]) /
                         (parameters[1] - parameters[0]),
           h2x2 = 3 / (parameters[1] - parameters[0]),
           dx = std::pow(parameters[1] - parameters[0], 2) / (12 * size),
           covxx2 = (parameters[0] + parameters[1]) *
                    std::pow(parameters[1] - parameters[0], 2) / (12 * size),
           dx2 = (std::pow(parameters[1] - parameters[0], 4) +
                  15 * std::pow(parameters[0] + parameters[1], 2) *
                      std::pow(parameters[1] - parameters[0], 2)) /
                 (180 * size);

    parametersDeviation.push_back(std::pow(h1x, 2) * dx +
                                  std::pow(h1x2, 2) * dx2 +
                                  2 * h1x * h1x2 * covxx2);
    parametersDeviation.push_back(std::pow(h2x, 2) * dx +
                                  std::pow(h2x2, 2) * dx2 +
                                  2 * h2x * h2x2 * covxx2);

    // parametersCv = (h1x * h2x2 + h1x2 * h2x) * covxx2;
    parametersCv = h1x * h2x * dx + h1x2 * h2x2 * dx2 +
		(h1x*h2x2 + h1x2*h2x)*covxx2;

    pdfString = QString("if (x >= %1 and x < %2) 1/(%2-%1); else 0;")
                    .arg(parameters[0])
                    .arg(parameters[1]);
    parser.compile(pdfString.toStdString(), pdfExpression);

    cdfString = QString("if (x >= %1 and x < %2) (x-%1)/(%2-%1); else 0;")
                    .arg(parameters[0])
                    .arg(parameters[1]);
    parser.compile(cdfString.toStdString(), cdfExpression);

    invCdfString = QString("x(%2-%1)+%1")
                       .arg(parameters[0], 0, 'f', 6)
                       .arg(parameters[1], 0, 'f', 6);
    parser.compile(invCdfString.toStdString(), invCdfExpression);

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
  default:
    break;
  }

  if (domain.first != domain.second) {
	  double x = domain.first, f = 0;
	  while (std::abs(f) < 0.01) {
		  x += 0.01;
		  f = cdf(x);
	  }
	  domain.first = x;

	  while (std::abs(f - 1) > 0.01) {
		  x += 0.01;
		  f = cdf(x);
	  }
	  domain.second = x;
  }
}

double DistributionReproducer::pdf(double x1) {
  x = x1;
  return pdfExpression.value();
}

double DistributionReproducer::cdf(double x1) {
  x = x1;
  return cdfExpression.value();
}

double DistributionReproducer::cdfDev(double x1) {
  x = x1;
  return cdfDeviationExpression.value();
}

double DistributionReproducer::invCdf(double x1) {
  x = x1;
  return invCdfExpression.value();
}

std::list<double> DistributionReproducer::generateSet(Method m, size_t s,
                                                      double from, double to) {
  size_t setSize = s ? s : size;
  std::list<double> set;

  std::default_random_engine generator;
  generator.seed();
  switch (m) {
  case Method::InverseM: {
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    for (int i = 0; i < setSize; i++) {
      x = distribution(generator);
      set.push_back(invCdfExpression.value());
    }
  }
  case Method::PlaneM: {
    std::uniform_real_distribution<double> distributionX(from, to);
    std::uniform_real_distribution<double> distributionY(0, pdfMax);

    while (set.size() < setSize) {
      x = distributionX(generator);
      double y = pdfExpression.value(), y1 = distributionY(generator);
      if (y1 <= y)
        set.push_back(x);
    }
  }
  default:
    break;
  }

  return set;
}

DistributionReproducer::~DistributionReproducer() {
	delete eNormalDistributionCdf;
	delete eNormQuantile;
}

const QStringList DistributionReproducer::distributionName = {
    "Невідомий", "Нормальний",    "Екпоненціальний",
    "Вейбула",   "Логнормальний", "Рівномірний",
};

const QStringList DistributionReproducer::methodName = {
	"Звороьньої функції",
	"Площинний"
};

const QList<QStringList> DistributionReproducer::parameterName = {
    {}, {"m", "σ"}, {"λ"}, {"𝛼", "β"}, {"m", "σ"}, {"a", "b"},
};

}
