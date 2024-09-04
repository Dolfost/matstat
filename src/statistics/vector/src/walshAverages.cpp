#include "vector.hpp"

namespace ss {

void WalshAverages::adapt() {
  for (auto const &i : s_vector.vector()) {
    for (auto const &j : s_vector.vector()) {
      s_value.push_back((i + j) * 0.5);
    }
  }
}

void WalshAverages::invalidate() {
	s_value.clear();
	StatisticSingle::invalidate();
}

void WalshAveragesMedian::adapt() {
  Vector walshAveragesVector(
		std::list<double>(
			s_vector.walshAverages().begin(), 
			s_vector.walshAverages().end()
		)
	);
  s_value = walshAveragesVector.med();
}

}
