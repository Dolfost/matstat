#ifndef _VECTOR_TRIMMER_DIALOG_HPP_
#define _VECTOR_TRIMMER_DIALOG_HPP_

#include "dataVector.hpp"

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QStatusBar>
#include <QDoubleSpinBox>

#include "rangeSlider.hpp"

#include "guiTypes.hpp"

class VectorTrimmerDialog : public QDialog {
	Q_OBJECT
public:
	VectorTrimmerDialog(
			VectorEntry*,
			QWidget* = nullptr,
			Qt::WindowFlags = Qt::WindowFlags()
			);

private:
	VectorEntry* ve = nullptr;
	static int trimIdx;

	QDoubleRangeSlider* slider = nullptr;
	QDoubleSpinBox* maxSpinBox = nullptr;
	QDoubleSpinBox* minSpinBox = nullptr;
	QPushButton* trimButton = nullptr;

	QStatusBar* statusBar = nullptr;

	double glow, ghigh, interval;

public slots:
	void trim();
	void vectorDeletedHandler(VectorEntry*);
	void boundsChanged(int, int, double, double);
	void lowChanged(double);
	void highChanged(double);

signals:
	void vectorTrimmed(VectorEntry*);
};

#endif // !_VECTOR_TRIMMER_DIALOG_HPP_
