#ifndef _DATA_VECTOR_SET_
#define _DATA_VECTOR_SET_

#include<vector>
#include<string>

#include "vector.hpp"

namespace ss {

class VectorChain : public std::vector<Vector*> {
public:
	void writeToFile(std::string);
};

}

#endif // !_DATA_VECTOR_SET_
