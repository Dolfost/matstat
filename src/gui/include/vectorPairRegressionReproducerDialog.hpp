#ifndef _VECTOR_PAIR_REGRESSION_REPRODUCER_DIALOG_
#define _VECTOR_PAIR_REGRESSION_REPRODUCER_DIALOG_

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

class VectorPairRegressionReproducerDialog : public FunctionReproducerDialogBase {
	Q_OBJECT
	public:
	VectorPairRegressionReproducerDialog(
		VectorPair*,
		QWidget* = nullptr,
		Qt::WindowFlags = Qt::WindowFlags()
	);

protected:
	virtual void fill() override;
	VectorPair* v_vectorPair = nullptr;

protected slots:
	virtual void distribute(int) override;
	virtual void makeTtest() override;
};

#endif // !_VECTOR_PAIR_REGRESSION_REPRODUCER_DIALOG_
