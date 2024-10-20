#include<vectorPair/hypothesis.hpp>

namespace ss {

const std::vector<std::string> VectorPairHypothesis::procedureName {
	"Значущість коефіцієнта кореляції",
	"Збіг коефіцієтів кореляції k вибірок",
	"Значущість кореляційного відношення",
	"Адекватність відтворення нормального розподілу",
	"Значущість рангового коефіцієнта кореляції Спірмена",
	"Значущість рангового коефіцієнта кореляції Кендалла",
	"Значущість коефіцієнта сполучень Ф",
	"Значущість коефіцієнта звʼязку Юла Q",
	"Значущість коефіцієнта звʼязку Юла Y",
	"Міра звʼязаності (таблиця сполучень)",
	"Адекватність відтворення регресії",
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

void VectorPairHypothesis::NormalDistribtuionRevelance::adapt() {
	if (s_vector->size() != 1)
		throw "Кількість вибірок не рівна 1";

	VectorPair& v = *s_vector->at(0);
	s_value = 0;
	for (std::size_t i = 0; i < v.cs.countX(); i++) {
		for (std::size_t j = 0; j < v.cs.countY(); j++) {
			double pij = v.dist.pdf(
				v.x.min() + (i+0.5)*v.cs.stepX(),
				v.y.min() + (j+0.5)*v.cs.stepY()
			) * v.cs.stepX() * v.cs.stepY();
			s_value += std::pow(v.cs.series()[i][j].second - pij, 2)/(pij);
		}
	}
}

void VectorPairHypothesis::TTestCorRatio::adapt() {
	if (s_vector->size() != 1)
		throw "Кількість вибірок не рівна 1";

	VectorPair* vp = s_vector->at(0);
	double p2 = std::pow(vp->corRatio(), 2);
	s_value = (p2/(1.0-p2))*((double)(vp->size() - vp->corRatio.count())/(vp->corRatio.count() - 1));
}

void VectorPairHypothesis::CorSpearman::adapt() {
	if (s_vector->size() != 1)
		throw "Кількість вибірок не рівна 1";

	VectorPair* vp = s_vector->at(0);
	s_value = (vp->corSpearman()*std::sqrt(vp->size()-1)) / 
		std::sqrt(1-std::pow(vp->corSpearman(),2));
}

void VectorPairHypothesis::CorKendall::adapt() {
	if (s_vector->size() != 1)
		throw "Кількість вибірок не рівна 1";

	VectorPair* vp = s_vector->at(0);
	s_value = (2*vp->corKendall()*std::sqrt(vp->size()*(vp->size()-1))) /
		std::sqrt(2*(2*vp->size()+5));
}

void VectorPairHypothesis::ConnectionsPhi::adapt() {
	if (s_vector->size() != 1)
		throw "Кількість вибірок не рівна 1";

	VectorPair& v = *s_vector->at(0);
	v.conTable.connectionsPhi();
	if (v.size() > 40)
		s_value = v.size() * std::pow(v.conTable.connectionsPhi(), 2);
	else 
		s_value = v.size() * std::pow(v.conTable()[0][0]*v.conTable()[1][1] - v.conTable()[0][1]*v.conTable()[1][0] - 0.5, 2)/
			(v.conTable.row()[0]*v.conTable.row()[1]*v.conTable.col()[0]*v.conTable.col()[1]);
}

void VectorPairHypothesis::CouplingQ::adapt() {
	if (s_vector->size() != 1)
		throw "Кількість вибірок не рівна 1";

	VectorPair& v = *s_vector->at(0);
	s_value = 2*v.conTable.copulingQ() / 
		((1-std::pow(v.conTable.copulingQ(),2))*std::sqrt(1/v.conTable()[0][0] + 1/v.conTable()[0][1] + 1/v.conTable()[1][0] + 1/v.conTable()[1][1]));
}

void VectorPairHypothesis::CouplingY::adapt() {
	if (s_vector->size() != 1)
		throw "Кількість вибірок не рівна 1";

	VectorPair& v = *s_vector->at(0);
	s_value = 4*v.conTable.copulingY() / 
		((1-std::pow(v.conTable.copulingY(),2))*std::sqrt(1/v.conTable()[0][0] + 1/v.conTable()[0][1] + 1/v.conTable()[1][0] + 1/v.conTable()[1][1]));
}

void VectorPairHypothesis::CouplingMeasure::adapt() {
	if (s_vector->size() != 1)
		throw "Кількість вибірок не рівна 1";

	VectorPair& v = *s_vector->at(0);
	s_value = 0;
	for (int i = 0; i < v.conTable.row().size(); i++)
		for (int j = 0; j < v.conTable.col().size(); j++) {
			double nij = v.conTable.row()[i]*v.conTable.col()[j]/v.size();
			s_value += std::pow(v.conTable()[i][j] - nij, 2) / nij;
		}
}

void VectorPairHypothesis::RegressionRevalance::adapt() {
	if (s_vector->size() != 1)
		throw "Кількість вибірок не рівна 1";

	VectorPair& v = *s_vector->at(0);

	if (v.reg.model == ss::VectorPair::Regression::Model::Unknown)
		throw "Регресія вибірки не відтворена";

	s_value = std::pow(v.reg.remDispersion/v.y.sd(), 2);
}

void VectorPairHypothesis::invalidate() {
	tTestCor.invalidate();
	compareCor.invalidate();
	normalDistributionRevelance.invalidate();
}

}
