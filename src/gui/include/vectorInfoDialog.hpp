#ifndef _VECTOR_INFO_DIALOG_HPP_
#define _VECTOR_INFO_DIALOG_HPP_

#include "vector.hpp"

#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QPushButton>
#include <QStringList>
#include <QTabWidget>
#include <QTableWidgetItem>
#include <QTextEdit>
#include <QVBoxLayout>

#include <infoDialogBase.hpp>

class VectorInfoDialog: public InfoDialogBase {
public:
  VectorInfoDialog(
		Vector *, QWidget * = nullptr,
    Qt::WindowFlags = Qt::WindowFlags()
	);

public slots:
	virtual void fill() override;

protected:
	Vector* v_vector;

protected:
	QTableWidget* v_interval = nullptr;
	QTableWidget* v_var = nullptr;
	QList<double> v_probs = {
		0.99, 0.98, 0.97, 0.95, 0.9, 0.85, 0.8
	};
};

#endif // !_VECTOR_INFO_DIALOG_HPP_
