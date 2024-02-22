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

#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>

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

class VectorPickerTable : public QTableWidget {
public:
	VectorPickerTable(QWidget* = nullptr);

private:
	QPoint dragStartPosition;

protected:
	// void mousePressEvent(QMouseEvent*) override;
	// void mouseMoveEvent(QMouseEvent*) override;
};

#endif // !_VECTOR_PICKER_HPP_
