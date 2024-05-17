#include "dataVectorSet.hpp"
#include "classSeries.hpp"
#include <QDebug>
#include <QtCore/qlogging.h>
#include <algorithm>
#include <cmath>
#include <iterator>
#include <list>
#include <vector>

QStringList DataVectorSet::procedureName = {
	"Т—тест (залежні віибірки)",
	"Т—тест (незалежні вибірки)",
	"F—тест (2 вибірки)",
	"F—тест (Бартлетта)",
	"Однофакторний дисперсійний аналіз",
	"Тест на однорідність Смірнова-Колмогорова",
	"Критерій суми рангів Вілкоксона",
	"U-критерій Манна-Уїтні",
	"Критерій різниці середніх рангів вибірок",
	"H-критерій Крускала-Уоліса",
};

size_t DataVectorSet::overallSize() {
	size_t s = 0;

	for (auto const& v : *this) {
		s += v->size();
	}

	return s;
}

double DataVectorSet::overallMean() {
	double mean = 0;

	for (auto const& v : *this) {
		mean += v->size()*v->mean();
	}

	return mean / overallSize();
}

double DataVectorSet::intergroupVariation() {
	double s2m = 0,
		   mean = overallMean();

	for (auto const& v : *this) {
		s2m += v->size()*std::pow(v->mean() - mean, 2);
	}

	return s2m/(size() - 1);
}

double DataVectorSet::intragroupVariation() {
	double s2b = 0;

	for (auto const& v : *this) {
		s2b += (v->size() - 1)*v->variance();
	}

	return s2b/(overallSize() - size());
}

std::list<double> DataVectorSet::overallVector() {
	std::list<double> globalVector;

	for (auto const& v : *this) {
		globalVector.splice(globalVector.end(), std::list<double>(v->vector()));
	}

	globalVector.sort();

	return globalVector;
}

std::map<double, double> DataVectorSet::overallRank() {
	std::map<double, double> ranks;

	std::list<double> vector = overallVector();

	size_t r = 1;
	for (auto x = vector.begin(); x != vector.end(); x++) {
		size_t times = 1;
		while (std::next(x) != vector.end() and *std::next(x) == *x) {
			times++;
			x++;
		}

		ranks[*x] = r + 1.0/times;
		r++;
	}

	return ranks;
}

double DataVectorSet::tTestDependent() {
	if (size() != 2)
		throw "Кількість вибірок не рівна 2";

	DataVector* v1 = this->at(0);
	DataVector* v2 = this->at(1);

	if (v1->size() != v2->size())
		throw "Вибірки різного розміру";

	auto y = v2->timeVector().begin();
	std::list<double> z;
	for (auto x = v1->timeVector().begin();
			x != v1->timeVector().end(); x++, y++) {
		z.push_back(*x - *y);
	}

	DataVector zv(z);
	return (zv.mean()*std::sqrt(zv.size()))/zv.standardDeviation(DataVector::SampleM);
}

double DataVectorSet::tTestIndependent() {
	if (size() != 2)
		throw "Кількість вибірок не рівна 2";

	DataVector* v1 = this->at(0);
	DataVector* v2 = this->at(1);

	double z = v1->mean() - v2->mean(),
		   s2 = v1->centralMoment(2, DataVector::SampleM)/v1->size() + 
			   v2->centralMoment(2, DataVector::SampleM)/v2->size(),
		   t;
	if (v1->size() + v2->size() >= 25)
		t = z/std::sqrt(s2);
	else {
		t = std::sqrt(v1->size()*v2->size()/(v1->size() + (double)v2->size()) *
				(v1->mean() - v2->mean())/std::sqrt(
						((v1->size()-1)*v1->centralMoment(2, DataVector::SampleM) + 
						 (v2->size()-1)*v2->centralMoment(2, DataVector::SampleM))) / 
						(v1->size()+v2->size()-2));
	}

	return t;
}

double DataVectorSet::fTest() {
	if (size() != 2)
		throw "Кількість вибірок не рівна 2";

	DataVector* v1 = this->at(0);
	DataVector* v2 = this->at(1);

	double sx2 = v1->variance(),
		   sy2 = v2->variance();

	double f = (sx2 >= sy2 ? sx2/sy2 : sy2/sx2);

	return f;
}

double DataVectorSet::fTestBartlett() {
	double num = 0, den = 0, m = 0;

	for (auto* v : *this) {
		num += (v->size() - 1)*v->variance();
		den += v->size() - 1;
		m += 1.0/(v->size() - 1);
	}

	double S2 = num/den;

	double b = 0, c = 0;

	for (auto* v : *this) {
		b += (v->size() - 1)*log(v->variance()/S2);
	}

	b = -b;
	c = 1 + (1.0/(3*(size() - 1))) * (m - 1.0/den);

	return b/c;
}

double DataVectorSet::oneWayANOVA() {
	return intergroupVariation()/intragroupVariation();
}

double DataVectorSet::testKS() {
	if (size() != 2)
		throw "Кількість вибірок не рівна 2";

	DataVector* v1 = this->at(0);
	DataVector* v2 = this->at(1);

	if (!v1->classSeries() or !v2->classSeries())
		throw "Не всі вибірки були розбиті на класи";

	double from = std::min(v1->min(), v2->min()),
	       to = std::max(v1->max(), v2->max()),
		   step = std::abs(to - from)/overallSize();

	double z = std::abs(v1->classSeries()->eCdf(from)-v2->classSeries()->eCdf(from));
	for (double x = from + step; x <= to + step; x += step) {
		double tmp = std::abs(v1->classSeries()->eCdf(x)-v2->classSeries()->eCdf(x)); if (tmp > z) 
			z = tmp;
	}

	size_t N = std::min(v1->size(), v2->size());
	double z2 = std::pow(z, 2);
	double z4 = std::pow(z2, 2);

	return 1 - std::exp(-2*z2) * (1 - (2*z)/(3*std::sqrt(z)) + 
			((2*z2)/(3*N))*(1 - (2*z2)/3) + 
			((4*z)/(9*std::pow(N, 1.5)))*(0.2 - (19*z2)/15 + (2*z4)/3));
}

double DataVectorSet::testWilcoxon() {
	if (size() != 2)
		throw "Кількість вибірок не рівна 2";

	std::map<double, double> ranks = overallRank();

	DataVector* v1 = this->at(0);
	DataVector* v2 = this->at(1);

	double W = 0;
	for (auto const& x : v1->vector()) 
		W += ranks[x];

	size_t N = overallSize();

	double E = v1->size()*(N+1)/2.0,
		   D = (v1->size()*v2->size()*(N+1))/12.0;

	return (W - E)/std::sqrt(D);
}

double DataVectorSet::criteriaU() {
	if (size() != 2)
		throw "Кількість вибірок не рівна 2";

	DataVector* v1 = this->at(0);
	DataVector* v2 = this->at(1);

	size_t u = 0;

	for (auto const& x : v1->vector()) {
		for (auto const& y : v2->vector()) {
			if (x > y)
				u++;
		}
	}

	size_t N = overallSize();
	double E = (v1->size()*v2->size())/2.0,
		   D = (v1->size()*v2->size()*(N*1))/12.0;

	return (u - E)/std::sqrt(D);
}

double DataVectorSet::rankAveragesDifference() {
	if (size() != 2)
		throw "Кількість вибірок не рівна 2";

	DataVector* v1 = this->at(0);
	DataVector* v2 = this->at(1);

	std::map<double, double> ranks = overallRank();

	double rx = 0, ry = 0;

	for (auto const& x : v1->vector()) {
		rx += ranks[x];
	}
	rx /= v1->size();

	for (auto const& y : v2->vector()) {
		ry += ranks[y];
	}
	ry /= v2->size();

	size_t N = overallSize();

	return (rx - ry)/(N*std::sqrt((N+1.0)/(12.0*v1->size()*v2->size())));
}

double DataVectorSet::hTest() {
	std::map<double, double> ranks = overallRank();
	std::vector<double> w;

	for (auto const& v : *this) {
		double wi = 0;
		for (auto const& x : v->vector())
			wi += ranks[x];
		w.push_back(wi/v->size());
	}

	double N = overallSize();
	double H = 0;
	for (size_t i = 0; i < size(); i++)
		H += (std::pow(w[i]-(N+1)/2, 2)*(1 - at(i)->size()/N)) /
			((N+1)*(N-at(i)->size())/(12.0*at(i)->size()));

	return H;
}
