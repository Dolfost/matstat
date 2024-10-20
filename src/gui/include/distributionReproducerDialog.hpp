#ifndef _VECTOR_DISTRIBUTION_REPRODUCER_DIALOG_
#define _VECTOR_DISTRIBUTION_REPRODUCER_DIALOG_

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

#include <functionReproducerDialogBase.hpp>
#include <infoDialogBase.hpp>
#include <namedWidget.hpp>

#include <vector/quantile.hpp>

#include "guiTypes.hpp"

class VectorDistributionReproducerDialog : public FunctionReproducerDialogBase {
	Q_OBJECT
	public:
	VectorDistributionReproducerDialog(
		Vector*,
		QWidget* = nullptr,
		Qt::WindowFlags = Qt::WindowFlags()
	);

protected:
	virtual void fill() override;
	Vector* v_vector = nullptr;

private slots:
	virtual void distribute(int) override;
	virtual void makeTtest() override;

	signals:
	void modelSelected(Vector*);
};

#endif // !_VECTOR_DISTRIBUTION_REPRODUCER_DIALOG_
