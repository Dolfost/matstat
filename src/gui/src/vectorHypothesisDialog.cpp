#include "vectorHypothesisDialog.hpp"
#include "vector/quantile.hpp"
#include <QGroupBox>
#include <QtCore/qstring.h>
#include <cstdlib>
#include <functional>

VectorHypothesisDialog::VectorHypothesisDialog(
	QList<Vector*> v,
	ss::VectorHypothesis::Procedure proc,
	QWidget* parent,
	Qt::WindowFlags flags
) : HypothesisDialogBase<Vector, ss::VectorHypothesis>(v, proc, parent, flags) {

	this->setWindowTitle("Одновимірні гіпотези");
	fill();
}

void VectorHypothesisDialog::fill() {
	switch ((ss::VectorHypothesis::Procedure)procedureComboBox->currentIndex()) {
		case ss::VectorHypothesis::Procedure::tTestDependent: {
			doTest(
				"≤",
				[&](){ return std::abs(h_hypot.tTestDependent()); },
				[&](double a) { return ss::studQuantile(1-a/2, h_hypot[0]->size()-2); },
				std::less_equal<double>(),
				{"середні збігаються", "середні не збігаються"}
			);
			break;
		}

		case ss::VectorHypothesis::Procedure::tTestIndependent: {
			doTest(
				"≤",
				[&](){ return h_hypot.tTestIndependent(); },
				[&](double a) { return ss::studQuantile(1-a/2, h_hypot[0]->size() + h_hypot[1]->size() -2); },
				std::less_equal<double>(),
				{"середні збігаються", "середні не збігаються"}
			);
			break;
		}
		case ss::VectorHypothesis::Procedure::fTest:
			doTest(
				"≤",
				[&](){ return std::abs(h_hypot.fTest()); },
				[&](double a) { return ss::fishQuantile(1-a, h_hypot[0]->size() - 1, h_hypot[1]->size() - 1); },
				std::less_equal<double>(),
				{"дисперсії збігаються", "дисперсії не збігаються"}
			);
			break;
		case ss::VectorHypothesis::Procedure::fTestBartlett: {
			doTest(
				"≤",
				[&](){ return h_hypot.fTestBartlett(); },
				[&](double a) { return ss::pearQuantile(1-a, h_hypot.size() - 1); },
				std::less_equal<double>(),
				{"дисперсії збігаються", "дисперсії не збігаються"}
			);
			break;
		}
		case ss::VectorHypothesis::Procedure::oneWayANOVA: {
			doTest(
				"<",
				[&](){ return h_hypot.oneWayANOVA(); },
				[&](double a) { return ss::fishQuantile(1-a, h_hypot.size() - 1, h_hypot.overallSize() - h_hypot.size()); },
				std::less_equal<double>(),
				{"середні збігаються", "середні не збігаються"}
			);
			break;
		}
		case ss::VectorHypothesis::Procedure::testKS: {
			doTest(
				"≤",
				[&](){ return 1 - h_hypot.testKS(); },
				[&](double a) { return a; },
				std::less_equal<double>(),
				{"вибірки однорідні", "вибірки не однорідні"}
			);
			break;
		}
		case ss::VectorHypothesis::Procedure::testWilcoxon: {
			doTest(
				"≤",
				[&](){ return h_hypot.testWilcoxon(); },
				[&](double a) { return ss::normQuantile(1 - a/2); },
				std::less_equal<double>(),
				{"вибірки однорідні", "вибірки не однорідні"}
			);
			break;
		}
		case ss::VectorHypothesis::Procedure::criteriaU: {
			doTest(
				"≤",
				[&](){ return h_hypot.criteriaU(); },
				[&](double a) { return ss::normQuantile(1 - a/2); },
				std::less_equal<double>(),
				{"вибірки однорідні", "вибірки не однорідні"}
			);
			break;
		}
		case ss::VectorHypothesis::Procedure::rankAveragesDifference: {
			doTest(
				"≤",
				[&](){ return std::abs(h_hypot.rankAveragesDifference()); },
				[&](double a) { return ss::normQuantile(1 - a/2); },
				std::less_equal<double>(),
				{"вибірки однорідні", "вибірки не однорідні"}
			);
			break;
		}
		case ss::VectorHypothesis::Procedure::hTest: {
			doTest(
				"≤",
				[&](){ return h_hypot.hTest(); },
				[&](double a) { return ss::pearQuantile(1 - a, h_hypot.size() - 1); },
				std::less_equal<double>(),
				{"вибірки однорідні", "вибірки не однорідні"}
			);
			break;
		}
		case ss::VectorHypothesis::Procedure::signTest: {
			doTest(
				"<",
				[&](){ return h_hypot.signTest(); },
				[&](double a) { return ss::normQuantile(1 - a); },
				std::less<double>(),
				{"вибірки однорідні", "вибірки не однорідні"}
			);
			break;
		}
		case ss::VectorHypothesis::Procedure::qTest: {
			doTest(
				"≤",
				[&](){ return h_hypot.qTest(); },
				[&](double a) { return ss::pearQuantile(1 - a, h_hypot.size() - 1); },
				std::less_equal<double>(),
				{"всі способи мають однакову імовірність", "всі способи мають різну імовірність"}
			);
			break;
		}
		case ss::VectorHypothesis::Procedure::testAbbe: {
			doTest(
				">",
				[&](){ return h_hypot.testAbbe(); },
				[&](double a) { return ss::normalDistributionCdf(a); },
				std::greater<double>(),
				{"спостереження незалежні", "спостереження залежні"}
			);
			break;
		}
		case ss::VectorHypothesis::Procedure::kolmConsentCriterion: {
			doTest(
				"≤",
				[&](){ return 1 - h_hypot.kolmConsentCriterion() ; },
				[&](double a) { return a; },
				std::less_equal<double>(),
				{"Відтворена та теоретична функція збігається", "Відтворена та теоретична функція не збігається"}
			);
			break;
		}
		case ss::VectorHypothesis::Procedure::pearConsentCriterion: {
			doTest(
				"≤",
				[&](){ return h_hypot.pearConsentCriterion() ; },
				[&](double a) { return ss::pearQuantile(1-a, h_hypot[0]->cs.count()-1); },
				std::less_equal<double>(),
				{"Відтворена та теоретична функція збігається", "Відтворена та теоретична функція не збігається"}
			);
			break;
		}

		case ss::VectorHypothesis::Procedure::Count: {}
	}
}
