#include <testutils.hpp>
#include <iostream>
#include <sstream>

char col(double a) {
	if (a > 1 or a < 0)
		return 'F';
	return '0' + std::round(9*a);
}

void drawClassSeries(ss::VectorPair& v) {
	std::stringstream ss;
	for (long int y = v.y.cs.count()-1; y >= 0; y--) {
		ss.str("");
		for (std::size_t x = 0; x < v.x.cs.count(); x++) {
			ss << col(v.cs()[x][y].second) << "  ";
		}
		std::cout << ss.str() << '\n';
	}
}

void drawCumClassSeries(ss::VectorPair& v) {
	std::stringstream ss;
	for (long int y = v.y.cs.count()-1; y >= 0; y--) {
		ss.str("");
		for (std::size_t x = 0; x < v.x.cs.count(); x++) {
			ss << col(v.cs.cumSeries()[x][y].second) << "  ";
		}
		std::cout << ss.str() << '\n';
	}
}
