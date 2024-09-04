#ifndef _DATASERIES_HPP_
#define _DATASERIES_HPP_

#include <QString>

#include <list>

class DataSeries {
public:
	DataSeries() = default;

	void readData(QString);
	const std::vector<std::list<double>>& series();
	const std::list<double>& filewiseSeries();
	size_t size();
	unsigned short dimension();

	~DataSeries() = default;

private:
	QString filename;

	std::vector<std::list<double>> dataSeries;
	std::list<double> filewiseDataSeries;
	unsigned short dimensions = 0;
};

#endif // !_MATSTAT_HPP_
