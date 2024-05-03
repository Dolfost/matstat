#ifndef _DATA_VECTOR_SET_
#define _DATA_VECTOR_SET_

#include "dataVector.hpp"

class DataVectorSet : public std::vector<DataVector*> {
public:
	DataVectorSet();

	double tTestDependent();
	double tTestIndependent();
private:
};

#endif // !_DATA_VECTOR_SET_
