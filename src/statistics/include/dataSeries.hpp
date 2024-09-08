#ifndef _DATASERIES_HPP_
#define _DATASERIES_HPP_

#include <list>
#include <string>

class DataSeries {
public:
	DataSeries() = default;

	void readData(std::string);
	const std::vector<std::list<double>>& series();
	const std::list<double>& filewiseSeries();
	size_t size();
	unsigned short dimension();

	~DataSeries() = default;

private:
	std::string filename;

	std::vector<std::list<double>> dataSeries;
	std::list<double> filewiseDataSeries;
	unsigned short dimensions = 0;
};

#endif // !_MATSTAT_HPP_
