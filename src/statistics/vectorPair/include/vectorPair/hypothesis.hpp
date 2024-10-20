#ifndef _VECTOR_PAIR_HYPOTHESIS_HPP_
#define _VECTOR_PAIR_HYPOTHESIS_HPP_

#include "vector/hypothesis.hpp"
#include "vectorPair.hpp"

namespace ss {

class VectorPairHypothesis: public Hypothesis<VectorPair> {
public:

	enum class Procedure {
		tTestCor,
		compareCor,
		tTestCorRatio,
		normalDistrubutionRevalance,
		corSpearman,
		corKendall,
		ConnectionsPhi,
		CouplingQ,
		CouplingY,
		CouplingMeasure,
		RegresionRevalance,
		Count
	};
	
	static const std::vector<std::string> procedureName;

public: // tests
	class TTestCor: public utils::StatisticSingle<double, VectorPairHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} tTestCor = TTestCor(this);

	class CompareCor: public utils::StatisticSingle<double, VectorPairHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} compareCor = CompareCor(this);

	class TTestCorRatio
	: public utils::StatisticSingle<double, VectorPairHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} tTestCorRatio = TTestCorRatio(this);

	class NormalDistribtuionRevelance
	: public utils::StatisticSingle<double, VectorPairHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} normalDistributionRevelance = NormalDistribtuionRevelance(this);

	class CorSpearman
	: public utils::StatisticSingle<double, VectorPairHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} corSpearman = CorSpearman(this);

	class CorKendall
	: public utils::StatisticSingle<double, VectorPairHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} corKendall = CorKendall(this);

	class ConnectionsPhi
	: public utils::StatisticSingle<double, VectorPairHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} connectionsPhi = ConnectionsPhi(this);

	class CouplingQ
	: public utils::StatisticSingle<double, VectorPairHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} couplingQ = CouplingQ(this);

	class CouplingY
	: public utils::StatisticSingle<double, VectorPairHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} couplingY = CouplingY(this);

	class CouplingMeasure
	: public utils::StatisticSingle<double, VectorPairHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} couplingMeasure = CouplingMeasure(this);

	class RegressionRevalance
	: public utils::StatisticSingle<double, VectorPairHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} regressionRevalance = RegressionRevalance(this);


public:
	virtual void invalidate() override;
};

}

#endif // !_VECTOR_PAIR_HYPOTHESIS_HPP_j
