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

#include "vectorEntryDialogBase.hpp"

#include "guiTypes.hpp"

class DistributionReproducerDialog : public VectorEntryDialogBase {
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

	virtual void fill() override;

	Vector* v_vector = nullptr;

	int precision = 4;

private slots:
	void distribute(int);
	void makeConsents();
	void makeTtest();

	signals:
	void distributionSelected(Vector*);
};

#endif // !_DISTRIBUTION_REPRODUCER_DIALOG_
