#include <iomanip>
#include<iostream>
#include<vectorPairTestutils.hpp>
#include<iostream>

int main() {
	ss::VectorPair vp(
		{10, 7, 11, 3, 7, 12, 5},
		{13, 5, 10, 5, 8, 15, 9}
	);

	std::cout << "X-ranks:\n";
	for (auto const& x : vp.x.ranks()) {
		std::cout << std::setw(5) << x << " ";
	}
	std::cout << "\nY-ranks:\n";
	for (auto const& y : vp.yRanks()) {
		std::cout << std::setw(5) << y << " ";
	}
	
	return vp.yRanks() != std::list<double>{1.5, 4, 1.5, 3, 6, 5, 7};
}
