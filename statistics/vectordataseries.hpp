#ifndef _VECTORDATASERIES_HPP_
#define _VECTORDATASERIES_HPP_

#include <cstddef>
#include <vector>

class VectorDataSeries {
public:
	VectorDataSeries(std::vector<double>&);
	~VectorDataSeries() = default;

	// std::vector<double> series();
	size_t size();

private:
	std::vector<double> vectorDataSeries;
};

#endif // !_VECTORDATASERIES_HPP_
