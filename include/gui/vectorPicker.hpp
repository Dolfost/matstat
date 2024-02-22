#ifndef _VECTOR_PICKER_HPP_
#define _VECTOR_PICKER_HPP_

#include "statistics/dataSeries.hpp"
#include <QDialog>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QTextEdit>
#include <QTabWidget>
#include <QHeaderView>

class VectorPicker : public QDialog {
public:
	VectorPicker(QWidget* = nullptr, Qt::WindowFlags = Qt::WindowFlags());

	void fileContents(QString);

private:
	QHBoxLayout* vectorsTabLayout = nullptr;
	QHBoxLayout* contentsTabLayout = nullptr;
	QTextEdit* contentsTextEdit = nullptr;
	QTableWidget* vectorsTableWidget = nullptr;
	void setContentsTab();
	void setVectorsTab();

	QTableWidget* vectorTable = nullptr;
	QStatusBar* statusBar = nullptr;
	DataSeries dataSeries;

	void fill();
};

#endif // !_VECTOR_PICKER_HPP_
