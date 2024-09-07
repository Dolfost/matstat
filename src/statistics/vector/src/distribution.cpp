#include "vector.hpp"

#include <vector.hpp>

#include <QDebug>
#include <QStringList>
#include <QtCore/qalgorithms.h>
#include <QtCore/qlogging.h>
#include <vector>

#include <statistics/quantile.hpp>

#include <random>

namespace ss {

Vector::Distribution::Distribution() {
}

std::pair<double, double> Vector::Distribution::cdfConfidence(double x, double alpha) {
	return thetaDeviation(
		cdf(x), cdfDev(x), alpha, 61, true);
}

void Vector::Distribution::setDistribution(
	Model type,
	std::vector<double> p, size_t s
) {
	model = type;
	size = s;
	domain = {1,1};

	paremeterNames.clear();
	parametersDeviationNames.clear();
	parameters.clear();
	parametersDeviation.clear();

	switch (model) {
		case Model::Normal: {
			parametersCount = 2;
			paremeterNames = {"m", "σ"};
			parametersDeviationNames = paremeterNames;
			parameters = p;
			pdfMax = 1 / (p[1] * 2.5066282746);
			parametersDeviation.push_back(std::pow(parameters[1], 2) / size);
			parametersDeviation.push_back(std::pow(parameters[1], 2) / (2 * size));
			parametersCv = 0;

			double m = parameters[0], o = parameters[1],
			md = parametersDeviation[0], od = parametersDeviation[1];

			d_pdf = [m, o](double x) { 
				return 1/(o*2.5066282746)*std::exp(-(std::pow(x-m,2))/(2*std::pow(o,2)));
			};
			d_cdf = [m, o](double x) {
				return normalDistributionCdf((x-m)/(o));
			};
			d_invCdf = [m, o](double x) {
				return m + o*normQuantile(x);
			};
			d_cdfDev = [m, o, md, od](double x) {
				return 
				std::pow((-1/(o*2.5066282746))*exp(-(std::pow(x-m, 2)/(2*std::pow(o,2)))),2)*(md) + 
				(std::pow((-(x-m)/((std::pow(o,2))*2.5066282746))*exp(-(std::pow(x-m,2))/(2*std::pow(o,2))), 2))*(od);
			};

			break;
		}
		case Model::Exponential: {
			parametersCount = 1;
			paremeterNames = {
				"λ",
			};
			parametersDeviationNames = paremeterNames;
			parameters = p;
			pdfMax = parameters[0];
			parametersDeviation.push_back(std::pow(parameters[0], 2) / size);
			domain.first = 0;
			parametersCv = 0;

			double l = parameters[0], ld = parametersDeviation[0];

			d_pdf = [l](double x) {
				if (x >= 0)
					return l*std::exp(-l*x);
				return 0.0;
			};
			d_cdf = [l](double x) {
				if (x >= 0) 
					return 1-std::exp(-l*x);
				return 0.0;
			};
			d_invCdf = [l](double x) {
				return (1/l)*std::log(1/(1-x));
			};
			d_cdfDev = [l, ld](double x) {
				return std::pow(x,2)*std::exp(-2*l*x)*ld;
			};
			break;
		}
		case Model::Weibull: {
			parametersCount = 2;
			paremeterNames = {"𝛼", "β"};
			parametersDeviationNames = paremeterNames;
			parameters.push_back(p[0]);
			parameters.push_back(p[1]);

			double a = parameters[0], b = parameters[1];

			d_pdf = [a, b](double x) {
				if (x >= 0)
					return ((b)/(a))*std::pow(x,b-1)*std::exp(-(std::pow(x, b))/(a));
				return 0.0;
			};
			d_cdf = [a, b](double x) {
				if (x >= 0)
					return 1-std::exp(-std::pow(x, b)/a);
				return 0.0;
			};
			d_invCdf = [a, b](double x) {
				return std::pow(-a*std::log(1-x), 1/b);
			};

			pdfMax = d_pdf(
				std::pow(abs(a * (b - 1)) / b, 1 / b)
			);
			domain.first = 0;

			if (p.size() == 2)
				break;

			double DA = (p[6] * p[3]) / (p[4] * p[6] - std::pow(p[5], 2));

			parametersDeviation.push_back(std::exp(-2 * p[2]) * DA);
			parametersDeviation.push_back((p[4] * p[3]) /
																 (p[4] * p[6] - std::pow(p[5], 2)));
			double ad = parametersDeviation[0], 
			bd = parametersDeviation[1];

			double covAb = -(p[5] * p[3]) / (p[4] * p[6] - std::pow(p[5], 2));
			parametersCv = -std::exp(p[2]) * covAb;
			double cv = parametersCv;

			d_cdfDev = [a, b, ad, bd, cv](double x) {
				double p1 = -(std::pow(x,b))/(std::pow(a,2))*std::exp(-std::pow(x,b)/(a)),
				p2 = (std::pow(x,b)/(a))*std::log(x)*std::exp(-std::pow(x,b)/(a));
				return  std::pow(p1, 2)*ad + std::pow(p2, 2)*bd + 2*p1*p2*cv;
			};
			break;
		}
		case Model::LogNormal: {
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

			double m = parameters[0], o = parameters[1],
			md = parametersDeviation[0], od = parametersDeviation[1];

			d_pdf = [m, o](double x) {
				if (x > 0)
					return 1/(x*o*2.5066282746) * 
					std::exp(-(std::pow(std::log(x)-m, 2))/(2*std::pow(o,2)));
				return 0.0;
			};
			d_cdf = [m, o](double x) {
				if (x > 0)
					return normalDistributionCdf((std::log(x) - m)/o);
				return 0.0;
			};
			d_invCdf = [m, o](double x) {
				if (x > 0)
					return std::exp(m + 0*normQuantile(x));
				return 0.0;
			};

			parametersCv =
				(-exp(4 * sigma) + 6 * std::exp(2 * sigma) - 8 * std::exp(sigma) + 3) /
				(4 * size * sigma);
			double cv = parametersCv;

			d_cdfDev = [m, o, md, od, cv](double x) {
				double p1 = (1/((o)*2.5066282746))*(1-std::exp(-(std::pow(std::log(x)-(m), 2))/(2*std::pow(o,2)))),
				p2 = normalDistributionCdf((std::log(x)-m)/(o)) * 
					(1-1/(o))-(1/((o)*2.5066282746))*((std::log(x)-m)/(o)) *
					std::exp(-(std::pow(std::log(x)-(m),2))/(2*std::pow(o,2)));
				return std::pow(p1, 2)*md + std::pow(p2, 2)*od + 2*p1*p2*cv;
			};
			
			pdfMax = d_pdf(std::exp(m - std::pow(o, 2)));
			break;
		}
		case Model::Uniform: {
			parametersCount = 2;
			paremeterNames = {"a", "b"};
			parametersDeviationNames = paremeterNames;
			parameters = p;
			double a = p[0], b = p[1];

			pdfMax = 2 / (b - a);

			double h1x = 1 + 3 * (a + b) /
				(b - a),
			h1x2 = -3 / (b - a),
			h2x = 1 - 3 * (a + b) /
				(b - a),
			h2x2 = 3 / (b - a),
			dx = std::pow(b - a, 2) / (12 * size),
			covxx2 = (a + b) *
				std::pow(b - a, 2) / (12 * size),
			dx2 = (std::pow(b - a, 4) +
				15 * std::pow(a + b, 2) *
				std::pow(b - a, 2)) /
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
			double ad = parametersDeviation[0], bd = parametersDeviation[1],
			cv = parametersCv;

			d_pdf = [a, b](double x) {
				if (x >= a and x < b)
					return 1/(b-a);
				return 0.0;
			};
			d_cdf = [a, b](double x) {
				if (x >= a and x < b)
					return (x-a)/(b-a);
				return 0.0;
			};
			d_invCdf = [a, b](double x) {
				return x*(b-a)+a;
			};
			d_cdfDev = [a, b, ad, bd, cv](double x) {
				return std::pow(x-b,2)/std::pow((b-a),4)*ad + std::pow(x-a,2)/std::pow(b-a,4)*bd -
					- (2*((x-a)*(x-b))/(std::pow(b-a,4)))*cv;
			};
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

double Vector::Distribution::pdf(double x) {
	return d_pdf(x);
}

double Vector::Distribution::cdf(double x) {
	return d_cdf(x);
}

double Vector::Distribution::cdfDev(double x) {
	return d_cdfDev(x);
}

double Vector::Distribution::invCdf(double x) {
	return d_invCdf(x);
}

std::list<double> Vector::Distribution::generateSet(Method m, size_t s,
																						double from, double to) {
	size_t setSize = s ? s : size;
	std::list<double> set;

	std::default_random_engine generator;
	generator.seed();
	switch (m) {
		case Method::Inverse: {
			std::uniform_real_distribution<double> distribution(0.0, 1.0);

			for (int i = 0; i < setSize; i++) {
				set.push_back(d_invCdf(distribution(generator)));
			}
		}
		case Method::Plane: {
			std::uniform_real_distribution<double> distributionX(from, to);
			std::uniform_real_distribution<double> distributionY(0, pdfMax);

			while (set.size() < setSize) {
				double x = distributionX(generator);
				double y = d_pdf(x), y1 = distributionY(generator);
				if (y1 <= y)
					set.push_back(x);
			}
		}
		default:
			break;
	}

	return set;
}

Vector::Distribution::~Distribution() {
}

const QStringList Vector::Distribution::distributionName = {
	"Невідомий", "Нормальний",    "Екпоненціальний",
	"Вейбула",   "Логнормальний", "Рівномірний",
};

const QStringList Vector::Distribution::methodName = {
	"Звороьньої функції",
	"Площинний"
};

const QList<QStringList> Vector::Distribution::parameterName = {
	{}, {"m", "σ"}, {"λ"}, {"𝛼", "β"}, {"m", "σ"}, {"a", "b"},
};

}
