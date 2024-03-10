#ifndef _DISTRIBUTION_REPRODUCTION_DIALOG_
#define _DISTRIBUTION_REPRODUCTION_DIALOG_

#include "statistics/dataVector.hpp"

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QTableWidget>
#include <QHeaderView>

#include "guiTypes.hpp"

class DistributionReproductionDialog : public QDialog {
	Q_OBJECT
public:
	DistributionReproductionDialog(
			VectorEntry*,
			QWidget* = nullptr,
			Qt::WindowFlags = Qt::WindowFlags()
			);

private:
	QComboBox* distributionComboBox = nullptr;

	QWidget* tablesWidget = nullptr;
	QVBoxLayout* tablesLayout = nullptr;
	QTableWidget* parameterTable = nullptr;
	QTableWidget* dispersionTable = nullptr;
	QTableWidget* functionTable = nullptr;

	VectorEntry* ve = nullptr;

	void refill();

public slots:
	void vectorDeletedHandler(VectorEntry*);

private slots:
	void distribute(int);

signals:
	void distributionSelected(VectorEntry*);
};

#endif // !_DISTRIBUTION_REPRODUCTION_DIALOG_
