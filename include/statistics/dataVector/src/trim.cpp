#include "../dataVector.hpp"

size_t DataVector::trim(double from, double to) {
  std::list<double> newVector;

  auto it = dataVector.begin();
  while (it != dataVector.end()) {
    if (*it >= from)
      break;
    it++;
  }

  while (it != dataVector.end()) {
    if (*it <= to)
      newVector.push_back(*(it++));
    else
      break;
  }

  auto x = timeSeries.begin();
  while (x != timeSeries.end()) {
	  if (*x <= to or *x >= from)
		  x = timeSeries.erase(x);
  }

  size_t res = dataVector.size() - newVector.size();
  dataVector = newVector;

  clearStatistics();

  return res;
}
