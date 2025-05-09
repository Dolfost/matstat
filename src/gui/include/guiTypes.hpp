#ifndef _GUI_TYPES_HPP_
#define _GUI_TYPES_HPP_

#include <QString>
#include <QTableWidgetItem>

#include "vector.hpp"
#include "vectorPair.hpp"
#include <vectorChain.hpp>

class VectorEntry {
public:
	VectorEntry(QString n = "") {
		v_name = n;
	}
	void setName(QString n) { v_name = n; };
	QString name() { return v_name; };
	void setTableItem(QTableWidgetItem* i) { v_tableItem = i; };
	QTableWidgetItem* tableItem() { return v_tableItem; };
	virtual ~VectorEntry() = 0;

	const std::vector<double>& distributionParameters() { return v_modelParameters; }
	void setDistribuitonParameters(const std::vector<double> p) {  v_modelParameters = p; }
protected:
	QString v_name;
	QTableWidgetItem* v_tableItem = nullptr;

	std::vector<double> v_modelParameters;
};

inline VectorEntry::~VectorEntry() {};

class Vector: public VectorEntry {
public:
	Vector(ss::Vector* dv = nullptr, QString n = ""): VectorEntry(n) {
		v_vector = dv;
		v_distribbuitonModel = ss::Vector::Distribution::Model::Unknown;
		v_modelParameters = {};
	};

	void setDistribuitonModel(ss::Vector::Distribution::Model m, std::vector<double> p, ss::Vector::Distribution::Method meth) {
		v_distribbuitonModel = m;
		v_modelParameters = p;
		v_generathionMethod = meth;
	}
	ss::Vector::Distribution::Model distribuitonModel() {
		return v_distribbuitonModel;
	}

	ss::Vector* vector() { return v_vector; }
	ss::Vector* data() { return v_vector; }
	void setVector(ss::Vector* v) { v_vector = v; }
	ss::Vector::Distribution::Model model() { return v_distribbuitonModel; }
	ss::Vector::Distribution::Method method() { return v_generathionMethod; }

	~Vector() {
		delete v_vector;
	}
protected:
	ss::Vector* v_vector = nullptr;
	ss::Vector::Distribution::Model v_distribbuitonModel = ss::Vector::Distribution::Model::Unknown;
	ss::Vector::Distribution::Method v_generathionMethod;
};

class VectorPair: public VectorEntry {
public:
	VectorPair(QString n = ""): VectorEntry(n) {};
	ss::VectorPair* vectorPair() { return v_vectorPair; }
	ss::VectorPair* data() { return v_vectorPair; }
	void setVectorPair(ss::VectorPair* v) { v_vectorPair = v; }
	void setRegressionModel(ss::VectorPair::Regression::Model m, const std::vector<double>& p) {
		v_regressionModel = m;
		v_regressionParameters = p;
	}
	ss::VectorPair::Regression::Model regressionModel() {
		return v_regressionModel;
	}
	void setNormalDistribution(bool n) {
		v_isNormalDistribution = n;
	}
	bool isNormalDistribution() {
		return v_isNormalDistribution;
	}
	const std::vector<double>& regressionParameters() { return v_regressionParameters; }

	std::optional<double> rotated_angle;
protected:
	ss::VectorPair* v_vectorPair = nullptr;
	ss::VectorPair::Regression::Model v_regressionModel = ss::VectorPair::Regression::Model::Unknown;
	std::vector<double> v_regressionParameters;
	bool v_isNormalDistribution = false;
};

class VectorChain: public VectorEntry {
public:
	ss::VectorChain* chain() { return v_vectorChain; }
	ss::VectorChain* data() { return v_vectorChain; }
	void setVectorChain(ss::VectorChain* v) { v_vectorChain = v; }

protected:
	ss::VectorChain* v_vectorChain = nullptr;
};

#endif // !_GUI_TYPES_HPP_
