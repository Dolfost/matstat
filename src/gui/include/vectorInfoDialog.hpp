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
	QTableWidget* v_var = nullptr;
	InfoTableWidget* v_table = nullptr;
	IntervalTableWidget* v_interval = nullptr;
};

#endif // !_VECTOR_INFO_DIALOG_HPP_
