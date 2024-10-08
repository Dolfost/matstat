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

		// 				criteria = vectorSet.tTestDependent();
		// 				quantile = ss::studQuantile(1-critLevel/2, vectorSet[0]->size()-2);
		// 				cond = QString("|%1| < t(%2,%3) = %4")
		// 					.arg(criteria, 3, 'f')
		// 					.arg(1-critLevel/2, 3, 'f')
		// 					.arg(vectorSet[0]->size()-2)
		// 					.arg(quantile, 3, 'f');
		// 				accepted = std::abs(criteria) <= quantile;
		// 				implies = accepted ? "середні збігаються" : "середні не збігаються";
		// 				qf = [=](double a) { 
		// 					return std::abs(criteria) <= ss::studQuantile(1-a/2, vectorSet[0]->size()-2); 
		// 				};
		// 				break;
		// 			}
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
	// 		case ss::VectorHypothesis::Procedure::tTestIndependent:
	// 			{
	// 				criteria = vectorSet.tTestIndependent();
	// 				quantile = ss::studQuantile(1-critLevel/2,
	// 						vectorSet[0]->size() + vectorSet[1]->size() - 2);
	// 				cond = QString("%1 < t(%2,%3) = %4")
	// 					.arg(criteria, 3, 'f')
	// 					.arg(1-critLevel/2, 3, 'f')
	// 					.arg(vectorSet[0]->size() + vectorSet[1]->size() - 2)
	// 					.arg(quantile, 3, 'f');
	// 				accepted = criteria <= quantile;
	// 				implies = accepted ? "середні збігаються" : "середні не збігаються";
	// 				qf = [=](double a) { 
	// 					return criteria <= ss::studQuantile(1-a/2,
	// 						vectorSet[0]->size() + vectorSet[1]->size() - 2);
	// 				};
	// 				break;
	// 			}
		case ss::VectorHypothesis::Procedure::fTest:
			doTest(
				"≤",
				[&](){ return std::abs(h_hypot.fTest()); },
				[&](double a) { return ss::fishQuantile(1-a, h_hypot[0]->size() - 1, h_hypot[1]->size() - 1); },
				std::less_equal<double>(),
				{"дисперсії збігаються", "дисперсії не збігаються"}
			);
			break;
	// 		case ss::VectorHypothesis::Procedure::fTest:
	// 			{
	// 				criteria = vectorSet.fTest();
	// 				quantile = ss::fishQuantile(1-critLevel,
	// 						vectorSet[0]->size()-1, vectorSet[1]->size() - 1);
	// 				cond = QString("|%1| < f(%2,%3,%4) = %5")
	// 					.arg(criteria, 3, 'f')
	// 					.arg(1-critLevel, 3, 'f')
	// 					.arg(vectorSet[0]->size() - 1)
	// 					.arg(vectorSet[1]->size() - 1)
	// 					.arg(quantile, 3, 'f');
	// 				accepted = std::abs(criteria) <= quantile;
	// 				implies = accepted ? "дисперсії збігаються" : "дисперсії не збігаються";
	// 				qf = [=](double a) { 
	// 					return std::abs(criteria) <= ss::fishQuantile(1-a,
	// 						vectorSet[0]->size()-1, vectorSet[1]->size() - 1);
	// 				};
	// 				break;
	// 			}
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
	// 		case ss::VectorHypothesis::Procedure::fTestBartlett:
	// 			{
	// 				criteria = vectorSet.fTestBartlett();
	// 				quantile = ss::pearQuantile(1-critLevel,
	// 						vectorSet.size()-1);
	// 				cond = QString("%1 < 𝜒(%2,%3) = %4")
	// 					.arg(criteria, 3, 'f')
	// 					.arg(1-critLevel, 3, 'f')
	// 					.arg(vectorSet.size() - 1)
	// 					.arg(quantile, 3, 'f');
	// 				accepted = criteria <= quantile;
	// 				implies = accepted ? "дисперсії збігаються" : "дисперсії не збігаються";
	// 				qf = [=](double a) { 
	// 					return criteria <= ss::pearQuantile(1-a,
	// 						vectorSet.size()-1);
	// 				};
	// 				break;
	// 			}
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
	// 		case ss::VectorHypothesis::Procedure::oneWayANOVA:
	// 			{
	// 				criteria = vectorSet.oneWayANOVA();
	// 				double v1 = vectorSet.size() - 1,
	// 					   v2 = vectorSet.overallSize() - vectorSet.size();
	// 				quantile = ss::fishQuantile(1-critLevel,
	// 						v1, v2);
	// 				cond = QString("%1 < f(%2,%3,%4) = %5")
	// 					.arg(criteria, 3, 'f')
	// 					.arg(1-critLevel, 3, 'f')
	// 					.arg(v1)
	// 					.arg(v2)
	// 					.arg(quantile, 3, 'f');
	// 				accepted = criteria <= quantile;
	// 				implies = accepted ? "середні збігаються" : "середні не збігаються";
	// 				qf = [=](double a) { 
	// 					return criteria <= ss::fishQuantile(1-a,
	// 						v1, v2);
	// 				};
	// 				break;
	// 			}
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
	// 		case ss::VectorHypothesis::Procedure::testKS:
	// 			{
	// 				criteria = 1 - vectorSet.testKS();
	// 				quantile = critLevel;
	// 				cond = QString("%1 < %2")
	// 					.arg(criteria, 3, 'f')
	// 					.arg(critLevel, 3, 'f');
	// 				accepted = criteria >= quantile;
	// 				implies = accepted ? "вибірки однорідні" : "вибірки не однорідні";
	// 				qf = [=](double a) { 
	// 					return criteria >= a;
	// 				};
	// 				break;
	// 			}
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
	// 		case ss::VectorHypothesis::Procedure::testWilcoxon:
	// 			{
	// 				criteria = vectorSet.testWilcoxon();
	// 				quantile = ss::normQuantile(1-critLevel/2);
	// 				cond = QString("%1 < u(%2) = %3")
	// 					.arg(criteria, 3, 'f')
	// 					.arg(1-critLevel/2, 3, 'f')
	// 					.arg(quantile, 3, 'f');
	// 				accepted = criteria <= quantile;
	// 				implies = accepted ? "вибірки однорідні" : "вибірки не однорідні";
	// 				qf = [=](double a) { 
	// 					return criteria <= ss::normQuantile(1-a/2);
	// 				};
	// 				break;
	// 			}
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
	// 		case ss::VectorHypothesis::Procedure::criteriaU:
	// 			{
	// 				criteria = vectorSet.criteriaU();
	// 				quantile = ss::normQuantile(1-critLevel/2);
	// 				cond = QString("%1 < u(%2) = %3")
	// 					.arg(criteria, 3, 'f')
	// 					.arg(1-critLevel/2, 3, 'f')
	// 					.arg(quantile, 3, 'f');
	// 				accepted = criteria <= quantile;
	// 				implies = accepted ? "вибірки однорідні" : "вибірки не однорідні";
	// 				qf = [=](double a) { 
	// 					return criteria <= ss::normQuantile(1-a/2);
	// 				};
	// 				break;
	// 			}
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
	// 		case ss::VectorHypothesis::Procedure::rankAveragesDifference:
	// 			{
	// 				criteria = vectorSet.rankAveragesDifference();
	// 				quantile = ss::normQuantile(1-critLevel/2);
	// 				cond = QString("|%1| < u(%2) = %3")
	// 					.arg(criteria, 3, 'f')
	// 					.arg(1-critLevel/2, 3, 'f')
	// 					.arg(quantile, 3, 'f');
	// 				accepted = std::abs(criteria) <= quantile;
	// 				implies = accepted ? "вибірки однорідні" : "вибірки не однорідні";
	// 				qf = [=](double a) { 
	// 					return std::abs(criteria) <= ss::normQuantile(1-a/2);
	// 				};
	// 				break;
	// 			}
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
	// 		case ss::VectorHypothesis::Procedure::hTest:
	// 			{
	// 				criteria = vectorSet.hTest();
	// 				quantile = ss::pearQuantile(1-critLevel, vectorSet.size()-1);
	// 				cond = QString("%1 < 𝜒(%2,%3) = %4")
	// 					.arg(criteria, 3, 'f')
	// 					.arg(1-critLevel, 3, 'f')
	// 					.arg(vectorSet.size()-1)
	// 					.arg(quantile, 3, 'f');
	// 				accepted = criteria <= quantile;
	// 				implies = accepted ? "вибірки однорідні" : "вибірки не однорідні";
	// 				qf = [=](double a) { 
	// 					return criteria <= ss::pearQuantile(1-a, vectorSet.size()-1);
	// 				};
	// 				break;
	// 			}
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
	// 		case ss::VectorHypothesis::Procedure::signTest:
	// 			{
	// 				criteria = vectorSet.signTest();
	// 				quantile = ss::normQuantile(1-critLevel);
	// 				cond = QString("%1 < u(%2) = %3")
	// 					.arg(criteria, 3, 'f')
	// 					.arg(1-critLevel, 3, 'f')
	// 					.arg(quantile, 3, 'f');
	// 				accepted = criteria < quantile;
	// 				implies = accepted ? "вибірки однорідні" : 
	// 					"вибірки не однорідні (F(x) < G(y))";
	// 				qf = [=](double a) { 
	// 					return criteria < ss::normQuantile(1-a);
	// 				};
	// 				break;
	// 			}
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
	// 		case ss::VectorHypothesis::Procedure::qTest:
	// 			{
	// 				criteria = vectorSet.qTest();
	// 				quantile = ss::pearQuantile(1-critLevel, vectorSet.size() - 1);
	// 				cond = QString("%1 ≤ 𝜒(%2, %3) = %4")
	// 					.arg(criteria, 3, 'f')
	// 					.arg(1-critLevel, 3, 'f')
	// 					.arg(vectorSet.size() - 1)
	// 					.arg(quantile, 3, 'f');
	// 				accepted = criteria <= quantile;
	// 				implies = accepted ? "всі способи мають однакову імовірність" : 
	// 					"всі способи мають різну імовірність" ;
	// 				qf = [=](double a) { 
	// 					return criteria <= ss::pearQuantile(1-a, vectorSet.size() - 1);
	// 				};
	// 				break;
	// 			}
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

		case ss::VectorHypothesis::Procedure::Count: {}
	// 		case ss::VectorHypothesis::Procedure::testAbbe:
	// 			{
	// 				criteria = vectorSet.testAbbe();
	// 				quantile = ss::normQuantile(critLevel);
	// 				cond = QString("%1 ≤ n(%2) = %3")
	// 					.arg(criteria, 3, 'f')
	// 					.arg(critLevel, 3, 'f')
	// 					.arg(quantile, 3, 'f');
	// 				accepted = criteria > quantile;
	// 				implies = accepted ? "спостереження незалежні" : 
	// 					"спостереження залежні" ;
	// 				qf = [=](double a) { 
	// 					return criteria > ss::normQuantile(a);
	// 				};
	// 				break;
	// 			}
	}
}
