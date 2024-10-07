#include <iostream>
#include <list>
#include <string>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <regex>

#include "dataSeries.hpp"

std::list<std::string> split(const std::string &s, const std::regex &sep_regex = std::regex{"\\s+"}) {
  std::sregex_token_iterator iter(s.begin(), s.end(), sep_regex, -1);
  std::sregex_token_iterator end;
  return {iter, end};
}

void DataSeries::readData(std::string fn) {
	std::stringstream msg;
	filename = fn;

	std::ifstream file;
	// file.exceptions(std::ios::badbit | std::ios::failbit);
	file.exceptions(std::ios::badbit);

	file.open(filename, std::ios::in);

	std::string line;
	std::list<std::string> words;
	unsigned short dim;
	unsigned long lineno = 0;

	double tmp;
	int column;
	std::vector<std::list<double>> tmpDataSeries;

	dimensions = 0;
	while (!file.eof()) {
		// read new line
		lineno++;
		line.clear();
		std::getline(file, line);
		words = split(line);
		auto e = std::remove_if(words.begin(), words.end(), [](std::string s) {
			return !s.length();
		});
		words.erase(e, words.end());

		// skip empty lines
		if (words.size() == 0)
			continue;

		// check data dimension
		if (dimensions == 0) {
			dimensions = words.size();
			tmpDataSeries.resize(dimensions);
		} else if (words.size() != dimensions) {
			msg << "Прочитано за" << (words.size() > dimensions ? "багато" : "мало")
				<< "входжень у рядку " << lineno << "в файлі '" << filename
				<< "', очікувано " << dimensions << ", отримано " << words.size() << ".";
			throw std::logic_error(msg.str());
		}

		// parse integers
		column = 0;
		for (const auto& word : words) {
			try {
				tmp = std::stod(word);
			} catch (std::invalid_argument& ex) {
				msg << "Не вдалося прочитати число у рядку " 
					<< lineno << " в файлі '" << filename << "'.";
				throw std::logic_error(msg.str());
			}

			tmpDataSeries[column].push_back(tmp);
			column++;
		}
    }

	dataSeries = tmpDataSeries;

	filewiseDataSeries.clear();
	std::vector<std::list<double>::iterator> iterators;
	for (auto& list : tmpDataSeries) {
		iterators.push_back(list.begin());
	}

	int row, col;
	for (row = 0; row < tmpDataSeries[0].size(); row++) {
		for (col = 0; col < dimensions; col++) {
			filewiseDataSeries.push_back(*(iterators[col]++));
		}
	}
}

const std::vector<std::list<double>>& DataSeries::series() {
	return dataSeries;
}

const std::list<double>& DataSeries::filewiseSeries() {
	return filewiseDataSeries;
}

size_t DataSeries::size() {
	return dataSeries.size();
}

unsigned short DataSeries::dimension() {
	return dimensions;
}
