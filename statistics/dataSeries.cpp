#include <QString>
#include <QDebug>
#include <QFile>
#include <QtCore/qnamespace.h>
#include <QtCore/qstring.h>
#include <QRegularExpression>

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
			msg = QString("Got too %1 entries on line %2 in '%3', expected %4, got %5.")
					.arg(words.length() > dimensions ? "many" : "few")
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
				msg = QString("Could not parse number on line %1 from '%2'.")
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

	msg = QString("Read %1 %2-dimensional entries from '%3'.")
		.arg(QString::number(dataSeries[0].size()))
		.arg(QString::number(dimensions))
		.arg(filename);

	return dataSeries.size() == 0 ? Status::Warning : Status::Ok;
}

std::vector<std::list<double>>& DataSeries::series() {
	return dataSeries;
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
