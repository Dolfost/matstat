#include<iostream>
#include<testutils.hpp>
#include<dataSeries.hpp>

int main() {
	DataSeries dat;
	dat.readData("../src/statistics/vectorPair/tests/norm3n.txt");
	ss::VectorPair vec(
		dat.series()[0],
		dat.series()[1]
	);

	std::cout << "Class series:\n";
  drawClassSeries(vec);
	std::cout << "\nCummulative class series:\n";
	drawCumClassSeries(vec);

  return 0;
}
