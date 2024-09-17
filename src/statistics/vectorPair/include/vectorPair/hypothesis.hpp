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

public:
	virtual void invalidate() override;
};

}

#endif // !_VECTOR_PAIR_HYPOTHESIS_HPP_j
