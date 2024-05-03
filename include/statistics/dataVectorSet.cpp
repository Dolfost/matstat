#include "dataVectorSet.hpp"
#include <cmath>
#include <list>

QStringList DataVectorSet::procedureName = {
	"Т—тест (залежні віибірки)",
	"Т—тест (незалежні вибірки)"
};

double DataVectorSet::tTestDependent() {
	if (size() != 2)
		throw "Кількість вибірок не рівна 2";

	DataVector* v1 = this->at(0);
	DataVector* v2 = this->at(1);

	if (v1->size() != v2->size())
		throw "Вибірки різного розміру";

	auto y = v2->vector().begin();
	std::list<double> z;
	for (auto x = v1->vector().begin();
			x != v1->vector().end(); x++, y++) {
		z.push_back(*x - *y);
	}

	DataVector zv(z);

	return (zv.mean()*std::sqrt(zv.size()))/zv.centralMoment(2, DataVector::SampleM);
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
