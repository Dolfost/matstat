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

#include "guiTypes.hpp"

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

class SetGeneratorDialog : public QDialog {
  Q_OBJECT
public:
  SetGeneratorDialog(Vector * = nullptr, QWidget * = nullptr,
                     bool show = true, Qt::WindowFlags = Qt::WindowFlags());

private:
  QComboBox *distributionComboBox = nullptr;
  QGroupBox *boundsBox = nullptr;
  QSpinBox *countSpinBox = nullptr;
  QDoubleSpinBox *minSpinBox = nullptr;
  QDoubleSpinBox *maxSpinBox = nullptr;
  ParametersWidget *parametersWidget = nullptr;
  QVBoxLayout *parametersLayout = nullptr;
  QComboBox *methodComboBox = nullptr;

  QPushButton *generateButton = nullptr;

  QStatusBar *statusBar = nullptr;

  Vector *ve = nullptr;

  std::vector<double> params = {};

  bool enabled = true;

  int precision = 4;

public slots:
  void vectorDeletedHandler(Vector *);

private slots:
  void generate();
  void distributionSelected(int);
  void methodSelected(int);
  void minBoundChanged(double);
  void maxBoundChanged(double);

signals:
  void setGenerated(Vector *);
  void message(QString);
};

#endif // !_SET_GENERATOR_DIALOG_
