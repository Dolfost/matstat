#include "dataVector.hpp"

#include <QGuiApplication>
#include <QStyleHints>
#include <QtCore/qlist.h>
#include <QtCore/qlogging.h>

#include "classSeries.hpp"
#include "distributionReproducerDialog.hpp"
#include "gui/transformationFormulaEditorDialog.hpp"
#include "gui/vectorInfoDialog.hpp"
#include "hypothesisManagerDialog.hpp"
#include "setGeneratorDialog.hpp"
#include "vectorContainerWidget.hpp"
#include "vectorTrimmerDialog.hpp"

QList<std::pair<VectorEntry *, QTableWidgetItem *>>
VectorContainerWidget::selectedVectors() {
  QList<std::pair<VectorEntry *, QTableWidgetItem *>> vectors;
  QList<QTableWidgetItem *> items = this->selectedItems();
  for (auto const &item : items) {
    if (item->type() == VectorContainerWidget::InfoCell::Name) {
      vectors.push_back(
          {item->data(Qt::UserRole).value<VectorEntry *>(), item});
    }
  }
  return vectors;
}

std::pair<VectorEntry *, QTableWidgetItem *>
VectorContainerWidget::selectedVector() {
  QTableWidgetItem *item = this->item(this->currentRow(), InfoCell::Name);
  return {item->data(Qt::UserRole).value<VectorEntry *>(), item};
}

VectorContainerWidget::VectorContainerWidget(QWidget *parent)
    : QTableWidget(parent) {
  this->setColumnCount(InfoCell::Count);
  this->setRowCount(0);
  this->setAcceptDrops(false);
  this->setDragEnabled(false);
  this->setSelectionBehavior(QAbstractItemView::SelectRows);
  this->setSelectionMode(QAbstractItemView::ExtendedSelection);
  this->setEditTriggers(QAbstractItemView::NoEditTriggers);
  this->verticalHeader()->hide();
  this->setContextMenuPolicy(Qt::CustomContextMenu);

  QStringList headers = {"Назва", "Розмір", "Мін.", "Макс.", "Файл"};
  QList<int> widths = {90, 60, 75, 75};

  for (int i = 0; i < InfoCell::Count; i++) {
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setText(headers[i]);
    this->setColumnWidth(i, widths[i]);
    this->setHorizontalHeaderItem(i, item);
  }

  connect(this, &QTableWidget::customContextMenuRequested, this,
          &VectorContainerWidget::showContextMenu);
  connect(this, &QTableWidget::cellDoubleClicked, this,
          &VectorContainerWidget::makeActiveAction);
}

void VectorContainerWidget::appendVector(VectorEntry *vectorEntry) {
  int row = this->rowCount();

  this->insertRow(row);

  this->setColumnCount(
      (vectorEntry->vector->size() + InfoCell::Count > this->columnCount()
           ? vectorEntry->vector->size() + InfoCell::Count
           : this->columnCount()));
  if (vectorEntry->name.length() == 0)
    vectorEntry->name = "V" + QString::number(++vectorCount);

  fillRow(row, vectorEntry);
}

void VectorContainerWidget::appendList(const std::list<double> *vec,
                                       QString name) {
  VectorEntry *vectorEntry = new VectorEntry;
  vectorEntry->vector = new DataVector(*vec);
  vectorEntry->name = name;
  appendVector(vectorEntry);
}

void VectorContainerWidget::fillRow(int row, VectorEntry *vectorEntry) {
  QList<HorizontalHeaderItem *> infoItems;
  infoItems.append(new HorizontalHeaderItem(InfoCell::Name));
  infoItems[InfoCell::Name]->setData(Qt::DisplayRole,
                                     QVariant(vectorEntry->name));
  infoItems[InfoCell::Name]->setData(Qt::UserRole,
                                     QVariant::fromValue(vectorEntry));

  infoItems.append(new HorizontalHeaderItem(InfoCell::Size));
  infoItems[InfoCell::Size]->setData(
      Qt::DisplayRole, QVariant((int)vectorEntry->vector->size()));

  infoItems.append(new HorizontalHeaderItem(InfoCell::Min));
  infoItems[InfoCell::Min]->setData(Qt::DisplayRole,
                                    QVariant(vectorEntry->vector->min()));

  infoItems.append(new HorizontalHeaderItem(InfoCell::Max));
  infoItems[InfoCell::Max]->setData(Qt::DisplayRole,
                                    QVariant(vectorEntry->vector->max()));

  for (int i = 0; i < InfoCell::Count; i++) {
    this->setItem(row, i, infoItems[i]);
  }

  auto list = vectorEntry->vector->vector();
  auto it = list.begin();
  for (size_t col = InfoCell::Count;
       col < vectorEntry->vector->size() + InfoCell::Count; col++) {
    QTableWidgetItem *tableItem = new QTableWidgetItem(DataCell::Data);
    tableItem->setText(QString::number(*it, 'f', precision));
    it++;
    this->setItem(row, col, tableItem);
  }

  for (size_t i = InfoCell::Count; i < this->columnCount() + InfoCell::Count;
       i++) {
    QTableWidgetItem *headerItem = new QTableWidgetItem();
    headerItem->setText(QString::number(i - InfoCell::Count + 1));
    this->setHorizontalHeaderItem(i, headerItem);
  }
}

void VectorContainerWidget::refillRow(int idx, VectorEntry *vectorEntry) {
  fillRow(idx, vectorEntry);
}

void VectorContainerWidget::showContextMenu(const QPoint &pos) {
  if (this->currentRow() == -1)
    return;

  QMenu menu;

  QAction *setActiveAction = menu.addAction("Додати до процессора");
  connect(setActiveAction, &QAction::triggered, this,
          &VectorContainerWidget::makeActiveAction);

  menu.addSeparator();

  QAction *removeOutliersAction = menu.addAction("Видалити аномалії");
  connect(removeOutliersAction, &QAction::triggered, this,
          &VectorContainerWidget::removeOutliersAction);

  QAction *trimAction = menu.addAction("Обрізати…");
  connect(trimAction, &QAction::triggered, this,
          &VectorContainerWidget::trimAction);

  QMenu *transform = menu.addMenu("Трансформації…");
  QAction *normalizeAction = transform->addAction("Нормалізувати");
  connect(normalizeAction, &QAction::triggered, this,
          &VectorContainerWidget::standardizeAction);
  QAction *logAction = transform->addAction("Логарифмувати");
  connect(logAction, &QAction::triggered, this,
          &VectorContainerWidget::logAction);
  QAction *reverseAction = transform->addAction("Обернути");
  connect(reverseAction, &QAction::triggered, this,
          &VectorContainerWidget::reverseAction);
  QAction *rightShiftAction = transform->addAction("Зсунути на xₘᵢₙ+1");
  connect(rightShiftAction, &QAction::triggered, this,
          &VectorContainerWidget::rightShiftAction);
  transform->addSeparator();
  QAction *transformAction = transform->addAction("Власне перетворення…");
  connect(transformAction, &QAction::triggered, this,
          &VectorContainerWidget::transformAction);

  QAction *reproductionAction = menu.addAction("Відтворення розподілу…");
  connect(reproductionAction, &QAction::triggered, this,
          &VectorContainerWidget::reproductionAction);

  QAction *generateAction = menu.addAction("Генерація вибірки…");
  connect(generateAction, &QAction::triggered, this,
          &VectorContainerWidget::generateAction);

  menu.addSeparator();

  QMenu *hypotesisMenu = menu.addMenu("Перевірка гіпотез…");

  QMenu *tTestMenu = hypotesisMenu->addMenu("Т—тести…");
  QAction *tTestDependentAction = tTestMenu->addAction("Залежні вибірки…");
  connect(tTestDependentAction, &QAction::triggered, this,
	[this](){ this->makeHypothesisAction(DataVectorSet::tTestDependentP); });
  QAction *tTestIndependentAction = tTestMenu->addAction("Незалежні вибірки…");
  connect(tTestIndependentAction, &QAction::triggered, this,
	[this](){ this->makeHypothesisAction(DataVectorSet::tTestIndependentP); });

  QMenu *fTestMenu = hypotesisMenu->addMenu("F—тести…");
  QAction* fTestAction = fTestMenu->addAction("F—тест");
  connect(fTestAction, &QAction::triggered, this,
	[this](){ this->makeHypothesisAction(DataVectorSet::fTestP); });
  QAction* fTestBartlettAction = fTestMenu->addAction("F—тест Бартлетта");
  connect(fTestBartlettAction, &QAction::triggered, this,
	[this](){ this->makeHypothesisAction(DataVectorSet::fTestBartlettP); });

  QMenu *indentityMenu = hypotesisMenu->addMenu("Тести однорідності…");

  QAction* testKSAction = indentityMenu->addAction("Тест Колмогорова-Смірнова");
  connect(testKSAction, &QAction::triggered, this,
	[this](){ this->makeHypothesisAction(DataVectorSet::testKSP); });

  QAction* testWilcoxonAction = indentityMenu->addAction("Критерій суми рангів Вілкоксона");
  connect(testWilcoxonAction, &QAction::triggered, this,
	[this](){ this->makeHypothesisAction(DataVectorSet::testWilcoxonP); });

  QAction* criteriaUAction = indentityMenu->addAction("U-критерій");
  connect(criteriaUAction, &QAction::triggered, this,
	[this](){ this->makeHypothesisAction(DataVectorSet::criteriaUP); });

  QAction* rankAveragesDifferenceAction = indentityMenu->addAction("Крит. різн. сер. ранг. виб.");
  connect(rankAveragesDifferenceAction, &QAction::triggered, this,
	[this](){ this->makeHypothesisAction(DataVectorSet::rankAveragesDifferenceP); });

  QAction* hTestAction = indentityMenu->addAction("H-критерій");
  connect(hTestAction, &QAction::triggered, this,
	[this](){ this->makeHypothesisAction(DataVectorSet::hTestP); });

  QAction* oneWayANOVAAction = hypotesisMenu->addAction("Одноф. дисп. аналіз");
  connect(oneWayANOVAAction, &QAction::triggered, this,
	[this](){ this->makeHypothesisAction(DataVectorSet::oneWayANOVAP); });

  menu.addSeparator();

  QAction *infoAction = menu.addAction("Про вектор…");
  connect(infoAction, &QAction::triggered, this,
          &VectorContainerWidget::infoAction);

  QAction *writeAction = menu.addAction("Зберегти у файл…");
  connect(writeAction, &QAction::triggered, this,
          &VectorContainerWidget::writeAction);

  menu.addSeparator();

  QAction *deleteAction = menu.addAction("Видалити");
  connect(deleteAction, &QAction::triggered, this,
          &VectorContainerWidget::deleteAction);

  menu.exec(mapToGlobal(pos));
}

void VectorContainerWidget::makeActiveAction() {
  QList<std::pair<VectorEntry *, QTableWidgetItem *>> vectors =
      selectedVectors();
  for (auto const &vec : vectors) {
    emit vectorSelected(vec.first);
  }
}

void VectorContainerWidget::deleteAction() {
  QList<std::pair<VectorEntry *, QTableWidgetItem *>> vectors =
      selectedVectors();
  for (auto const &vec : vectors) {
    emit vectorDeleted(vec.first);
    delete vec.first;
    this->removeRow(this->indexFromItem(vec.second).row());
  }
}

void VectorContainerWidget::standardizeAction() {
  QList<std::pair<VectorEntry *, QTableWidgetItem *>> vectors =
      selectedVectors();
  for (auto const &vec : vectors) {
    DataVector newVector(vec.first->vector->vector());
    newVector.standardize();
    appendList(&newVector.vector(), QString("S(%1)").arg(vec.first->name));
  }
}

void VectorContainerWidget::logAction() {
  QList<std::pair<VectorEntry *, QTableWidgetItem *>> vectors =
      selectedVectors();
  for (auto const &vec : vectors) {
    DataVector newVector(vec.first->vector->vector());
    newVector.transform("log(x)");
    appendList(&newVector.vector(), QString("LN(%1)").arg(vec.first->name));
  }
}

void VectorContainerWidget::reverseAction() {
  QList<std::pair<VectorEntry *, QTableWidgetItem *>> vectors =
      selectedVectors();
  for (auto const &vec : vectors) {
    DataVector newVector(vec.first->vector->vector());
    newVector.transform("1/x");
    appendList(&newVector.vector(), QString("R(%1)").arg(vec.first->name));
  }
}

void VectorContainerWidget::rightShiftAction() {
  QList<std::pair<VectorEntry *, QTableWidgetItem *>> vectors =
      selectedVectors();
  for (auto const &vec : vectors) {
    DataVector newVector(vec.first->vector->vector());
    newVector.transform("x+abs(xmin)+1");
    appendList(&newVector.vector(), QString("RS(%1)").arg(vec.first->name));
  }
}

void VectorContainerWidget::transformAction() {
  QList<std::pair<VectorEntry *, QTableWidgetItem *>> vectors =
      selectedVectors();
  QList<VectorEntry *> vec;

  for (auto const &v : vectors) {
    vec.push_back(v.first);
  }

  TransformationFormulaEditorDialog *tfe =
      new TransformationFormulaEditorDialog(vec, this);
  connect(tfe, &TransformationFormulaEditorDialog::vectorTransformed, this,
          &VectorContainerWidget::appendVector);
  connect(this, &VectorContainerWidget::vectorDeleted, tfe,
          &TransformationFormulaEditorDialog::vectorDeletedHandler);
}

void VectorContainerWidget::reproductionAction() {
  QList<std::pair<VectorEntry *, QTableWidgetItem *>> vectors =
      selectedVectors();

  for (auto const &vec : vectors) {
    if (vec.first->vector->classSeries() == nullptr) {
      vec.first->vector->makeClassSeries();
      emit message(
          "Вектор " + vec.first->name + " було розбито на " +
          QString::number(vec.first->vector->classSeries()->classCount()) +
          " класів");
    }

    DistributionReproducerDialog *drd =
        new DistributionReproducerDialog(vec.first, this);
    connect(this, &VectorContainerWidget::vectorDeleted, drd,
            &DistributionReproducerDialog::vectorDeletedHandler);
    connect(drd, &DistributionReproducerDialog::distributionSelected,
            [=]() { emit distributionSelected(vec.first); });
  }
}

void VectorContainerWidget::trimAction() {
  QList<std::pair<VectorEntry *, QTableWidgetItem *>> vectors =
      selectedVectors();

  for (auto const &vec : vectors) {
    VectorTrimmerDialog *vtd = new VectorTrimmerDialog(vec.first, this);
    connect(vtd, &VectorTrimmerDialog::vectorTrimmed, this,
            &VectorContainerWidget::appendVector);
    connect(this, &VectorContainerWidget::vectorDeleted, vtd,
            &VectorTrimmerDialog::vectorDeletedHandler);
  }
}

void VectorContainerWidget::removeOutliersAction() {
  QList<std::pair<VectorEntry *, QTableWidgetItem *>> vectors =
      selectedVectors();

  for (auto const &vec : vectors) {
    DataVector newVector(vec.first->vector->vector());
    bool ok = newVector.removeOutliers();

    emit outliersRemoved(ok);

    if (!ok) // no entries removed
      return;

    appendList(&newVector.vector(), QString("RMOUT(%1)").arg(vec.first->name));
  }
}

void VectorContainerWidget::infoAction() {
  QList<std::pair<VectorEntry *, QTableWidgetItem *>> vectors =
      selectedVectors();

  for (auto const &vec : vectors) {
    VectorInfoDialog *tfe = new VectorInfoDialog(vec.first, this);
    connect(this, &VectorContainerWidget::vectorDeleted, tfe,
            &VectorInfoDialog::vectorDeletedHandler);
  }
}

void VectorContainerWidget::generateAction() {
  QList<std::pair<VectorEntry *, QTableWidgetItem *>> vectors =
      selectedVectors();

  for (auto const &vec : vectors) {
    SetGeneratorDialog *sgd = new SetGeneratorDialog(vec.first, this);
    connect(this, &VectorContainerWidget::vectorDeleted, sgd,
            &SetGeneratorDialog::vectorDeletedHandler);
    connect(sgd, &SetGeneratorDialog::setGenerated, this,
            &VectorContainerWidget::appendVector);
    connect(sgd, &SetGeneratorDialog::message,
            [=](QString msg) { emit message(msg); });
  }
}

void VectorContainerWidget::writeAction() {
  std::pair<VectorEntry *, QTableWidgetItem *> ve = selectedVector();

  QString filename = QFileDialog::getSaveFileName(
      this, "Зберегти вектор",
      QDir::homePath() + "/" + ve.first->name + "-" +
          QString::number(ve.first->vector->size()) + ".txt",
      "Текстові файли (*.txt) ;; CSV файли (*.csv)");

  if (filename.length() == 0)
    return;

  ve.first->vector->writeToFile(filename);
}

void VectorContainerWidget::makeHypothesisAction(DataVectorSet::Procedure p) {
  QList<std::pair<VectorEntry *, QTableWidgetItem *>> vectors =
      selectedVectors();

  QList<VectorEntry *> vec;
  for (auto const &v : vectors)
    vec.push_back(v.first);

  HypothesisManagerDialog *hmd = new HypothesisManagerDialog(
      vec, p, this);
  connect(this, &VectorContainerWidget::vectorDeleted, hmd,
          &HypothesisManagerDialog::vectorDeletedHandler);
}

HorizontalHeaderItem::HorizontalHeaderItem(int type) : QTableWidgetItem(type) {
  QColor col;

  if (QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark)
    col.setRgb(65, 65, 65);
  else
    col.setRgb(219, 219, 219);

  this->setBackground(col);
}
