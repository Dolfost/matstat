#ifndef _SET_GENERATOR_DIALOG_
#define _SET_GENERATOR_DIALOG_

#include <QComboBox>
#include <QDialog>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QStatusBar>
#include <QVBoxLayout>

#include <calgo/qt/matWidget.hpp>

#include "guiTypes.hpp"

#include <dialogBase.hpp>

class ParametersWidget : public QWidget {
  Q_OBJECT
public:
  ParametersWidget(QStringList, std::vector<double>, bool = true);
  std::vector<double> parameters();

private:
  QGridLayout *layout;
  size_t size = 0;
  int precision = 4;
};

class SetGeneratorDialog : public DialogBase {
  Q_OBJECT
public:
  SetGeneratorDialog(QWidget * = nullptr,
                     bool show = true, Qt::WindowFlags = Qt::WindowFlags());

private:
	void setVectorTab();
	void setVectorPairTab();
	void setVectorChainTab();

  QComboBox *vectorDistributionComboBox = nullptr;
  QGroupBox *vectorBoundsBox = nullptr;
  QDoubleSpinBox *vectorMinSpinBox = nullptr;
  QDoubleSpinBox *vectorMaxSpinBox = nullptr;
  ParametersWidget *vectorParametersWidget = nullptr;
  QVBoxLayout *vectorParametersLayout = nullptr;
  QComboBox *vectorMethodComboBox = nullptr;

  QPushButton *generateButton = nullptr;
  QSpinBox *countSpinBox = nullptr;

  ParametersWidget *vectorPairParametersWidget = nullptr;
  QVBoxLayout *vectorPairParametersLayout = nullptr;
	QComboBox* vectorPairModelComboBox = nullptr;

  ParametersWidget *vectorChainMeans = nullptr;
	ca::qt::MatWidget* vectorChainDCwidget = nullptr;
  QVBoxLayout *vectorChainParametersLayout = nullptr;
  QSpinBox *vectorChainDimensionSpinBox = nullptr;

	QTabWidget* tabs = nullptr;
	QWidget* vectorTab = nullptr;
	QWidget* vectorPairTab = nullptr;
	QWidget* vectorChainTab = nullptr;

  QStatusBar *statusBar = nullptr;

  std::vector<double> params = {};

  bool enabled = true;

  int precision = 4;

  void generateVector();
  void generateVectorPair();
  void generateVectorChain();

public slots:
	virtual void fill() {};

private slots:
	void generateHandler();
  void vectorDistributionSelected(int);
  void vectorMethodSelected(int);
  void vectorMinBoundChanged(double);
  void vectorMaxBoundChanged(double);

	void vectorPairModelSelected(int);

signals:
  void vectorGenerated(Vector*);
  void vectorPairGenerated(VectorPair*);
  void vectorChainGenerated(VectorChain*);
  void message(QString);
};

#endif // !_SET_GENERATOR_DIALOG_
