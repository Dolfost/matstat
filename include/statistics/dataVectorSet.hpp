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
		Count
	};

	static QStringList procedureName;

	double tTestDependent();
	double tTestIndependent();
	double fTest();
	double fTestBartlett();
	double oneWayANOVA();
	double testKS();
	double testWilcoxon();

public: // statistics
	size_t overallSize();
	double overallMean();
	double intergroupVariation(); // міжгрупова
	double intragroupVariation(); // в кожній вибірці
	std::map<double, double> overallRank(); 

private:
};

#endif // !_DATA_VECTOR_SET_
