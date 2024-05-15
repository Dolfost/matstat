#include "dataVectorSet.hpp"
#include <QtCore/qlogging.h>
#include <cmath>
#include <list>

QStringList DataVectorSet::procedureName = {
	"Т—тест (залежні віибірки)",
	"Т—тест (незалежні вибірки)",
	"F—тест (2 вибірки)",
	"F—тест (Бартлетта)",
	"Однофакторний дисперсійний аналіз",
};

size_t DataVectorSet::totalSize() {
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

	return mean / totalSize();
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

	return s2b/(totalSize() - size());
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
	qDebug() << intergroupVariation() << intragroupVariation();
	return intergroupVariation()/intragroupVariation();
}
