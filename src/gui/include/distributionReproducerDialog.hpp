#ifndef _DISTRIBUTION_REPRODUCER_DIALOG_
#define _DISTRIBUTION_REPRODUCER_DIALOG_

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
#include <QDoubleSpinBox>
#include <QStackedWidget>

#include "guiTypes.hpp"

class DistributionReproducerDialog : public QDialog {
	Q_OBJECT
public:
	DistributionReproducerDialog(
			Vector*,
			QWidget* = nullptr,
			Qt::WindowFlags = Qt::WindowFlags()
			);

private:
	QComboBox* distributionComboBox = nullptr;

	QWidget* tablesWidget = nullptr;
	QVBoxLayout* tablesLayout = nullptr;
	QTableWidget* parameterTable = nullptr;
	QTableWidget* deviationTable = nullptr;
	QTableWidget* functionDeviationTable = nullptr;
	QTableWidget* ttestTable = nullptr;
	QStackedWidget* ttestWidget = nullptr;
	QTextEdit* consentTextEdit = nullptr;

	QDoubleSpinBox* consentsProbabilitySpinBox = nullptr;

	Vector* ve = nullptr;

	void refill();

	int precision = 4;

public slots:
	void vectorDeletedHandler(Vector*);

private slots:
	void distribute(int);
	void makeConsents();
	void makeTtest();

signals:
	void distributionSelected(Vector*);
};

#endif // !_DISTRIBUTION_REPRODUCER_DIALOG_
