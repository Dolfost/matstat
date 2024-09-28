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
		case ss::VectorPairHypothesis::Procedure::compareCor: {
			doTest(
				"<=",
				[&](){ return h_hypot.compareCor(); },
				[&](double a) { return ss::pearQuantile(1-a, h_hypot.size()-1); },
				std::less_equal<double>(),
				{"r₁ = r₂ = … = rₖ (коефіцієнти кореляції збігаються)", "r₁ ≠ r₂ ≠ … ≠ rₖ (коефіцієнти кореляції не збігаються)",}
			);
			break;
		}
		case ss::VectorPairHypothesis::Procedure::tTestCorRatio: {
			doTest(
				"<=",
				[&](){ return h_hypot.tTestCorRatio(); },
				[&](double a) { return ss::fishQuantile(1-a, h_hypot[0]->corRatio.count() - 1, h_hypot[0]->size() - h_hypot[0]->corRatio.count()); },
				std::less_equal<double>(),
				{"кореляційне відноешння не значуще", "кореляційне відношення значуще"}
			);
			break;
		}
		case ss::VectorPairHypothesis::Procedure::normalDistrubutionRevelance: {
			doTest(
				"<=",
				[&](){ return h_hypot.normalDistributionRevelance(); },
				[&](double a) { return ss::pearQuantile(a, h_hypot[0]->cs.countX()*h_hypot[0]->cs.countY()-2); },
				std::less_equal<double>(),
				{
					"відтворення нормального розподілу адекватне", 
					"відтворення нормального розподілу не адекватне", 
				}
			);
			break;
		}

		case ss::VectorPairHypothesis::Procedure::Count: {}
	}
}
