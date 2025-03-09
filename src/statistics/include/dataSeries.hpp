#ifndef _DATASERIES_HPP_
#define _DATASERIES_HPP_

#include <vector>
#include <string>

class DataSeries {
public:
	DataSeries() = default;

	void readData(std::string);
	const std::vector<std::vector<double>>& series();
	const std::vector<double>& filewiseSeries();
	size_t size();
	unsigned short dimension();

	~DataSeries() = default;

private:
	std::string filename;

	std::vector<std::vector<double>> dataSeries;
	std::vector<double> filewiseDataSeries;
	unsigned short dimensions = 0;
};

#endif // !_MATSTAT_HPP_
