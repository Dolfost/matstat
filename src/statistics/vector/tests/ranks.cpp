#include <vector.hpp>
#include <iostream>

int main() {
	ss::Vector vec;
	vec.setVector(
		{13, 5, 10, 5, 8, 15, 9}
	);
	std::list<double> trueRanks = 
		{1.5, 1.5, 3, 4, 5, 6, 7};

	std::list<double> ranks = vec.ranks();

	for (auto const& x : ranks) {
		std::cout << x << " ";
	}
	std::cout << "\n";

	for (auto const& x : trueRanks) {
		std::cout << x << " ";
	}
	
	return !(trueRanks == ranks);
}
