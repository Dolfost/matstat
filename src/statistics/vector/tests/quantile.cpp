#include <iomanip>
#include <vector/quantile.hpp>
#include <iostream>
#include <string>
#include <functional>

void plot(
	std::function<double(double)> f, 
	std::pair<double, double> range, 
	std::string title = "graph"
) {
	double step = std::abs(range.second - range.first)/20;
	std::cout << title << "\n" << std::fixed << "x    ";
	for (double x = range.first; x <= range.second; x += step) {
		std::cout << std::setw(10) << x;
	}

	std::cout << "\nf(x) ";
	for (double x = range.first; x <= range.second; x += step) {
		std::cout << std::setw(10) << f(x);
	}

	std::cout << std::endl;
}

int main() {
	plot(
		[](double a){ return ss::studQuantile(a, 15); },
		{0, 1},
		"Stud quantile v = 15"
	);

	plot(
		[](double a){ return ss::normQuantile(a); },
		{0, 1},
		"Norm quantile"
	);

	plot(
		[](double a){ return ss::fishQuantile(a, 10, 10); },
		{0, 1},
		"Fish quantile v1 = v2 = 10"
	);
	return 0;
}
