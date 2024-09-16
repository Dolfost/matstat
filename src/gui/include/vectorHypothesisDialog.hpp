#ifndef _VECTOR_HYPOTHESIS_DIALOG_HPP_
#define _VECTOR_HYPOTHESIS_DIALOG_HPP_

#include <vector/hypothesis.hpp>
#include <hypothesisDialogBase.hpp>

class VectorHypothesisDialog : public HypothesisDialogBase<Vector, ss::VectorHypothesis> {
public:
	VectorHypothesisDialog(
		QList<Vector*>,
		ss::VectorHypothesis::Procedure = ss::VectorHypothesis::Procedure::tTestDependent,
		QWidget* = nullptr,
		Qt::WindowFlags = Qt::WindowFlags()
	);

public slots:
	virtual void fill() override;

};

#endif // !_VECTOR_HYPOTHESIS_DIALOG_HPP_
