#ifndef _VECTOR_PAIR_HYPOTHESIS_DIALOG_HPP_
#define _VECTOR_PAIR_HYPOTHESIS_DIALOG_HPP_

#include <vectorPair/hypothesis.hpp>
#include <hypothesisDialogBase.hpp>

class VectorPairHypothesisDialog : public HypothesisDialogBase<VectorPair, ss::VectorPairHypothesis> {
public:
	VectorPairHypothesisDialog(
		QList<VectorPair*>,
		ss::VectorPairHypothesis::Procedure = ss::VectorPairHypothesis::Procedure::tTestCor,
		QWidget* = nullptr,
		Qt::WindowFlags = Qt::WindowFlags()
	);

public slots:
	virtual void fill() override;

};

#endif // !_VECTOR_PAIR_HYPOTHESIS_DIALOG_HPP_
