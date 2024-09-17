#include "vectorPairHypothesisDialog.hpp"
#include "vector/quantile.hpp"
#include <QGroupBox>
#include <QtCore/qstring.h>
#include <cstdlib>
#include <functional>

VectorPairHypothesisDialog::VectorPairHypothesisDialog(
	QList<VectorPair*> v,
	ss::VectorPairHypothesis::Procedure proc,
	QWidget* parent,
	Qt::WindowFlags flags
) : HypothesisDialogBase<VectorPair, ss::VectorPairHypothesis>(v, proc, parent, flags) {

	this->setWindowTitle("Двовимірні гіпотези");
	fill();
}

void VectorPairHypothesisDialog::fill() {
	switch ((ss::VectorPairHypothesis::Procedure)procedureComboBox->currentIndex()) {
		case ss::VectorPairHypothesis::Procedure::tTestCor: {
			doTest(
				"<=",
				[&](){ return std::abs(h_hypot.tTestCor()); },
				[&](double a) { return ss::studQuantile(1-a/2, h_hypot[0]->size()-2); },
				std::less_equal<double>(),
				{"коефіцієнт кореляції не значущий", "коефіцієнт кореляції значущий"}
			);
			break;
		}

		case ss::VectorPairHypothesis::Procedure::Count: {}
	}
}
