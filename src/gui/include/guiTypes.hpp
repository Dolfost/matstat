#ifndef _GUI_TYPES_HPP_
#define _GUI_TYPES_HPP_

#include <QString>
#include <vector>
#include "vector.hpp"

struct VectorEntry {
	ss::Vector* vector = nullptr;
	QString name;

	bool isModeled;
	ss::DistributionReproducer::Distribution modelDistribution;
	ss::	DistributionReproducer::Method modelMethod;
	std::vector<double> modelParameters;

	VectorEntry(ss::Vector* dv = nullptr, QString n = "") {
		vector = dv;
		name = n;

		isModeled = false;
		modelDistribution = ss::DistributionReproducer::UnknownD;
		modelParameters = {};
	}

	void setModel(ss::DistributionReproducer::Distribution m, std::vector<double> p, ss::DistributionReproducer::Method meth) {
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
