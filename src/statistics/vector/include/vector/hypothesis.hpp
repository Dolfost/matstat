#ifndef _VECTOR_HYPOTHESIS_HPP_
#define _VECTOR_HYPOTHESIS_HPP_

#include <vector.hpp>
#include <vector/utils.hpp>

namespace ss {

template<class V>
class Hypothesis: protected std::vector<V*> {
public:
	using std::vector<V*>::vector;
};

class VectorHypothesis: protected std::vector<Vector*> {
public:
	using std::vector<Vector*>::vector;
	using std::vector<Vector*>::operator[];
	using std::vector<Vector*>::size;
	using std::vector<Vector*>::erase;
	using std::vector<Vector*>::cbegin;
	using std::vector<Vector*>::cend;
	using std::vector<Vector*>::begin;
	using std::vector<Vector*>::end;
	using std::vector<Vector*>::push_back;

	enum class Procedure {
		tTestDependent,
		tTestIndependent,
		fTest,
		fTestBartlett,
		oneWayANOVA,
		testKS,
		testWilcoxon,
		criteriaU,
		rankAveragesDifference,
		hTest,
		signTest,
		qTest,
		testAbbe,
		Count
	};
	
	static const std::vector<std::string> procedureName;

public: // tests
	class TTestDependent: public utils::StatisticSingle<double, VectorHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} tTestDependent = TTestDependent(this);

	class TTestIndependent: public utils::StatisticSingle<double, VectorHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} tTestIndependent = TTestIndependent(this);

	class FTest: public utils::StatisticSingle<double, VectorHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} fTest = FTest(this);

	class FTestBartlett: public utils::StatisticSingle<double, VectorHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} fTestBartlett = FTestBartlett(this);

	class OneWayANOVA: public utils::StatisticSingle<double, VectorHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} oneWayANOVA = OneWayANOVA(this);

	class TestKS: public utils::StatisticSingle<double, VectorHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} testKS = TestKS(this);

	class TestWilcoxon: public utils::StatisticSingle<double, VectorHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} testWilcoxon = TestWilcoxon(this);

	class CriteriaU: public utils::StatisticSingle<double, VectorHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} criteriaU = CriteriaU(this);

	class RankAveragesDifference: public utils::StatisticSingle<double, VectorHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} rankAveragesDifference = RankAveragesDifference(this);

	class HTest: public utils::StatisticSingle<double, VectorHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} hTest = HTest(this);
	
	class SignTest: public utils::StatisticSingle<double, VectorHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} signTest = SignTest(this);

	class QTest: public utils::StatisticSingle<double, VectorHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} qTest = QTest(this);

	class TestAbbe: public utils::StatisticSingle<double, VectorHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} testAbbe = TestAbbe(this);

	class OverallRank: public utils::StatisticContainer<std::map<double, double>, VectorHypothesis> {
	public:
		using StatisticContainer::StatisticContainer;
	protected:
		virtual void adapt() override;
	} overallRank = OverallRank(this);

	class OverallVector: public utils::StatisticContainer<std::list<double>, VectorHypothesis> {
	public:
		using StatisticContainer::StatisticContainer;
	protected:
		virtual void adapt() override;
	} overallVector = OverallVector(this);

	class IntragroupVariation: public utils::StatisticSingle<double, VectorHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} intragroupVariation = IntragroupVariation(this);

	class IntergroupVariation: public utils::StatisticSingle<double, VectorHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} intergroupVariation = IntergroupVariation(this);

	class OverallMean: public utils::StatisticSingle<double, VectorHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} overallMean = OverallMean(this);

	class OverallSize: public utils::StatisticSingle<double, VectorHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} overallSize = OverallSize(this);

public:
	void invalidate();
};

}

#endif // !_VECTOR_HYPOTHESIS_HPP_j
