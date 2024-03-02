#ifndef _VECTOR_INFO_DIALOG_HPP_
#define _VECTOR_INFO_DIALOG_HPP_

#include "statistics/dataVector.hpp"
#include "statistics/varSeries.hpp"

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QTabWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QList>
#include <QStringList>

#include "Section.h"

#include "guiTypes.hpp"

class VectorInfoDialog : public QDialog {
	Q_OBJECT
public:
	VectorInfoDialog(
			VectorEntry*,
			QWidget* = nullptr,
			Qt::WindowFlags = Qt::WindowFlags()
			);

private:

	VectorEntry* ve = nullptr;
	int precision = 6;

public slots:
	void vectorDeletedHandler(int, VectorEntry*);
};

#endif // !_VECTOR_INFO_DIALOG_HPP_
