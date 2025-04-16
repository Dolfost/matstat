#ifndef _VECTOR_CHAIN_MATH_HPP_
#define _VECTOR_CHAIN_MATH_HPP_

#include <cmath>
#include <cstddef>

namespace ss {

template<typename T, typename R = typename T::value_type::value_type>
R determinant(T matrix, std::size_t n) {
	R det = 0;
	T submatrix(n);
	for (auto& x: submatrix) {
		x.resize(n);
	}
	if (n == 2)
		return ((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]));
	else {
		for (std::size_t x = 0; x < n; x++) {
			std::size_t subi = 0;
			for (int i = 1; i < n; i++) {
				std::size_t subj = 0;
				for (std::size_t j = 0; j < n; j++) {
					if (j == x)
						continue;
					submatrix[subi][subj] = matrix[i][j];
					subj++;
				}
				subi++;
			}
			det = det + (std::pow(-1, x) * matrix[0][x] * determinant( submatrix, n - 1 ));
		}
	}
	return det;
}

template<typename T, typename R = typename T::value_type::value_type>
R determinant(T matrix) {
	return determinant(matrix, matrix.size());
}

template<typename T> 
T minor(T matrix, std::size_t k) {
	std::size_t n = matrix.size();
	T m(n - 1);

	for (std::size_t i = 0; i < k; i += 1) {
		m[i].resize(n-1);
		for (std::size_t j = 0; j < k; j++)
			m[i][j] = matrix[i][j];
		for (std::size_t j = k+1; j < n; j++)
			m[i][j-1] = matrix[i][j];
	}

	for (std::size_t i = k+1; i < n; i += 1) {
		m[i-1].resize(n-1);
		for (std::size_t j = 0; j < k; j++)
			m[i-1][j] = matrix[i][j];
		for (std::size_t j = k+1; j < n; j++)
			m[i-1][j-1] = matrix[i][j];
	}

	return m;
}

}

#endif // !_VECTOR_CHAIN_MATH_HPP_
