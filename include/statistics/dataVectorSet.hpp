#ifndef _DATA_VECTOR_SET_
#define _DATA_VECTOR_SET_

#include "dataVector.hpp"
#include <QStringList>

class DataVectorSet : public std::vector<DataVector*> {
public:
	// DataVectorSet();

	enum Procedure {
		tTestDependentP,
		tTestIndependentP,
		fTestP,
		fTestBartlettP,
		oneWayANOVAP,
		testKSP,
		testWilcoxonP,
		criteriaUP,
		rankAveragesDifferenceP,
		hTestP,
		signTestP,
		qTestP,
		testAbbeP,
		Count
	};

	static QStringList procedureName;

public: // tests
	double tTestDependent();
	double tTestIndependent();
	double fTest();
	double fTestBartlett();
	double oneWayANOVA();
	double testKS();
	double testWilcoxon();
	double criteriaU();
	double rankAveragesDifference();
	double hTest();
	double signTest();
	double qTest();
	double testAbbe();

public: // statistics
	size_t overallSize();
	double overallMean();
	double intergroupVariation(); // міжгрупова
	double intragroupVariation(); // в кожній вибірці
	std::list<double> overallVector();
	std::map<double, double> overallRank(); 

public: // misc
	void writeToFile(QString);

private:
};

#endif // !_DATA_VECTOR_SET_
