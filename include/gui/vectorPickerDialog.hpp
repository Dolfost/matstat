#ifndef _VECTOR_PICKER_DIALOG_HPP_
#define _VECTOR_PICKER_DIALOG_HPP_

#include "statistics/dataSeries.hpp"
#include <QDialog>
#include <QTableWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStatusBar>
#include <QTextEdit>
#include <QTabWidget>
#include <QHeaderView>
#include <QPushButton>

#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QApplication>

class VectorPickerDialog : public QDialog {
	Q_OBJECT
public:
	VectorPickerDialog(
			QWidget* = nullptr,
			Qt::WindowFlags = Qt::WindowFlags()
			);

	void fileContents(QString);

private:
	QVBoxLayout* vectorsTabLayout = nullptr;
	QVBoxLayout* contentsTabLayout = nullptr;
	QTextEdit* contentsTextEdit = nullptr;
	QPushButton* addContentsPushButton = nullptr;
	QTableWidget* vectorsTableWidget = nullptr;
	void setContentsTab();
	void setVectorsTab();

	QStatusBar* statusBar = nullptr;
	DataSeries dataSeries;

	void fill();

protected:
	void closeEvent(QCloseEvent*) override;
private slots:
	void addVector(int, int);
	void addContents();

signals:
	void vectorSelected(const std::list<double>*);
};

#endif // !_VECTOR_PICKER_DIALOG_HPP_
