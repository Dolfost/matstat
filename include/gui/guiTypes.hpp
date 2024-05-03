#ifndef _GUI_TYPES_HPP_
#define _GUI_TYPES_HPP_

#include <QString>
#include "dataVector.hpp"

struct VectorEntry {
	DataVector* vector = nullptr;
	QString name;

	VectorEntry(DataVector* dv = nullptr, QString n = "") {
		vector = dv;
		name = n;
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
