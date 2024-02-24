#include <QString>
#include <QDebug>
#include <QFile>
#include <QtCore/qnamespace.h>
#include <QtCore/qstring.h>
#include <QRegularExpression>
#include <vector>

#include "dataSeries.hpp"

Status DataSeries::readData(QString fn) {
	filename = fn;

	QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
     	msg = "'" + filename + "'" + ": " + file.errorString() + ".";
		status = Status::Error;
		return Status::Error;
    }

	QString line;
    QStringList words;
	unsigned short dim;
	unsigned long lineno = 0;

	double tmp;
	bool ok;
	int column;
	std::vector<std::list<double>> tmpDataSeries;
	QRegularExpression reqExp("[\t, ]+");

	dimensions = 0;
    while (!file.atEnd()) {
		// read new line
		lineno++;
		line = file.readLine();
		words = line.split(reqExp, Qt::SkipEmptyParts);

		// skip empty lines
		if (words.length() == 0)
			continue;

		// check data dimension
		if (dimensions == 0) {
			dimensions = words.length();
			tmpDataSeries.resize(dimensions);
		} else if (words.length() != dimensions) {
			msg = QString("Прочитано за%1 входжень у рядку %2 в файлі '%3', очікувано %4, отримано %5.")
					.arg(words.length() > dimensions ? "багато" : "мало")
					.arg(QString::number(lineno))
					.arg(filename)
					.arg(QString::number(dimensions))
					.arg(QString::number(words.length()));
			status = Status::Error;
			return Status::Error;
		}

		// parse integers
		column = 0;
		for (const auto& word : words) {
			tmp = word.toDouble(&ok);
			if (ok == false) {
				msg = QString("Не вдалося прочитати число у рядку %1 в файлі '%2'.")
					.arg(QString::number(lineno))
					.arg(filename);
				status = Status::Error;
				return Status::Error;
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

	msg = QString("Прочитано %1 %2-вимірних даних з файлу '%3'.")
		.arg(QString::number(dataSeries[0].size()))
		.arg(QString::number(dimensions))
		.arg(filename);

	return dataSeries.size() == 0 ? Status::Warning : Status::Ok;
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

QString DataSeries::message() {
	return msg;
}
