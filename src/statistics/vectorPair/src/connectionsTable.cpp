#include <vectorPair.hpp>
#include <vectorPair/hypothesis.hpp>

namespace ss {

void VectorPair::ConnectionsTable::adapt() {
	ss::VectorPair& v = *s_vector;
	std::size_t cols = v.y.len()+1, rows = v.x.len()+1;

	s_value.resize(rows);
	c_rowCount.resize(rows);
	c_columnCount.resize(cols);

	double x = v.x.min();
	for (long long i = 0; i < rows; i++) {
		s_value[i].resize(cols);
		double y = v.y.min();
		for (long long j = 0; j < cols; j++) {
			std::size_t val = v.vs[{x, y++}].first;
			s_value[i][j] = val;
			c_rowCount[i] += val;
			c_columnCount[j] += val;
		}
		x++;
	}
}

void VectorPair::ConnectionsTable::FehnerIndex::adapt() {
	const std::vector<std::vector<double>>& t = s_vector->value();
	if (t.size() != 2 or t[0].size() != 2)
		throw std::invalid_argument("Таблиця сполучень: розмірність не 2x2");

	s_value = (t[0][0] + t[1][1] - t[1][0] - t[0][1]) / 
		(t[0][0] + t[1][1] + t[1][0] + t[0][1]);
}

void VectorPair::ConnectionsTable::ConnectionsPhi::adapt() {
	if (!s_vector->is2by2())
		throw std::invalid_argument("Таблиця сполучень: розмірність не 2x2");
	const std::vector<std::vector<double>>& t = s_vector->value();
	const std::vector<double>& n = s_vector->row();
	const std::vector<double>& m = s_vector->col();

	s_value = (t[0][0]*t[1][1] - t[1][0]*t[0][1]) / 
		(std::sqrt(n[0]*n[1]*m[0]*m[1]));
}

void VectorPair::ConnectionsTable::CouplingQ::adapt() {
	if (!s_vector->is2by2())
		throw std::invalid_argument("Таблиця сполучень: розмірність не 2x2");

	const std::vector<std::vector<double>>& t = s_vector->value();

	s_value = (t[0][0]*t[1][1] - t[1][0]*t[0][1]) / (t[0][0]*t[1][1] + t[1][0]*t[0][1]);
}

void VectorPair::ConnectionsTable::CouplingY::adapt() {
	if (!s_vector->is2by2())
		throw std::invalid_argument("Таблиця сполучень: розмірність не 2x2");

	const std::vector<std::vector<double>>& t = s_vector->value();

	s_value = (std::sqrt(t[0][0]*t[1][1]) - std::sqrt(t[1][0]*t[0][1])) / (std::sqrt(t[0][0]*t[1][1]) + std::sqrt(t[1][0]*t[0][1]));
}

void VectorPair::ConnectionsTable::PearsonConnectionsCoefficient::adapt() {
	VectorPairHypothesis h;
	h.push_back(s_vector->s_vector);
	s_value = std::sqrt(h.couplingMeasure()/(s_vector->s_vector->size()+h.couplingMeasure()));
}

void VectorPair::ConnectionsTable::KendallCouplingMeasure::adapt() {
	if (s_vector->value().size() != s_vector->value()[0].size())
		throw std::invalid_argument("Таблиця cполучень не квадратна: n ≠ m");

	const std::vector<std::vector<double>>& t = s_vector->value();
	const std::vector<double>& n = s_vector->row();
	const std::vector<double>& m = s_vector->col();

	long long int p = 0, q = 0, t1 = 0, t2 = 0, N = s_vector->s_vector->size();

	for (int i = 0; i < n.size(); i++) {
		for (int j = 0; j < m.size(); j++) {
			double sum = 0;
			for (int k = i+1; k < n.size(); k++)
				for (int l = j+1; l < m.size(); l++) {
					sum += t[k][l];
				}
			p += t[i][j]*sum; 
			sum = 0;

			for (int k = i+1; k < n.size(); k++)
				for (int l = 0; l < j-1; l++) {
					sum += t[k][l];
				}
			q += t[i][j]*sum;
		}
		t1 += n[i]*(n[i]-1);
	}

	for (int j = 0; j < m.size(); j++) {
		t2 += m[j]*(m[j]-1);
	}

	t1 /= 2, t2 /= 2;

	s_value = (p - 1)/std::sqrt((0.5*N*(N-1)-t1)*(0.5*N*(N-1) - t2));
}

void VectorPair::ConnectionsTable::StuardStatistics::adapt() {
	if (s_vector->value().size() == s_vector->value()[0].size())
		throw std::invalid_argument("Таблиця cполучень квадратна: n = m");

	const std::vector<std::vector<double>>& t = s_vector->value();
	const std::vector<double>& n = s_vector->row();
	const std::vector<double>& m = s_vector->col();

	long long int p = 0, q = 0, N = s_vector->s_vector->size();

	for (int i = 0; i < n.size(); i++)
		for (int j = 0; j < m.size(); j++) {
			double sum = 0;
			for (int k = i+1; k < n.size(); k++)
				for (int l = j+1; l < m.size(); l++) {
					sum += t[k][l];
				}
			p += t[i][j]*sum; 
			sum = 0;

			for (int k = i+1; k < n.size(); k++)
				for (int l = 0; l < j-1; l++) {
					sum += t[k][l];
				}
			q += t[i][j]*sum;
		}

	s_value = (2*(p-q)*std::min(n.size(), m.size())) / 
		(std::pow(N, 2)*(std::min(n.size(), m.size()) - 1));
}


}
