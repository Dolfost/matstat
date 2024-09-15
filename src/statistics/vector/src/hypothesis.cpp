#include <vector/hypothesis.hpp>

namespace ss {

const std::vector<std::string> VectorHypothesis::procedureName = {
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
	"Критерій знаків",
	"Q-критерій Кохрена",
	"Критерій Аббе",
};

void VectorHypothesis::OverallSize::adapt() {
	size_t s = 0;

	for (auto const& v : *s_vector) {
		s += v->size();
	}

	s_value = s;
}

void VectorHypothesis::OverallMean::adapt() {
	double mean = 0;

	for (auto const& v : *s_vector) {
		mean += v->size()*v->mean();
	}

	s_value = mean / s_vector->overallSize();
}

void VectorHypothesis::IntergroupVariation::adapt() {
	double s2m = 0,
		   mean = s_vector->overallMean();

	for (auto const& v : *s_vector) {
		s2m += v->size()*std::pow(v->mean() - mean, 2);
	}

	s_value = s2m/(s_vector->size() - 1);
}

void VectorHypothesis::IntragroupVariation::adapt() {
	double s2b = 0;

	for (auto const& v : *s_vector) {
		s2b += (v->size() - 1)*v->variance();
	}

	s_value = s2b/(s_vector->overallSize() - s_vector->size());
}

void VectorHypothesis::OverallRank::adapt() {
	std::list<double> vector = s_vector->overallVector();

	size_t r = 1;
	for (auto x = vector.begin(); x != vector.end(); x++) {
		size_t times = 1;
		while (std::next(x) != vector.end() and *std::next(x) == *x) {
			times++;
			x++;
		}

		s_value[*x] = r + 1.0/times;
		r++;
	}
}

void VectorHypothesis::OverallVector::adapt() {
	for (auto const& v : *s_vector) {
		s_value.splice(s_value.end(), std::list<double>(v->cbegin(), v->cend()));
	}

	s_value.sort();
}

void VectorHypothesis::TTestDependent::adapt() {
	if (s_vector->size() != 2)
		throw "Кількість вибірок не рівна 2";

	Vector* v1 = s_vector->at(0);
	Vector* v2 = s_vector->at(1);

	if (v1->size() != v2->size())
		throw "Вибірки різного розміру";

	auto y = v2->begin();
	std::list<double> z;
	for (auto x = v1->begin();
			x != v1->end(); x++, y++) {
		z.push_back(*x - *y);
	}

	Vector zv(z);
	s_value = (zv.mean()*std::sqrt(zv.size()))/zv.sd(Measure::Sample);
}

void VectorHypothesis::TTestIndependent::adapt() {
	if (s_vector->size() != 2)
		throw "Кількість вибірок не рівна 2";

	Vector* v1 = s_vector->at(0);
	Vector* v2 = s_vector->at(1);

	double z = v1->mean() - v2->mean(),
		   s2 = v1->centralMoment(2, Measure::Sample)/v1->size() + 
			   v2->centralMoment(2, Measure::Sample)/v2->size(),
		   t;
	if (v1->size() + v2->size() >= 25)
		t = z/std::sqrt(s2);
	else {
		t = std::sqrt(v1->size()*v2->size()/(v1->size() + (double)v2->size()) *
				(v1->mean() - v2->mean())/std::sqrt(
						((v1->size()-1)*v1->centralMoment(2, Measure::Sample) + 
						 (v2->size()-1)*v2->centralMoment(2, Measure::Sample))) / 
						(v1->size()+v2->size()-2));
	}

	s_value = t;
}

void VectorHypothesis::FTest::adapt() {
	if (s_vector->size() != 2)
		throw "Кількість вибірок не рівна 2";

	Vector* v1 = s_vector->at(0);
	Vector* v2 = s_vector->at(1);

	double sx2 = v1->variance(),
		   sy2 = v2->variance();

	double f = (sx2 >= sy2 ? sx2/sy2 : sy2/sx2);

	s_value = f;
}

void VectorHypothesis::FTestBartlett::adapt() {
	double num = 0, den = 0, m = 0;

	for (auto* v : *s_vector) {
		num += (v->size() - 1)*v->variance();
		den += v->size() - 1;
		m += 1.0/(v->size() - 1);
	}

	double S2 = num/den;

	double b = 0, c = 0;

	for (auto* v : *s_vector) {
		b += (v->size() - 1)*log(v->variance()/S2);
	}

	b = -b;
	c = 1 + (1.0/(3*(s_vector->size() - 1))) * (m - 1.0/den);

	s_value = b/c;
}

void VectorHypothesis::OneWayANOVA::adapt() {
	s_value = s_vector->intergroupVariation()/s_vector->intragroupVariation();
}

void VectorHypothesis::TestKS::adapt() {
	if (s_vector->size() != 2)
		throw "Кількість вибірок не рівна 2";

	Vector* v1 = s_vector->at(0);
	Vector* v2 = s_vector->at(1);

	// if (!v1.classSeries or !v2->classSeries())
	// 	throw "Не всі вибірки були розбиті на класи";

	double from = std::min(v1->min(), v2->min()),
	       to = std::max(v1->max(), v2->max()),
		   step = std::abs(to - from)/s_vector->overallSize();

	double z = std::abs(v1->cs.cdf(from)-v2->cs.cdf(from));
	for (double x = from + step; x <= to + step; x += step) {
		double tmp = std::abs(v1->cs.cdf(x)-v2->cs.cdf(x)); if (tmp > z) 
			z = tmp;
	}

	size_t N = std::min(v1->size(), v2->size());
	double z2 = std::pow(z, 2);
	double z4 = std::pow(z2, 2);

	s_value = 1 - std::exp(-2*z2) * (1 - (2*z)/(3*std::sqrt(z)) + 
			((2*z2)/(3*N))*(1 - (2*z2)/3) + 
			((4*z)/(9*std::pow(N, 1.5)))*(0.2 - (19*z2)/15 + (2*z4)/3));
}

void VectorHypothesis::TestWilcoxon::adapt() {
	if (s_vector->size() != 2)
		throw "Кількість вибірок не рівна 2";

	std::map<double, double> ranks = s_vector->overallRank();

	Vector* v1 = s_vector->at(0);
	Vector* v2 = s_vector->at(1);

	double W = 0;
	for (auto const& x : *v1) 
		W += ranks[x];

	size_t N = s_vector->overallSize();

	double E = v1->size()*(N+1)/2.0,
		   D = (v1->size()*v2->size()*(N+1))/12.0;

	s_value = (W - E)/std::sqrt(D);
}

void VectorHypothesis::CriteriaU::adapt() {
	if (s_vector->size() != 2)
		throw "Кількість вибірок не рівна 2";

	Vector* v1 = s_vector->at(0);
	Vector* v2 = s_vector->at(1);

	size_t u = 0;

	for (auto const& x : *v1) {
		for (auto const& y : *v2) {
			if (x > y)
				u++;
		}
	}

	size_t N = s_vector->overallSize();
	double E = (v1->size()*v2->size())/2.0,
		   D = (v1->size()*v2->size()*(N*1))/12.0;

	s_value = (u - E)/std::sqrt(D);
}

void VectorHypothesis::RankAveragesDifference::adapt() {
	if (s_vector->size() != 2)
		throw "Кількість вибірок не рівна 2";

	Vector* v1 = s_vector->at(0);
	Vector* v2 = s_vector->at(1);

	std::map<double, double> ranks = s_vector->overallRank();

	double rx = 0, ry = 0;

	for (auto const& x : *v1) {
		rx += ranks[x];
	}
	rx /= v1->size();

	for (auto const& y : *v2) {
		ry += ranks[y];
	}
	ry /= v2->size();

	size_t N = s_vector->overallSize();

	s_value = (rx - ry)/(N*std::sqrt((N+1.0)/(12.0*v1->size()*v2->size())));
}

void VectorHypothesis::HTest::adapt() {
	std::map<double, double> ranks = s_vector->overallRank();
	std::vector<double> w;

	for (auto const& v : *s_vector) {
		double wi = 0;
		for (auto const& x : *v)
			wi += ranks[x];
		w.push_back(wi/v->size());
	}

	double N = s_vector->overallSize();
	double H = 0;
	for (size_t i = 0; i < s_vector->size(); i++)
		H += (std::pow(w[i]-(N+1)/2, 2)*(1 - s_vector->at(i)->size()/N)) /
			((N+1)*(N-s_vector->at(i)->size())/(12.0*s_vector->at(i)->size()));

	s_value = H;
}

void VectorHypothesis::SignTest::adapt() {
	if (s_vector->size() != 2)
		throw "Кількість вибірок не рівна 2";

	Vector* v1 = s_vector->at(0);
	Vector* v2 = s_vector->at(1);

	if (v1->size() != v2->size())
		throw "Вибірки різного розміру";

	auto iv1 = v1->begin();
	auto iv2 = v2->begin();
	size_t n = v1->size();

	size_t S = 0;
	while (iv1 != v1->end() and iv2 != v2->end()) {
		double diff = *iv1 - *iv2;
		if (diff > 0)
			S++;
		else if (diff == 0)
			n--;

		iv1++, iv2++;
	}

	s_value = (2*S - 1 - n)/std::sqrt(n);
}

void VectorHypothesis::QTest::adapt() {
	size_t n = s_vector->at(0)->size();

	for (size_t i = 1; i < s_vector->size(); i++)
		if (s_vector->at(i)->size() != n)
			throw "Вибірки не однакового розміру";

	std::vector<size_t> u(n), T(s_vector->size());

	size_t i = 0, j;
	for (auto const& v : *s_vector) {
		j = 0;
		for (auto const& x : *v) {
			if (x == 1) {
				T[i]++;
				u[j]++;
			}
			j++;
		}
		i++;
	}

	Vector tVector(std::list<double>(T.cbegin(), T.cend()));

	double uSum = 0, uSum2 = 0;
	for (auto const& ui : u) {
		uSum += ui;
		uSum2 += std::pow(ui, 2);
	}

	s_value = (std::pow(s_vector->size(), 2)*(s_vector->size() - 1) * tVector.centralMoment(2)) /
		(s_vector->size()*uSum - uSum2);
}

void VectorHypothesis::TestAbbe::adapt() {
	if (s_vector->size() != 1)
		throw "Кількість вибірок не рівна 1";

	Vector* v = s_vector->at(0);

	double d2 = 0;
	auto i1 = v->cbegin(),
		 i2 = std::next(i1);

	while (i2 != v->cend()) {
		d2 += std::pow(*i2 - *i1, 2);
		i1++, i2++;
	}
	d2 /= (v->size() - 1);

	double q = d2/(2*v->variance());
	double u = (q - 1)*std::sqrt((std::pow(v->size(), 2) - 1)/(v->size() - 2));

	s_value = u;
}

void VectorHypothesis::invalidate() {
	tTestDependent.invalidate();
	tTestIndependent.invalidate();
	fTest.invalidate();
	fTestBartlett.invalidate();
	oneWayANOVA.invalidate();
	testKS.invalidate();
	testWilcoxon.invalidate();
	criteriaU.invalidate();
	rankAveragesDifference.invalidate();
	hTest.invalidate();
	signTest.invalidate();
	qTest.invalidate();
	testAbbe.invalidate();
	overallRank.invalidate();
	overallVector.invalidate();
	intragroupVariation.invalidate();
	intergroupVariation.invalidate();
	overallMean.invalidate();
	overallSize.invalidate();
}

}
