#include<vectorPair/hypothesis.hpp>

namespace ss {

const std::vector<std::string> VectorPairHypothesis::procedureName {
	"Значущість коефіцієнта кореляції"
};

void VectorPairHypothesis::TTestCor::adapt() {
	if (s_vector->size() != 1)
		throw "Кількість вибірок не рівна 1";

	VectorPair* vp = s_vector->at(0);

	s_value = (vp->cor()*std::sqrt(vp->size() - 2)) /
		std::sqrt(1 - std::pow(vp->cor(), 2));
}

void VectorPairHypothesis::invalidate() {
	tTestCor.invalidate();
}

}
