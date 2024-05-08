#ifndef _GUI_TYPES_HPP_
#define _GUI_TYPES_HPP_

#include <QString>
#include <vector>
#include "dataVector.hpp"

struct VectorEntry {
	DataVector* vector = nullptr;
	QString name;

	bool isModeled;
	DistributionReproducer::Distribution modelDistribution;
	DistributionReproducer::Method modelMethod;
	std::vector<double> modelParameters;

	VectorEntry(DataVector* dv = nullptr, QString n = "") {
		vector = dv;
		name = n;

		isModeled = false;
		modelDistribution = DistributionReproducer::UnknownD;
		modelParameters = {};
	}

	void setModel(DistributionReproducer::Distribution m, std::vector<double> p, DistributionReproducer::Method meth) {
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
