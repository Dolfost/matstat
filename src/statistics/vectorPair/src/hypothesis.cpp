#include<vectorPair/hypothesis.hpp>

namespace ss {

const std::vector<std::string> VectorPairHypothesis::procedureName {
	"Значущість коефіцієнта кореляції",
	"Збіг коефіцієтів кореляції k вибірок",
	"Значущість кореляційного відношення",
};

void VectorPairHypothesis::TTestCor::adapt() {
	if (s_vector->size() != 1)
		throw "Кількість вибірок не рівна 1";

	VectorPair* vp = s_vector->at(0);

	s_value = (vp->cor()*std::sqrt(vp->size() - 2)) /
		std::sqrt(1 - std::pow(vp->cor(), 2));
}

void VectorPairHypothesis::CompareCor::adapt() {
	if (s_vector->size() <= 1)
		throw "Кількість вибірок замала";

	double sumNi = 0;
	double sumZi = 0;
	double sumZi2 = 0;
	for (auto& v : *s_vector) {
		double ni = (v->size() - 3);
		double zi = 0.5+std::log((1+v->cor())/(1-v->cor()));
		sumNi += ni; sumZi += sumNi*zi; sumZi2 += sumNi*std::pow(zi, 2);
	}
	
	s_value = sumZi2 - std::pow(sumZi, 2)/sumNi;
}

void VectorPairHypothesis::TTestCorRatio::adapt() {
	VectorPair* vp = s_vector->at(0);
	double p2 = std::pow(vp->corRatio(), 2);
	s_value = (p2/(1.0-p2))*((double)(vp->size() - vp->corRatio.count())/(vp->corRatio.count() - 1));
}

void VectorPairHypothesis::invalidate() {
	tTestCor.invalidate();
}

}
