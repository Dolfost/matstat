#ifndef _GUI_TYPES_HPP_
#define _GUI_TYPES_HPP_

#include <QString>
#include <vector>
#include "vector.hpp"

struct VectorEntry {
	ss::Vector* vector = nullptr;
	QString name;

	bool isModeled;
	ss::Vector::Distribution::Model modelDistribution;
	ss::Vector::Distribution::Method modelMethod;
	std::vector<double> modelParameters;

	VectorEntry(ss::Vector* dv = nullptr, QString n = "") {
		vector = dv;
		name = n;

		isModeled = false;
		modelDistribution = ss::Vector::Distribution::Model::Unknown;
		modelParameters = {};
	}

	void setModel(ss::Vector::Distribution::Model m, std::vector<double> p, ss::Vector::Distribution::Method meth) {
		isModeled = true;
		modelDistribution = m;
		modelParameters = p;
		modelMethod = meth;
	}

	~VectorEntry() {
		delete vector;
	}
};

enum Tab {
	TwoD,
	ThreeD,
	FourD,
	Count,
	Current
};

#endif // !_GUI_TYPES_HPP_
