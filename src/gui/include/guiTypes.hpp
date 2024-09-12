#ifndef _GUI_TYPES_HPP_
#define _GUI_TYPES_HPP_

#include <QString>
#include <vector>
#include "vector.hpp"

struct VectorEntry {
public:
	void setName(QString n) { v_name = n; };
	QString name() { return v_name; };
protected:
	QString v_name;
};

struct Vector: public VectorEntry {
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

enum Tab {
	TwoD,
	ThreeD,
	FourD,
	Count,
	Current
};

#endif // !_GUI_TYPES_HPP_
