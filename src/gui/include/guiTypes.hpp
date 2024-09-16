#ifndef _GUI_TYPES_HPP_
#define _GUI_TYPES_HPP_

#include <QString>
#include <QTableWidgetItem>

#include "vector.hpp"
#include "vectorPair.hpp"
#include "vectorChain.hpp"

class VectorEntry {
public:
	void setName(QString n) { v_name = n; };
	QString name() { return v_name; };
	void setTableItem(QTableWidgetItem* i) { v_tableItem = i; };
	QTableWidgetItem* tableItem() { return v_tableItem; };
	virtual ~VectorEntry() = 0;
protected:
	QString v_name;
	QTableWidgetItem* v_tableItem = nullptr;
};

inline VectorEntry::~VectorEntry() {};

class Vector: public VectorEntry {
public:
	Vector(ss::Vector* dv = nullptr, QString n = "") {
		v_vector = dv;
		v_name = n;

		v_isModeled = false;
		v_model = ss::Vector::Distribution::Model::Unknown;
		v_modelParameters = {};
	}

	void setModel(ss::Vector::Distribution::Model m, std::vector<double> p, ss::Vector::Distribution::Method meth) {
		v_isModeled = true;
		v_model = m;
		v_modelParameters = p;
		v_modelMethod = meth;
	}

	ss::Vector* vector() { return v_vector; }
	ss::Vector* data() { return v_vector; }
	void setVector(ss::Vector* v) { v_vector = v; }
	ss::Vector::Distribution::Model model() { return v_model; }
	ss::Vector::Distribution::Method method() { return v_modelMethod; }
	const std::vector<double>& parameters() { return v_modelParameters; }
	bool isModeled() { return v_isModeled; }

	~Vector() {
		delete v_vector;
	}
protected:
	ss::Vector* v_vector = nullptr;
	ss::Vector::Distribution::Model v_model;
	ss::Vector::Distribution::Method v_modelMethod;
	std::vector<double> v_modelParameters;
	bool v_isModeled;
};

class VectorPair: public VectorEntry {
public:
	ss::VectorPair* vectorPair() { return v_vectorPair; }
	ss::VectorPair* data() { return v_vectorPair; }
	void setVectorPair(ss::VectorPair* v) { v_vectorPair = v; }
protected:
	ss::VectorPair* v_vectorPair = nullptr;
};

class VectorChain: public VectorEntry {
public:
	ss::VectorChain* chain() { return v_vectorChain; }
	ss::VectorChain* data() { return v_vectorChain; }
	void setChain(ss::VectorChain* v) { v_vectorChain = v; }
protected:
	ss::VectorChain* v_vectorChain = nullptr;
};

#endif // !_GUI_TYPES_HPP_
