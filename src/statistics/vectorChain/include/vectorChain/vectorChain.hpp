#ifndef _VECTOR_CHAIN_HPP_
#define _VECTOR_CHAIN_HPP_	

#include <vector.hpp>
#include <vector/quantile.hpp>
#include <vector/utils.hpp>

#include <iterator>

#include <exprtk.hpp>

namespace ss {

#define WRAP_SINGLE(name) SS_WRAP_EXPRTK_SINGLE(name, VectorSet)
#define WRAP_PAIR(name) SS_WRAP_EXPRTK_PAIR(name, VectorSet)
#define WRAP_MAP(name) SS_WRAP_EXPRTK_MAP(name, VectorSet)
#define WRAP_PAIR_MAP(name) SS_WRAP_EXPRTK_PAIR_MAP(name, VectorSet)

class VectorChain: public std::vector<Vector> {
public:
	class PairCorrelation: public utils::StatisticMap<std::pair<std::size_t, std::size_t>, double, std::pair<std::size_t, std::size_t>, VectorChain> {
	public:
		using StatisticMap::StatisticMap;
		PairCorrelation() = delete;
		virtual void adapt(std::pair<std::size_t, std::size_t>) override;
	} pcor = PairCorrelation(this);

	class DC: public utils::StatisticSingle<std::vector<std::vector<double>>, VectorChain> {
	public:
		using StatisticSingle::StatisticSingle;
		virtual void adapt() override;
	} dc = DC(this);

	class R: public utils::StatisticSingle<std::vector<std::vector<double>>, VectorChain> {
	public:
		using StatisticSingle::StatisticSingle;
		virtual void adapt() override;
	} r = R(this);

	class PluralCorelationRatio: public utils::StatisticMap<std::size_t, double, std::size_t, VectorChain> {
	public:
		using StatisticMap::StatisticMap;
		virtual void adapt(std::size_t) override;
	} plural_corelation = PluralCorelationRatio(this);

	class PartialCorelationRatio: public utils::StatisticMap<std::tuple<std::size_t, std::size_t, std::vector<std::size_t>>, double, std::tuple<std::size_t, std::size_t, std::vector<std::size_t>>, VectorChain> {
	public:
		using StatisticMap::StatisticMap;
		virtual void adapt(std::tuple<std::size_t, std::size_t, std::vector<std::size_t>>) override;
	} partial_corelation = PartialCorelationRatio(this);
	
	VectorChain() {};
	template<class Iter, typename std::enable_if<std::is_same<typename
	std::iterator_traits<Iter>::iterator_category,
	std::random_access_iterator_tag>::value and std::is_same<typename
	std::iterator_traits<Iter>::value_type, ss::Vector*>::value, int>::type = 0>
	VectorChain(const Iter& begin, const Iter& end) {
		const std::size_t l = (*begin)->size();
		for (auto i = std::next(begin); i != end; i++) {
			if ((*i)->size() != l)
				throw std::logic_error("Вектори різного розміру");
		}
		for (auto i = begin; i != end; i++) {
			push_back(**i);
		}
	}

	template<class Iter, typename std::enable_if<std::is_same<typename
	std::iterator_traits<Iter>::iterator_category,
	std::random_access_iterator_tag>::value and std::is_same<typename
	std::iterator_traits<Iter>::value_type, ss::Vector>::value, int>::type = 0>
	VectorChain(const Iter& begin, const Iter& end) {
		const std::size_t l = (*begin).size();
		for (auto i = std::next(begin); i != end; i++) {
			if ((*i).size() != l)
				throw std::logic_error("Вектори різного розміру");
		}
		for (auto i = begin; i != end; i++) {
			push_back(*i);
		}
	}

	class PrincipalComponentAnalysis: public utils::Statistic<int, VectorChain> {
	public:
		using Statistic::Statistic;

	public:
		virtual void invalidate() override {
			if (m_done) {
				m_eigenvalues.clear();
				m_eigenvectors.clear();
				m_done = false;
			}
		}

		bool is_done() const { return m_done; }
		const std::vector<double>& eigenvalues() { return m_eigenvalues; }
		const std::vector<std::vector<double>>& eigenvectors() { return m_eigenvectors; }

	public:
		void perform();

	protected:
		std::vector<double> m_eigenvalues;
		std::vector<std::vector<double>> m_eigenvectors;
		bool m_done = false;
	} pca = PrincipalComponentAnalysis(this);

	class Regression: public utils::Statistic<int, VectorChain> {
	public:
		using Statistic::Statistic;

	public:
		void setModel(std::vector<double>);
		double regression(std::vector<double> x);
		std::vector<double> confidence(std::vector<double> x) {
			// double f = this->regression(x), q = ss::studQuantile(1-this->d_confidence/2, this->s_vector->size()-2)*this->Symx(x);
			// return {f - q, f + q};
			return {0};
		}

		double confidenceLevel() { return d_confidence; };
		void setConfidenceLevel(double c) { d_confidence = c; };

		size_t parametersCount = 0;
		std::vector<double> parameters{0};
		std::vector<double> parametersDeviation{0};

		double remDispersion;
		double determination;
		double phi1, phi2;

		virtual void invalidate() override {
		}
	protected:
		double d_confidence = 0.95;
	} reg = Regression(this);

	void writeToFile(std::string filename);

public:
	// std::string transform(std::string, std::string);

public:
	void invalidate();

	// static void setExprtkSymbolTable(::exprtk::symbol_table<double>&, VectorSet*, std::string = "");
	// static const std::string exprtkFunctions;
protected:
	void checkSize();

	// ::exprtk::symbol_table<double> v_exprtkSymbolTable;
};

#undef WRAP_SINGLE
#undef WRAP_PAIR
#undef WRAP_MAP
#undef WRAP_PAIR_MAP

}

#endif // !_VECTOR_CHAIN_HPP_
