#ifndef _VECTOR_SET_HYPOTHESIS_HPP_
#define _VECTOR_SET_HYPOTHESIS_HPP_

#include "vector/hypothesis.hpp"
#include "vectorChain.hpp"

namespace ss {

class VectorSetHypothesis: public Hypothesis<VectorChain> {
public:

	enum class Procedure {
		tTestCor,
		Count
	};
	
	static const std::vector<std::string> procedureName;

public: // tests
	class TTestCor: public utils::StatisticSingle<double, VectorSetHypothesis> {
	public:
		using StatisticSingle::StatisticSingle;
	protected:
		virtual void adapt() override;
	} tTestCor = TTestCor(this);

public:
	virtual void invalidate() override;
};

}

#endif // !_VECTOR_PAIR_HYPOTHESIS_HPP_j
