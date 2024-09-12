#include "vector.hpp"

#include <QGuiApplication>
#include <QStyleHints>
#include <QtCore/qlist.h>
#include <QtCore/qlogging.h>

#include "distributionReproducerDialog.hpp"
#include "transformationFormulaEditorDialog.hpp"
#include "vectorInfoDialog.hpp"
#include "hypothesisManagerDialog.hpp"
#include "setGeneratorDialog.hpp"
#include "vectorContainerWidget.hpp"
#include "vectorTrimmerDialog.hpp"

#include <spinBoxAction.hpp>

#include <distributionDialog.hpp>
#include <densityDialog.hpp>

QList<std::pair<Vector*, QTableWidgetItem*>>
VectorContainerWidget::selectedVectors() {
	QList<std::pair<Vector*, QTableWidgetItem *>> vectors;
	QList<QTableWidgetItem*> items = this->selectedItems();
	for (auto const &item : items) {
		if (item->type() == VectorContainerWidget::InfoCell::Name) {
			vectors.push_back(
				{item->data(Qt::UserRole).value<Vector *>(), item});
		}
	}
	return vectors;
}

std::pair<Vector*, QTableWidgetItem*>
VectorContainerWidget::selectedVector() {
	QTableWidgetItem *item = this->item(this->currentRow(), InfoCell::Name);
	return {item->data(Qt::UserRole).value<Vector*>(), item};
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

void VectorContainerWidget::appendVector(Vector *vectorEntry) {
	int row = this->rowCount();

	this->insertRow(row);

	this->setColumnCount(
		(vectorEntry->vector()->size() + InfoCell::Count > this->columnCount()
		? vectorEntry->vector()->size() + InfoCell::Count
		: this->columnCount()));
	if (vectorEntry->name().length() == 0)
		vectorEntry->setName("V" + QString::number(++vectorCount));

	fillRow(row, vectorEntry);
}

void VectorContainerWidget::appendList(const std::list<double> *vec,
																			 QString name) {
	Vector *vectorEntry = new Vector;
	vectorEntry->setVector(new ss::Vector(*vec));
	vectorEntry->setName(name);
	appendVector(vectorEntry);
}

void VectorContainerWidget::fillRow(int row, Vector *vectorEntry) {
	QList<HorizontalHeaderItem *> infoItems;
	infoItems.append(new HorizontalHeaderItem(InfoCell::Name));
	infoItems[InfoCell::Name]->setData(Qt::DisplayRole,
																		QVariant(vectorEntry->name()));
	infoItems[InfoCell::Name]->setData(Qt::UserRole,
																		QVariant::fromValue(vectorEntry));

	infoItems.append(new HorizontalHeaderItem(InfoCell::Size));
	infoItems[InfoCell::Size]->setData(
		Qt::DisplayRole, QVariant((int)vectorEntry->vector()->size()));

	infoItems.append(new HorizontalHeaderItem(InfoCell::Min));
	infoItems[InfoCell::Min]->setData(Qt::DisplayRole,
																	 QVariant(vectorEntry->vector()->min()));

	infoItems.append(new HorizontalHeaderItem(InfoCell::Max));
	infoItems[InfoCell::Max]->setData(Qt::DisplayRole,
																	 QVariant(vectorEntry->vector()->max()));

	for (int i = 0; i < InfoCell::Count; i++) {
		this->setItem(row, i, infoItems[i]);
	}

	auto list = vectorEntry->vector();
	auto it = list->begin();
	for (size_t col = InfoCell::Count;
	col < vectorEntry->vector()->size() + InfoCell::Count; col++) {
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

void VectorContainerWidget::refillRow(int idx, Vector *vectorEntry) {
	fillRow(idx, vectorEntry);
}

void VectorContainerWidget::showContextMenu(const QPoint &pos) {
	if (this->currentRow() == -1)
		return;

	QMenu* menu;

	menu = vectorContextMenu();

	menu->exec(mapToGlobal(pos));
	delete menu;
}

QMenu* VectorContainerWidget::vectorContextMenu() {
	QMenu* menu = new QMenu;

	QMenu *graphics = menu->addMenu("Графіка…");
	QAction *distribution = graphics->addAction("Функція розподілу");
	connect(distribution, &QAction::triggered, this,
				 &VectorContainerWidget::vectorDistributionAction);
	QAction *density = graphics->addAction("Функція щільності");
	connect(density, &QAction::triggered, this,
				 &VectorContainerWidget::vectorDensityAction);
	SpinBoxAction *classCountAction = new SpinBoxAction("Кількість класів");
	classCountAction->spinBox()->setRange(0, 1000);
	graphics->addAction(classCountAction);
	connect(classCountAction->spinBox(), &QSpinBox::valueChanged, this,
				 &VectorContainerWidget::classCountAction);
	DoubleSpinBoxAction *confidence = new DoubleSpinBoxAction("Критерій довіри");
	confidence->spinBox()->setRange(0.0, 1.0);
	confidence->spinBox()->setDecimals(5);
	confidence->spinBox()->setSingleStep(0.1);
	graphics->addAction(confidence);
	connect(confidence->spinBox(), &QDoubleSpinBox::valueChanged, this,
				 &VectorContainerWidget::confidenceAction);

	menu->addSeparator();

	QAction *removeOutliersAction = menu->addAction("Видалити аномалії");
	connect(removeOutliersAction, &QAction::triggered, this,
				 &VectorContainerWidget::removeOutliersAction);

	QAction *trimAction = menu->addAction("Обрізати…");
	connect(trimAction, &QAction::triggered, this,
				 &VectorContainerWidget::trimAction);

	QMenu *transform = menu->addMenu("Трансформації…");
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

	QAction *reproductionAction = menu->addAction("Відтворення розподілу…");
	connect(reproductionAction, &QAction::triggered, this,
				 &VectorContainerWidget::reproductionAction);

	QAction *generateAction = menu->addAction("Генерація вибірки…");
	connect(generateAction, &QAction::triggered, this,
				 &VectorContainerWidget::generateAction);

	menu->addSeparator();

	QMenu *hypotesisMenu = menu->addMenu("Перевірка гіпотез…");

	QMenu *tTestMenu = hypotesisMenu->addMenu("Т—тести…");
	QAction *tTestDependentAction = tTestMenu->addAction("Залежні вибірки…");
	connect(tTestDependentAction, &QAction::triggered, this,
				 [this](){ this->makeHypothesisAction(ss::VectorChain::tTestDependentP); });
	QAction *tTestIndependentAction = tTestMenu->addAction("Незалежні вибірки…");
	connect(tTestIndependentAction, &QAction::triggered, this,
				 [this](){ this->makeHypothesisAction(ss::VectorChain::tTestIndependentP); });

	QMenu *fTestMenu = hypotesisMenu->addMenu("F—тести…");
	QAction* fTestAction = fTestMenu->addAction("F—тест");
	connect(fTestAction, &QAction::triggered, this,
				 [this](){ this->makeHypothesisAction(ss::VectorChain::fTestP); });
	QAction* fTestBartlettAction = fTestMenu->addAction("F—тест Бартлетта");
	connect(fTestBartlettAction, &QAction::triggered, this,
				 [this](){ this->makeHypothesisAction(ss::VectorChain::fTestBartlettP); });

	QMenu *indentityMenu = hypotesisMenu->addMenu("Тести однорідності…");

	QAction* testKSAction = indentityMenu->addAction("Тест Колмогорова-Смірнова");
	connect(testKSAction, &QAction::triggered, this,
				 [this](){ this->makeHypothesisAction(ss::VectorChain::testKSP); });

	QAction* testWilcoxonAction = indentityMenu->addAction("Критерій суми рангів Вілкоксона");
	connect(testWilcoxonAction, &QAction::triggered, this,
				 [this](){ this->makeHypothesisAction(ss::VectorChain::testWilcoxonP); });

	QAction* criteriaUAction = indentityMenu->addAction("U-критерій");
	connect(criteriaUAction, &QAction::triggered, this,
				 [this](){ this->makeHypothesisAction(ss::VectorChain::criteriaUP); });

	QAction* rankAveragesDifferenceAction = indentityMenu->addAction("Крит. різн. сер. ранг. виб.");
	connect(rankAveragesDifferenceAction, &QAction::triggered, this,
				 [this](){ this->makeHypothesisAction(ss::VectorChain::rankAveragesDifferenceP); });

	QAction* hTestAction = indentityMenu->addAction("H-критерій");
	connect(hTestAction, &QAction::triggered, this,
				 [this](){ this->makeHypothesisAction(ss::VectorChain::hTestP); });

	QAction* signTestAction = indentityMenu->addAction("Критерій знаків");
	connect(signTestAction, &QAction::triggered, this,
				 [this](){ this->makeHypothesisAction(ss::VectorChain::signTestP); });

	QAction* oneWayANOVAAction = hypotesisMenu->addAction("Одноф. дисп. аналіз");
	connect(oneWayANOVAAction, &QAction::triggered, this,
				 [this](){ this->makeHypothesisAction(ss::VectorChain::oneWayANOVAP); });

	QAction* qTest = hypotesisMenu->addAction("Q-критерій Кохрена");
	connect(qTest, &QAction::triggered, this,
				 [this](){ this->makeHypothesisAction(ss::VectorChain::qTestP); });

	QAction* testAbbeAction = hypotesisMenu->addAction("Критерій Аббе");
	connect(testAbbeAction, &QAction::triggered, this,
				 [this](){ this->makeHypothesisAction(ss::VectorChain::testAbbeP); });

	menu->addSeparator();

	QAction *infoAction = menu->addAction("Про вектор…");
	connect(infoAction, &QAction::triggered, this,
				 &VectorContainerWidget::infoAction);

	QAction *writeAction = menu->addAction("Зберегти у файл…");
	connect(writeAction, &QAction::triggered, this,
				 &VectorContainerWidget::writeAction);

	menu->addSeparator();

	QAction *deleteAction = menu->addAction("Видалити");
	connect(deleteAction, &QAction::triggered, this,
				 &VectorContainerWidget::deleteAction);

	return menu;
}

void VectorContainerWidget::classCountAction(int cls) {
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
		selectedVectors();
	for (auto const &vec : vectors) {
		vec.first->vector()->cs.setCount(cls);
		emit redrawVector(vec.first);
	}
}

void VectorContainerWidget::confidenceAction(double c) {
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
		selectedVectors();
	for (auto const &vec : vectors) {
		vec.first->vector()->dist.setConfidence(c);
		emit redrawVector(vec.first);
	}
}

void VectorContainerWidget::vectorDistributionAction() {
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
		selectedVectors();

	for (auto const &v : vectors) {
		DistributionDialog* dia = new DistributionDialog(vectors.front().first, this);
		connect(this, SIGNAL(redrawVector(Vector*)),
					dia, SLOT(fill()));
		connect(this, &VectorContainerWidget::vectorDeleted,
			dia, &DistributionDialog::vectorDeletedHandler);
	}
}

void VectorContainerWidget::vectorDensityAction() {
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
		selectedVectors();

	for (auto const &v : vectors) {
		DensityDialog* dia = new DensityDialog(vectors.front().first, this);
		connect(this, SIGNAL(redrawVector(Vector*)),
					dia, SLOT(fill()));
		connect(this, &VectorContainerWidget::vectorDeleted,
					dia, &DensityDialog::vectorDeletedHandler);
	}
}

void VectorContainerWidget::makeActiveAction() {
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
		selectedVectors();
	for (auto const &vec : vectors) {
		emit vectorSelected(vec.first);
	}
}

void VectorContainerWidget::deleteAction() {
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
		selectedVectors();
	for (auto const &vec : vectors) {
		emit vectorDeleted(vec.first);
		delete vec.first;
		this->removeRow(this->indexFromItem(vec.second).row());
	}
}

void VectorContainerWidget::standardizeAction() {
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
		selectedVectors();
	for (auto const &vec : vectors) {
		ss::Vector newVector(*vec.first->vector());
		newVector.standardize();
		appendList(&newVector.list(), QString("S(%1)").arg(vec.first->name()));
		//  TODO: move from std::list to Vector insertion
	}
}

void VectorContainerWidget::logAction() {
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
		selectedVectors();
	for (auto const &vec : vectors) {
		ss::Vector newVector(vec.first->vector()->list());
		newVector.transform("log(x)");
		appendList(&newVector.list(), QString("LN(%1)").arg(vec.first->name()));
	}
}

void VectorContainerWidget::reverseAction() {
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
		selectedVectors();
	for (auto const &vec : vectors) {
		ss::Vector newVector(vec.first->vector()->list());
		newVector.transform("1/x");
		appendList(&newVector.list(), QString("R(%1)").arg(vec.first->name()));
	}
}

void VectorContainerWidget::rightShiftAction() {
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
		selectedVectors();
	for (auto const &vec : vectors) {
		ss::Vector newVector(vec.first->vector()->list());
		newVector.transform("x+abs(xmin)+1");
		appendList(&newVector.list(), QString("RS(%1)").arg(vec.first->name()));
	}
}

void VectorContainerWidget::transformAction() {
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
		selectedVectors();
	QList<Vector *> vec;

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
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
		selectedVectors();

	for (auto const &vec : vectors) {
		DistributionReproducerDialog *drd =
			new DistributionReproducerDialog(vec.first, this);
		connect(this, &VectorContainerWidget::vectorDeleted, drd,
					&DistributionReproducerDialog::vectorDeletedHandler);
		connect(drd, &DistributionReproducerDialog::distributionSelected,
					[=]() { emit redrawVector(vec.first); });
	}
}

void VectorContainerWidget::trimAction() {
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
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
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
		selectedVectors();

	for (auto const &vec : vectors) {
		ss::Vector newVector(vec.first->vector()->list());
		bool ok = newVector.removeOutliers();

		emit outliersRemoved(ok);

		if (!ok) // no entries removed
			return;

		appendList(&newVector.list(), QString("RMOUT(%1)").arg(vec.first->name()));
	}
}

void VectorContainerWidget::infoAction() {
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
		selectedVectors();

	for (auto const &vec : vectors) {
		VectorInfoDialog *tfe = new VectorInfoDialog(vec.first, this);
		connect(this, &VectorContainerWidget::vectorDeleted, tfe,
					&VectorInfoDialog::vectorDeletedHandler);
	}
}

void VectorContainerWidget::generateAction() {
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
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
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
		selectedVectors();

	QString names;
	for (auto const& v : vectors) {
		names.append(QString("%1(%2),")
							 .arg(v.first->name())
							 .arg(v.first->vector()->size()));
	}
	names.chop(1);

	QString filename = QFileDialog::getSaveFileName(
		this, "Зберегти вектор",
		QDir::homePath() + "/" + names + ".txt",
		"Текстові файли (*.txt) ;; CSV файли (*.csv)");

	if (filename.length() == 0)
		return;

	ss::VectorChain set;
	for (auto const &v : vectors)
	set.push_back(v.first->vector());

	try {
		set.writeToFile(filename.toStdString());
	} catch (const char* msg) {
		message(msg);
	}
}

void VectorContainerWidget::makeHypothesisAction(ss::VectorChain::Procedure p) {
	QList<std::pair<Vector *, QTableWidgetItem *>> vectors =
		selectedVectors();

	QList<Vector *> vec;
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
