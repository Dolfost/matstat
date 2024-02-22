#ifndef _DATASERIES_HPP_
#define _DATASERIES_HPP_

#include <QString>

#include <list>

#include "../types.hpp"

class DataSeries {
public:
	DataSeries() = default;

	Status readData(QString);
	const std::vector<std::list<double>>& series();
	size_t size();
	unsigned short dimension();

	QString message();

	~DataSeries() = default;

private:
	QString filename;

	std::vector<std::list<double>> dataSeries;
	unsigned short dimensions = 0;


	QString msg;
	Status status = Status::None;
};

#endif // !_MATSTAT_HPP_
