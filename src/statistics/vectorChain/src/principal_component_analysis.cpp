#include <iostream>
#include <vectorChain.hpp>

#include <vectorChain/jacobi_rotation.hpp>

namespace ss { 

template<typename T>
void show(const T& m) {
	for (const auto& x: m) {
		for (const auto& y: x) {
			std::cout << y << '\t';
		}
		std::cout << std::endl;
	}
};

void VectorChain::PrincipalComponentAnalysis::perform() {
	VectorChain& X = *s_vector;
	VectorChain X_1(X.begin(), X.end());
	const std::size_t n = X.size();
	const std::size_t N = X.at(0).size();
	m_eigenvectors = std::vector<std::vector<double>>(n, std::vector<double>(n));
	m_eigenvalues.resize(n);

	jacobi_pd::Jacobi<double, std::vector<double>&, std::vector<std::vector<double>>&, const std::vector<std::vector<double>>&> jac(n);
	jac.Diagonalize(s_vector->dc(), m_eigenvalues, m_eigenvectors);

	// show(m_eigenvectors);
	// for (const auto& y: m_eigenvalues) {
	// 	std::cout << y << '\t';
	// }
	// std::cout << std::endl;

	for (std::size_t k = 0; k < n; k++) {
		for (std::size_t l = 0; l < N; l++) {
			double sum = 0;
			for (std::size_t v = 0; v < n; v++)
				sum += m_eigenvectors[k][v]*X_1[v][l];
			X[k][l] = sum;
		}
	}

	m_done = false;
	s_vector->invalidate();

	m_done = true;
}

}
