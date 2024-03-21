#ifndef _SET_GENERATOR_DIALOG_
#define _SET_GENERATOR_DIALOG_

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QSpinBox>
#include <QStatusBar>

#include "guiTypes.hpp"

class ParametersWidget : public QWidget {
	Q_OBJECT
public:
		ParametersWidget(QStringList, std::vector<double>, bool = true);
		std::vector<double> parameters();

private:
		QGridLayout* layout;
		size_t size = 0;
		int precision = 4;
};

class SetGeneratorDialog : public QDialog {
	Q_OBJECT
public:
	SetGeneratorDialog(
			VectorEntry* = nullptr,
			QWidget* = nullptr,
			Qt::WindowFlags = Qt::WindowFlags()
			);

private:
	QComboBox* distributionComboBox = nullptr;
	QGroupBox* boundsBox = nullptr;
	QSpinBox* countSpinBox = nullptr;
	QDoubleSpinBox* minSpinBox = nullptr;
	QDoubleSpinBox* maxSpinBox = nullptr;
	ParametersWidget* parametersWidget = nullptr;
	QVBoxLayout* parametersLayout = nullptr;
	QComboBox* methodComboBox = nullptr;

	QPushButton* generateButton = nullptr;

	QStatusBar* statusBar = nullptr;

	VectorEntry* ve = nullptr;

	std::vector<double> params = {};

	bool enabled = true;

	int precision = 4;

public slots:
	void vectorDeletedHandler(VectorEntry*);

private slots:
	void generate();
	void distributionSelected(int);
	void methodSelected(int);
	void minBoundChanged(double);
	void maxBoundChanged(double);

signals:
	void setGenerated(VectorEntry*);
};

#endif // !_SET_GENERATOR_DIALOG_
