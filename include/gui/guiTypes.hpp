#ifndef _GUI_TYPES_HPP_
#define _GUI_TYPES_HPP_

#include <QString>
#include "statistics/dataVector.hpp"

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

#endif // !_GUI_TYPES_HPP_
