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
		Count
	};

	static QStringList procedureName;

	double tTestDependent();
	double tTestIndependent();
private:
};

#endif // !_DATA_VECTOR_SET_
