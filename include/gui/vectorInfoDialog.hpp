#ifndef _VECTOR_INFO_DIALOG_HPP_
#define _VECTOR_INFO_DIALOG_HPP_

#include "dataVector.hpp"
#include "varSeries.hpp"

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

#include "Section.h"

#include "guiTypes.hpp"

class VectorInfoDialog : public QDialog {
  Q_OBJECT
public:
  VectorInfoDialog(VectorEntry *, QWidget * = nullptr,
                   Qt::WindowFlags = Qt::WindowFlags());

private:
  VectorEntry *ve = nullptr;
  int precision = 4;

public slots:
  void vectorDeletedHandler(VectorEntry *);
};

#endif // !_VECTOR_INFO_DIALOG_HPP_
