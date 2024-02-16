#ifndef _VECTOR_READER_WINDOW_HPP_
#define _VECTOR_READER_WINDOW_HPP_

#include <QDialog>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qtextedit.h>
#include <QStatusBar>
#include <vector>

#include "../statistics/vectordataseries.hpp"
#include "../statistics/dataseries.hpp"

class VectorReaderWindow : public QDialog {
public:
	VectorReaderWindow(QWidget *parent = nullptr);
	void readData(QString file);

	void setVectors();
	std::vector<VectorDataSeries> vectors();
private:
	std::vector<VectorDataSeries> vectorDataSeries;

	DataSeries* dataSeries = nullptr;
	QTextEdit* contentsTextEdit = nullptr;
	QTableWidget* vectorsTableWidget = nullptr;
	QStatusBar* statusBar = nullptr;
	QPushButton* importLinewiseButton = nullptr;
	QPushButton* importColumnwiseButton = nullptr;
};

#endif // !_VECTOR_READER_WINDOW_HPP_
