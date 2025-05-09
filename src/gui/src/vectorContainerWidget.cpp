#include "vector.hpp"

#include <QGuiApplication>
#include <QStyleHints>
#include <QList>
#include <QDebug>

#include <spinBoxAction.hpp>

#include <vectorDistributionReproducerDialog.hpp>
#include <setGeneratorDialog.hpp>

#include <vectorContainerWidget.hpp>

#include <vectorInfoDialog.hpp>
#include <vectorTrimmerDialog.hpp>
#include <vectorDistributionDialog.hpp>
#include <vectorDensityDialog.hpp>
#include <vectorHypothesisDialog.hpp>
#include <vectorTransformationDialog.hpp>

#include <vectorPairDistributionDialog.hpp>
#include <vectorPairCorelationDialog.hpp>
#include <vectorPairDensityDialog.hpp>
#include <vectorPairDensity3dDialog.hpp>
#include <vectorPairInfoDialog.hpp>
#include <vectorPairHypothesisDialog.hpp>
#include <vectorPairTransformationDialog.hpp>
#include <vectorPairConnectionsTableInfoDialog.hpp>
#include <vectorPairRegressionReproducerDialog.hpp>

#include <vectorChainInfoDialog.hpp>
#include <vectorChainField3dDialog.hpp>
#include <vectorChainCorelationCoeficientDialog.hpp>
#include <vectorChainScatterPlotMatrixDialog.hpp>

VectorContainerWidget::SelectedT<VectorEntry>
VectorContainerWidget::selectedVectors() {
	SelectedT<VectorEntry> vectors;
	QList<QTableWidgetItem*> items = this->selectedItems();
	for (auto const &item : items) {
		if (item->type() == VectorContainerWidget::InfoCell::Name) {
			vectors.push_back(item->data(Qt::UserRole).value<VectorEntry*>());
		}
	}
	return vectors;
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
}

void VectorContainerWidget::placeList(const std::vector<double>& l) {
	ss::Vector v = ss::Vector(l);
	placeVector(v);
}

void VectorContainerWidget::appendVector(Vector* v) {
	int row = this->rowCount();

	this->insertRow(row);

	this->setColumnCount(
		(v->vector()->size() + InfoCell::Count > this->columnCount()
		? v->vector()->size() + InfoCell::Count
		: this->columnCount()));
	if (v->name().length() == 0)
		v->setName("V" + QString::number(++vectorCount));

	QList<HorizontalHeaderItem *> infoItems;
	infoItems.append(new HorizontalHeaderItem(InfoCell::Name));
	infoItems[InfoCell::Name]->setData(Qt::DisplayRole,
																		QVariant(v->name()));
	v->setTableItem(infoItems[InfoCell::Name]);
	infoItems[InfoCell::Name]->setData(Qt::UserRole,
																		QVariant::fromValue(static_cast<VectorEntry*>(v)));

	infoItems.append(new HorizontalHeaderItem(InfoCell::Size));
	infoItems[InfoCell::Size]->setData(
		Qt::DisplayRole, QVariant((int)v->vector()->size()));

	infoItems.append(new HorizontalHeaderItem(InfoCell::Min));
	infoItems[InfoCell::Min]->setData(Qt::DisplayRole,
																	 QVariant(v->vector()->min()));

	infoItems.append(new HorizontalHeaderItem(InfoCell::Max));
	infoItems[InfoCell::Max]->setData(Qt::DisplayRole,
																	 QVariant(v->vector()->max()));

	for (int i = 0; i < InfoCell::Count; i++) {
		this->setItem(row, i, infoItems[i]);
	}

	auto list = v->vector();
	auto it = list->begin();
	for (size_t col = InfoCell::Count;
	col < v->vector()->size() + InfoCell::Count; col++) {
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

void VectorContainerWidget::appendVectorPair(VectorPair* vp) {
	int row = this->rowCount();

	this->insertRow(row);
	this->setRowHeight(row, this->horizontalHeader()->height()*2);

	this->setColumnCount(
		(vp->vectorPair()->size() + InfoCell::Count > this->columnCount()
		? vp->vectorPair()->size() + InfoCell::Count
		: this->columnCount()));
	if (vp->name().length() == 0)
		vp->setName("VP" + QString::number(++vectorCount));

	QList<HorizontalHeaderItem *> infoItems;
	infoItems.append(new HorizontalHeaderItem(InfoCell::Name));
	infoItems[InfoCell::Name]->setData(Qt::DisplayRole,
																		QVariant(vp->name()));
	vp->setTableItem(infoItems[InfoCell::Name]);
	infoItems[InfoCell::Name]->setData(Qt::UserRole,
																		QVariant::fromValue(static_cast<VectorEntry*>(vp)));

	infoItems.append(new HorizontalHeaderItem(InfoCell::Size));
	infoItems[InfoCell::Size]->setData(
		Qt::DisplayRole, QVariant((int)vp->vectorPair()->x.size()));

	infoItems.append(new HorizontalHeaderItem(InfoCell::Min));
	infoItems[InfoCell::Min]->setData(Qt::DisplayRole,
																	 QVariant(vp->vectorPair()->min()));

	infoItems.append(new HorizontalHeaderItem(InfoCell::Max));
	infoItems[InfoCell::Max]->setData(Qt::DisplayRole,
																	 QVariant(vp->vectorPair()->max()));

	for (int i = 0; i < InfoCell::Count; i++) {
		this->setItem(row, i, infoItems[i]);
	}

	auto x_it = vp->vectorPair()->x.begin();
	auto y_it = vp->vectorPair()->y.begin();
	for (size_t col = InfoCell::Count;
	col < vp->vectorPair()->size() + InfoCell::Count; col++) {
		QTableWidgetItem *tableItem = new QTableWidgetItem(DataCell::Data);
		tableItem->setText(QString("%1\n%2").arg(*x_it).arg(*y_it));
		this->setItem(row, col, tableItem);
		x_it++, y_it++;
	}

	for (size_t i = InfoCell::Count; i < this->columnCount() + InfoCell::Count;
	i++) {
		QTableWidgetItem *headerItem = new QTableWidgetItem();
		headerItem->setText(QString::number(i - InfoCell::Count + 1));
		this->setHorizontalHeaderItem(i, headerItem);
	}
}

void VectorContainerWidget::appendVectorChain(VectorChain* chain) {
	int row = this->rowCount();

	this->insertRow(row);
	this->setRowHeight(row, this->horizontalHeader()->height()*2);

	this->setColumnCount(
		(chain->chain()->at(0).size() + InfoCell::Count > this->columnCount()
		? chain->chain()->at(0).size() + InfoCell::Count
		: this->columnCount()));
	if (chain->name().length() == 0)
		chain->setName("VC" + QString::number(++vectorCount));


	QList<HorizontalHeaderItem *> infoItems;
	infoItems.append(new HorizontalHeaderItem(InfoCell::Name));
	infoItems[InfoCell::Name]->setData(Qt::DisplayRole,
																		QVariant(chain->name()));
	chain->setTableItem(infoItems[InfoCell::Name]);
	infoItems[InfoCell::Name]->setData(Qt::UserRole,
																		QVariant::fromValue(static_cast<VectorEntry*>(chain)));

	infoItems.append(new HorizontalHeaderItem(InfoCell::Size));
	infoItems[InfoCell::Size]->setData(
		Qt::DisplayRole, QVariant(QString("%1x%2").arg(chain->chain()->size()).arg(chain->chain()->at(0).size())));

	QString str;
	for (auto& v: *chain->chain()) {
		str.push_back(QString::number(v.min()) + "\n");
	}
	str.chop(1);

	infoItems.append(new HorizontalHeaderItem(InfoCell::Min));
	infoItems[InfoCell::Min]->setData(Qt::DisplayRole,
																	 QVariant(str));

	str.clear();
	for (auto& v: *chain->chain()) {
		str.push_back(QString::number(v.max()) + "\n");
	}
	str.chop(1);

	infoItems.append(new HorizontalHeaderItem(InfoCell::Max));
	infoItems[InfoCell::Max]->setData(Qt::DisplayRole,
																	 QVariant(str));

	QList<std::vector<double>::const_iterator> its;
	for (auto& it: *chain->chain())
		its.push_back(it.begin());

	for (size_t col = InfoCell::Count;
	col < chain->chain()->at(0).size() + InfoCell::Count; col++) {
		QTableWidgetItem *tableItem = new QTableWidgetItem(DataCell::Data);
		QString str;
		for (auto& it: its) {
			str.append(QString::number(*it) + "\n");
			it++;
		}
		str.chop(1);
		tableItem->setText(str);
		this->setItem(row, col, tableItem);
	}

	for (size_t i = InfoCell::Count; i < this->columnCount() + InfoCell::Count;
	i++) {
		QTableWidgetItem *headerItem = new QTableWidgetItem();
		headerItem->setText(QString::number(i - InfoCell::Count + 1));
		this->setHorizontalHeaderItem(i, headerItem);
	}
	for (int i = 0; i < InfoCell::Count; i++) {
		this->setItem(row, i, infoItems[i]);
	}

	this->resizeRowToContents(row);
}



void VectorContainerWidget::placeVector(ss::Vector& vec,
																			 QString name) {
	Vector *vectorEntry = new Vector;
	vectorEntry->setVector(new ss::Vector(vec));
	vectorEntry->setName(name);
	appendVector(vectorEntry);
}

void VectorContainerWidget::placeVectorPair(ss::VectorPair& vec,
																						QString name) {
	VectorPair *vectorPair = new VectorPair;
	vectorPair->setVectorPair(
		new ss::VectorPair(
			vec.x,
			vec.y
		)
	);
	vectorPair->setName(name);
	appendVectorPair(vectorPair);
}

void VectorContainerWidget::placeVectorChain(ss::VectorChain& chain, QString name) {
	VectorChain *vectorChain = new VectorChain;
	vectorChain->setVectorChain(
		new ss::VectorChain(
			chain.begin(), chain.end()
		)
	);
	vectorChain->setName(name);
	appendVectorChain(vectorChain);
}

void VectorContainerWidget::showContextMenu(const QPoint &pos) {
	if (this->currentRow() == -1)
		return;

	QMenu* menu = new QMenu;

	selectedVectorsEntryesList = selectedVectors();
	selectedVectorsList.clear();
	selectedVectorPairsList.clear();
	selectedVectorChainsList.clear();
	for (auto const& ve : selectedVectorsEntryesList) {
		Vector* v;
		if ((v = dynamic_cast<Vector*>(ve)))
			selectedVectorsList.push_back(v);
		else {
			selectedVectorsList.clear();
			break;
		}
	}
	if (selectedVectorsList.size() == 0) {
		for (auto const& ve : selectedVectorsEntryesList) {
			VectorPair* v;
			if ((v = dynamic_cast<VectorPair*>(ve)))
				selectedVectorPairsList.push_back(v);
			else {
				selectedVectorPairsList.clear();
				break;
			}
		}
	}
	if (selectedVectorPairsList.size() == 0) {
		for (auto const& ve : selectedVectorsEntryesList) {
			VectorChain* v;
			if ((v = dynamic_cast<VectorChain*>(ve)))
				selectedVectorChainsList.push_back(v);
			else {
				selectedVectorChainsList.clear();
				break;
			}
		}
	}

	if (selectedVectorsList.size())
		fillVectorContextMenu(menu);
	else if (selectedVectorPairsList.size())
		fillVectorPairContextMenu(menu);
	else if (selectedVectorChainsList.size())
		fillVectorChainContextMenu(menu);

	fillGenericContextMenu(menu);
	
	menu->exec(mapToGlobal(pos));
	delete menu;
}

void VectorContainerWidget::fillVectorContextMenu(QMenu* menu) {
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
				 &VectorContainerWidget::vectorClassCountAction);
	DoubleSpinBoxAction *confidence = new DoubleSpinBoxAction("Критерій довіри");
	confidence->spinBox()->setRange(0.0, 1.0);
	confidence->spinBox()->setDecimals(5);
	confidence->spinBox()->setSingleStep(0.1);
	connect(confidence->spinBox(), &QDoubleSpinBox::valueChanged, this,
				 &VectorContainerWidget::vectorConfidenceAction);
	graphics->addAction(confidence);

	if (selectedVectorsList.size() == 1) {
		classCountAction->spinBox()->setValue(selectedVectorsList[0]->vector()->cs.count());
		confidence->spinBox()->setValue(selectedVectorsList[0]->vector()->dist.confidenceLevel());
	}

	menu->addSeparator();

	if (selectedVectorsList.size() >= 2) {
		if (selectedVectorsList.size() == 2) {
			QAction* mergePair = menu->addAction("Створити двовимірний об'єкт");
			connect(mergePair, &QAction::triggered, this,
						&VectorContainerWidget::vectorMergePairAction);
		}
		QAction* mergeChain = menu->addAction("Створити багатовимірнйи об'єкт");
		connect(mergeChain, &QAction::triggered, this,
					&VectorContainerWidget::vectorMergeChainAction);
		menu->addSeparator();
	}

	QAction *removeOutliersAction = menu->addAction("Видалити аномалії");
	connect(removeOutliersAction, &QAction::triggered, this,
				 &VectorContainerWidget::vectorRemoveOutliersAction);

	QAction *trimAction = menu->addAction("Обрізати…");
	connect(trimAction, &QAction::triggered, this,
				 &VectorContainerWidget::vectorTrimAction);

	QMenu *transform = menu->addMenu("Трансформації…");
	QAction *normalizeAction = transform->addAction("Нормалізувати");
	connect(normalizeAction, &QAction::triggered, this,
				 &VectorContainerWidget::vectorStandardizeAction);
	QAction *logAction = transform->addAction("Логарифмувати");
	connect(logAction, &QAction::triggered, this,
				 &VectorContainerWidget::vectorLogAction);
	QAction *reverseAction = transform->addAction("Обернути");
	connect(reverseAction, &QAction::triggered, this,
				 &VectorContainerWidget::vectorReverseAction);
	QAction *rightShiftAction = transform->addAction("Зсунути на xₘᵢₙ+1");
	connect(rightShiftAction, &QAction::triggered, this,
				 &VectorContainerWidget::vectorRightShiftAction);
	transform->addSeparator();
	QAction *transformAction = transform->addAction("Власне перетворення…");
	connect(transformAction, &QAction::triggered, this,
				 &VectorContainerWidget::vectorTransformAction);

	QAction *reproductionAction = menu->addAction("Відтворення розподілу…");
	connect(reproductionAction, &QAction::triggered, this,
				 &VectorContainerWidget::vectorReproductionAction);

	menu->addSeparator();

	QMenu *hypotesisMenu = menu->addMenu("Перевірка гіпотез…");

	for (int p = 0; p < (int)ss::VectorHypothesis::Procedure::Count; p++) {
		QAction* act = hypotesisMenu->addAction(QString::fromStdString(ss::VectorHypothesis::procedureName[p]));
		connect(act, &QAction::triggered, this,
				 [p, this](){ this->vectorHypothesisAction(ss::VectorHypothesis::Procedure(p)); });
	}

	menu->addSeparator();

	QAction *infoAction = menu->addAction("Про вектор…");
	connect(infoAction, &QAction::triggered, this,
				 &VectorContainerWidget::vectorInfoAction);

	QAction *writeAction = menu->addAction("Зберегти у файл…");
	connect(writeAction, &QAction::triggered, this,
				 &VectorContainerWidget::vectorWriteAction);

}

void VectorContainerWidget::fillVectorPairContextMenu(QMenu* menu) {
	QMenu *graphics = menu->addMenu("Графіка…");
	QAction *distribution = graphics->addAction("Функція розподілу");
	connect(distribution, &QAction::triggered, this,
				 &VectorContainerWidget::vectorPairDistributionAction);

	QAction *density = graphics->addAction("Функція щільності");
	connect(density, &QAction::triggered, this,
				 &VectorContainerWidget::vectorPairDensityAction);

	QAction *corelation = graphics->addAction("Кореляційне поле");
	connect(corelation, &QAction::triggered, this,
				 &VectorContainerWidget::vectorPairCorelationAction);

	QAction *density3d = graphics->addAction("Відтворена функція щільності");
	connect(density3d, &QAction::triggered, this,
				 &VectorContainerWidget::vectorPairDensity3dAction);

	SpinBoxAction *classCountActionX = new SpinBoxAction("Кількість класів по х");
	classCountActionX->spinBox()->setRange(0, 1000);
	graphics->addAction(classCountActionX);
	connect(classCountActionX->spinBox(), &QSpinBox::valueChanged, this,
				 &VectorContainerWidget::vectorPairClassCountActionX);

	SpinBoxAction *classCountActionY = new SpinBoxAction("Кількість класів по y");
	classCountActionY->spinBox()->setRange(0, 1000);
	graphics->addAction(classCountActionY);
	connect(classCountActionY->spinBox(), &QSpinBox::valueChanged, this,
				 &VectorContainerWidget::vectorPairClassCountActionY);

	DoubleSpinBoxAction *confidence = new DoubleSpinBoxAction("Критерій довіри");
	confidence->spinBox()->setRange(0.0, 1.0);
	confidence->spinBox()->setDecimals(5);
	confidence->spinBox()->setSingleStep(0.1);
	connect(confidence->spinBox(), &QDoubleSpinBox::valueChanged, this,
				 &VectorContainerWidget::vectorPairConfidenceAction);
	graphics->addAction(confidence);

	if (selectedVectorsList.size() == 1) {
	}

	menu->addSeparator();

	QMenu *hypotesisMenu = menu->addMenu("Перевірка гіпотез…");

	for (int p = 0; p < (int)ss::VectorPairHypothesis::Procedure::Count; p++) {
		QAction* act = hypotesisMenu->addAction(QString::fromStdString(ss::VectorPairHypothesis::procedureName[p]));
		connect(act, &QAction::triggered, this,
				 [p, this](){ this->vectorPairHypothesisAction(ss::VectorPairHypothesis::Procedure(p)); });
	}

	menu->addSeparator();

	QMenu* transformMenu = menu->addMenu("Трансформації…");
	QAction* transformAction = transformMenu->addAction("Власне перетворення");
	connect(transformAction, &QAction::triggered, this,
				 &VectorContainerWidget::vectorPairTransformAction);

	QAction* normRotationAction = transformMenu->addAction("Нормалізуючий поворот");
	connect(normRotationAction, &QAction::triggered, this,
				 &VectorContainerWidget::vectorPairNormalizingRotationAction);

	if (
		std::all_of(
			selectedVectorPairsList.begin(), selectedVectorPairsList.end(), [](auto vp) {
				return bool(vp->rotated_angle);
			}
		)
	) {
		QAction* undoNormRotationAction = transformMenu->addAction("Відмінити нормалізуючий поворот");
		connect(undoNormRotationAction, &QAction::triggered, this,
					 &VectorContainerWidget::vectorPairUndoNormalizingRotationAction);
	}


	menu->addSeparator();

	QAction *infoAction = menu->addAction("Про вектор…");
	connect(infoAction, &QAction::triggered, this,
				 &VectorContainerWidget::vectorPairInfoAction);

	QAction *conTableAction = menu->addAction("Таблиця сполучень…");
	connect(conTableAction, &QAction::triggered, this,
				 &VectorContainerWidget::vectorPairConnectionsTableInfoAction);

	QAction *regressionAction = menu->addAction("Відтворення регресії…");
	connect(regressionAction, &QAction::triggered, this,
				 &VectorContainerWidget::vectorPairRegressionAction);

	QMenu *parameters = menu->addMenu("Параметри…");
	SpinBoxAction *corelationRatio = new SpinBoxAction("Кількість інтервалів кор. відн.");
	corelationRatio->spinBox()->setRange(0, 1000);
	parameters->addAction(corelationRatio);
	connect(corelationRatio->spinBox(), &QSpinBox::valueChanged, this,
				 &VectorContainerWidget::vectorPairCorelationRatioCountAction);

	menu->addSeparator();
	QAction *breakIt = menu->addAction("Розбити на одновимірні обʼєкти");
	connect(breakIt, &QAction::triggered, this,
				 &VectorContainerWidget::vectorPairBreak);

	if (selectedVectorPairsList.size() == 1) {
		classCountActionX->spinBox()->setValue(
			selectedVectorPairsList[0]->vectorPair()->cs.countX()
		);
		classCountActionY->spinBox()->setValue(
			selectedVectorPairsList[0]->vectorPair()->cs.countY()
		);
		corelationRatio->spinBox()->setValue(
			selectedVectorPairsList[0]->vectorPair()->corRatio.count()
		);
		confidence->spinBox()->setValue(selectedVectorPairsList[0]->vectorPair()->reg.confidenceLevel());
	}

}

void VectorContainerWidget::fillVectorChainContextMenu(QMenu* menu) {
	QMenu* graphics = menu->addMenu("Графіка...");

	QAction *field3d = graphics->addAction("Тривимірне поле");
	connect(
		field3d, &QAction::triggered, this,
		&VectorContainerWidget::vectorChainField3dAction
	);

	QAction *scatterPlotMatrix = graphics->addAction("Матриця діаграм розикду");
	connect(
		scatterPlotMatrix, &QAction::triggered, this,
		&VectorContainerWidget::vectorChainScatterPlotMatrixAction
	);

	menu->addSeparator();

	QMenu* transformations = menu->addMenu("Перетворення...");
	auto performPCA = transformations->addAction("Провести перетворення МГК");
	connect(
		performPCA, &QAction::triggered, this,
		&VectorContainerWidget::vectorChainPerformPCAAction
	);
	auto normalize = transformations->addAction("Нормалізувати");
	connect(
		normalize, &QAction::triggered, this,
		&VectorContainerWidget::vectorChainNormalizeAction
	);
	auto center = transformations->addAction("Відцентрувати");
	connect(
		center, &QAction::triggered, this,
		&VectorContainerWidget::vectorChainCenterAction
	);

	menu->addSeparator();

	QAction *info = menu->addAction("Про об'єкт...");
	connect(
		info, &QAction::triggered, this,
		&VectorContainerWidget::vectorChainInfoAction
	);

	QAction *corr = menu->addAction("Коефіцієнти кореляції...");
	connect(
		corr, &QAction::triggered, this,
		&VectorContainerWidget::vectorChainCorelationCoeficientAction
	);

	menu->addSeparator();

	QAction *breakIt = menu->addAction("Розбити на одновимірні обʼєкти");
	connect(
		breakIt, &QAction::triggered, this,
		&VectorContainerWidget::vectorChainBreak
	);
}

void VectorContainerWidget::fillGenericContextMenu(QMenu* menu) {
	menu->addSeparator();

	QAction *deleteAction = menu->addAction("Видалити");
	connect(
		deleteAction, &QAction::triggered, this,
		&VectorContainerWidget::deleteAction
	);
}

void VectorContainerWidget::vectorPairDensityAction() {
	for (auto& v : selectedVectorPairsList) {
		VectorPairDensityDialog* dia = new VectorPairDensityDialog(v, this);
		connect(this, &VectorContainerWidget::redrawVector,
					dia, &VectorPairDensityDialog::sync);
		connect(this, &VectorContainerWidget::vectorPairDeleted,
					dia, &VectorPairDensityDialog::vectorDeletedHandler);
	}
}

void VectorContainerWidget::vectorPairDensity3dAction() {
	for (auto& v : selectedVectorPairsList) {
		VectorPairDensity3dDialog* dia = new VectorPairDensity3dDialog(v, this);
		connect(this, &VectorContainerWidget::redrawVector,
					dia, &VectorPairDensity3dDialog::sync);
		connect(this, &VectorContainerWidget::vectorPairDeleted,
					dia, &VectorPairDensity3dDialog::vectorDeletedHandler);
	}
}

void VectorContainerWidget::vectorPairDistributionAction() {
	for (auto& v : selectedVectorPairsList) {
		VectorPairDistributionDialog* dia = new VectorPairDistributionDialog(v, this);
		connect(this, &VectorContainerWidget::redrawVector,
					dia, &VectorPairDistributionDialog::sync);
		connect(this, &VectorContainerWidget::vectorPairDeleted,
					dia, &VectorPairDistributionDialog::vectorDeletedHandler);
	}
}

void VectorContainerWidget::vectorPairCorelationAction() {
	for (auto& v : selectedVectorPairsList) {
		VectorPairCorelationDialog* dia = new VectorPairCorelationDialog(v, this);
		connect(this, &VectorContainerWidget::redrawVector,
					dia, &VectorPairCorelationDialog::sync);
		connect(this, &VectorContainerWidget::vectorPairDeleted,
					dia, &VectorPairCorelationDialog::vectorDeletedHandler);
	}
}

void VectorContainerWidget::vectorPairClassCountActionX(int cls) {
	for (auto& v : selectedVectorPairsList) {
		v->vectorPair()->cs.setCountX(cls);
		emit redrawVector(v);
	}
}

void VectorContainerWidget::vectorPairClassCountActionY(int cls) {
	for (auto& v : selectedVectorPairsList) {
		v->vectorPair()->cs.setCountY(cls);
		emit redrawVector(v);
	}
}

void VectorContainerWidget::vectorPairCorelationRatioCountAction(int cnt) {
	for (auto& v : selectedVectorPairsList) {
		v->vectorPair()->corRatio.setCount(cnt);
		emit vectorParametersChanged(v);
	}
}

void VectorContainerWidget::vectorPairInfoAction() {
	for (auto& v : selectedVectorPairsList) {
		VectorPairInfoDialog* dia = new VectorPairInfoDialog(v, this);
		connect(this, &VectorContainerWidget::vectorPairDeleted,
					dia, &VectorPairInfoDialog::vectorDeletedHandler);
		connect(this, &VectorContainerWidget::vectorParametersChanged,
					dia, &VectorPairInfoDialog::sync);
		connect(this, &VectorContainerWidget::redrawVector,
					dia, &VectorPairInfoDialog::sync);
	}
}

void VectorContainerWidget::vectorChainInfoAction() {
	for (auto& v : selectedVectorChainsList) {
		VectorChainInfoDialog* dia = new VectorChainInfoDialog(v, this);
		connect(this, &VectorContainerWidget::vectorChainDeleted,
					dia, &VectorChainInfoDialog::vectorDeletedHandler);
		connect(this, &VectorContainerWidget::vectorParametersChanged,
					dia, &VectorChainInfoDialog::sync);
		connect(this, &VectorContainerWidget::redrawVector,
					dia, &VectorChainInfoDialog::sync);
	}
}

void VectorContainerWidget::vectorChainField3dAction() {
	for (auto& v : selectedVectorChainsList) {
		VectorChainField3dDialog* dia;
		try {
			dia = new VectorChainField3dDialog(v, this);
		} catch (std::exception& ex) {
			message(ex.what());
			delete dia;
			continue;
		}
		connect(this, &VectorContainerWidget::redrawVector,
					dia, &VectorChainField3dDialog::sync);
		connect(this, &VectorContainerWidget::vectorChainDeleted,
					dia, &VectorChainField3dDialog::vectorDeletedHandler);
	}
}

void VectorContainerWidget::vectorChainCorelationCoeficientAction() {
	for (auto& v : selectedVectorChainsList) {
		VectorChainCorelationCoeficientsDialog* dia;
		try {
			dia = new VectorChainCorelationCoeficientsDialog(v, this);
		} catch (std::exception& ex) {
			message(ex.what());
			continue;
		}
		connect(this, &VectorContainerWidget::redrawVector,
					dia, &VectorChainCorelationCoeficientsDialog::sync);
		connect(this, &VectorContainerWidget::vectorChainDeleted,
					dia, &VectorChainCorelationCoeficientsDialog::vectorDeletedHandler);
	}
}

void VectorContainerWidget::vectorChainScatterPlotMatrixAction() {
	for (auto& v : selectedVectorChainsList) {
		VectorChainScatterPlotMatrixDialog* dia;
		try {
			dia = new VectorChainScatterPlotMatrixDialog(v, this);
		} catch (std::exception& ex) {
			message(ex.what());
			continue;
		}
		connect(this, &VectorContainerWidget::redrawVector,
					dia, &VectorChainScatterPlotMatrixDialog::sync);
		connect(this, &VectorContainerWidget::vectorChainDeleted,
					dia, &VectorChainScatterPlotMatrixDialog::vectorDeletedHandler);
	}
}

void VectorContainerWidget::vectorChainPerformPCAAction() {
	for (auto& vec : selectedVectorChainsList) {
		VectorChain* vc = new VectorChain;
		vc->setName("PCA" + QString::number(vectorCount++) + "(" + vec->name() + ")");
		ss::VectorChain* svc = new ss::VectorChain(vec->chain()->begin(), vec->chain()->end());
		svc->pca.perform();
		vc->setVectorChain(svc);
		appendVectorChain(vc);
	}
}

void VectorContainerWidget::vectorChainNormalizeAction() {
	for (auto& vec : selectedVectorChainsList) {
		VectorChain* vc = new VectorChain;
		vc->setName("NORM" + QString::number(vectorCount++) + "(" + vec->name() + ")");
		ss::VectorChain* svc = new ss::VectorChain(vec->chain()->begin(), vec->chain()->end());
		vc->setVectorChain(svc);
		for (auto& v: *svc) {
			v.standardize();
		}
		appendVectorChain(vc);
	}
}

void VectorContainerWidget::vectorChainCenterAction() {
	for (auto& vec : selectedVectorChainsList) {
		VectorChain* vc = new VectorChain;
		vc->setName("CNTR" + QString::number(vectorCount++) + "(" + vec->name() + ")");
		ss::VectorChain* svc = new ss::VectorChain(vec->chain()->begin(), vec->chain()->end());
		vc->setVectorChain(svc);
		for (auto& v: *svc) {
			v.transform("x - mean()");
		}
		appendVectorChain(vc);
	}
}


void VectorContainerWidget::vectorPairConnectionsTableInfoAction() {
	for (auto& v : selectedVectorPairsList) {
		VectorPairConnectionsTableInfoDialog* dia = new VectorPairConnectionsTableInfoDialog(v, this);
		connect(this, &VectorContainerWidget::vectorPairDeleted,
					dia, &VectorPairConnectionsTableInfoDialog::vectorDeletedHandler);
		connect(this, &VectorContainerWidget::vectorParametersChanged,
					dia, &VectorPairConnectionsTableInfoDialog::sync);
	}
}

void VectorContainerWidget::vectorClassCountAction(int cls) {
	for (auto const &vec : selectedVectorsList) {
		vec->vector()->cs.setCount(cls);
		emit redrawVector(vec);
	}
}

void VectorContainerWidget::vectorConfidenceAction(double c) {
	for (auto const &vec : selectedVectorsList) {
		vec->vector()->dist.setConfidenceLevel(c);
		emit redrawVector(vec);
	}
}

void VectorContainerWidget::vectorPairConfidenceAction(double c) {
	for (auto const &vec : selectedVectorPairsList) {
		vec->vectorPair()->reg.setConfidenceLevel(c);
		emit redrawVector(vec);
	}
}

void VectorContainerWidget::vectorPairNormalizingRotationAction() {
	for (auto const &vec : selectedVectorPairsList) {
		VectorPair* vp = new VectorPair("NR" + QString::number(vectorCount++) + "(" + vec->name() + ")");
		ss::VectorPair* svp = new ss::VectorPair(*(vec->vectorPair()));
		vp->setVectorPair(svp);
		vp->rotated_angle = svp->nangle();
		svp->rotate(svp->nangle());
		appendVectorPair(vp);
	}
}

void VectorContainerWidget::vectorPairUndoNormalizingRotationAction() {
	for (auto const &vec : selectedVectorPairsList) {
		VectorPair* vp = new VectorPair("UNR" + QString::number(vectorCount++) + "(" + vec->name() + ")");
		ss::VectorPair* svp = new ss::VectorPair(*(vec->vectorPair()));
		vp->setVectorPair(svp);
		svp->rotate(-vec->vectorPair()->nangle());
		appendVectorPair(vp);
	}
}

void VectorContainerWidget::vectorDistributionAction() {
	for (auto const &v : selectedVectorsList) {
		VectorDistributionDialog* dia = new VectorDistributionDialog(v, this);
		connect(this, &VectorContainerWidget::redrawVector,
					dia, &VectorDistributionDialog::sync);
		connect(this, &VectorContainerWidget::vectorDeleted,
			dia, &VectorDistributionDialog::vectorDeletedHandler);
	}
}

void VectorContainerWidget::vectorDensityAction() {
	for (auto const &v : selectedVectorsList) {
		VectorDensityDialog* dia = new VectorDensityDialog(v, this);
		connect(this, &VectorContainerWidget::redrawVector,
					dia, &VectorDistributionDialog::sync);
		connect(this, &VectorContainerWidget::vectorDeleted,
					dia, &VectorDensityDialog::vectorDeletedHandler);
	}
}

void VectorContainerWidget::deleteAction() {
	for (auto const &vec : selectedVectorsEntryesList) {
		Vector* vector;
		VectorPair* vectorPair;
		VectorChain* vectorChain;
		if ((vector = dynamic_cast<Vector*>(vec)))
			emit vectorDeleted(vector);
		else if ((vectorPair = dynamic_cast<VectorPair*>(vec)))
			emit vectorPairDeleted(vectorPair);
		else if ((vectorChain = dynamic_cast<VectorChain*>(vec)))
			emit vectorChainDeleted(vectorChain);
		else 
			throw std::runtime_error("Deleted vector object has unknown type!");

		this->removeRow(this->indexFromItem(vec->tableItem()).row());
		delete vec;
	}
}

void VectorContainerWidget::vectorStandardizeAction() {
	for (auto const &vec : selectedVectorsList) {
		ss::Vector newVector(*vec->vector());
		newVector.standardize();
		placeVector(newVector, QString("S(%1)").arg(vec->name()));
		//  TODO: move from std::list to Vector insertion
	}
}

void VectorContainerWidget::vectorLogAction() {
	for (auto const &vec : selectedVectorsList) {
		ss::Vector newVector(*vec->vector());
		newVector.transform("log(x)");
		placeVector(newVector, QString("LN(%1)").arg(vec->name()));
	}
}

void VectorContainerWidget::vectorReverseAction() {
	for (auto const &vec : selectedVectorsList) {
		ss::Vector newVector(*vec->vector());
		newVector.transform("1/x");
		placeVector(newVector, QString("R(%1)").arg(vec->name()));
	}
}

void VectorContainerWidget::vectorRightShiftAction() {
	for (auto const &vec : selectedVectorsList) {
		ss::Vector newVector(*vec->vector());
		newVector.transform("x+abs(xmin)+1");
		placeVector(newVector, QString("RS(%1)").arg(vec->name()));
	}
}

void VectorContainerWidget::vectorTransformAction() {
	QList<Vector*> vec;

	for (auto const &v : selectedVectorsList) {
		vec.push_back(v);
	}

	VectorTransformationDialog *tfe =
		new VectorTransformationDialog(vec, this);
	connect(tfe, &VectorTransformationDialog::vectorTransformed, this,
				 &VectorContainerWidget::appendVector);
	connect(this, &VectorContainerWidget::vectorDeleted, tfe,
				 &VectorTransformationDialog::vectorDeletedHandler);
}

void VectorContainerWidget::vectorPairTransformAction() {
	QList<VectorPair*> vec;

	for (auto const &v : selectedVectorPairsList) {
		vec.push_back(v);
	}

	VectorPairTransformationDialog *tfe =
		new VectorPairTransformationDialog(vec, this);
	connect(tfe, &VectorPairTransformationDialog::vectorTransformed, this,
				 &VectorContainerWidget::appendVectorPair);
	connect(this, &VectorContainerWidget::vectorPairDeleted, tfe,
				 &VectorPairTransformationDialog::vectorDeletedHandler);
}

void VectorContainerWidget::vectorReproductionAction() {
	for (auto const &vec : selectedVectorsList) {
		VectorDistributionReproducerDialog *drd =
			new VectorDistributionReproducerDialog(vec, this);
		connect(this, &VectorContainerWidget::vectorDeleted, drd,
					&VectorDistributionReproducerDialog::vectorDeletedHandler);
		connect(drd, &VectorDistributionReproducerDialog::modelSelected,
					[=]() { emit redrawVector(vec); });
	}
}

void VectorContainerWidget::vectorTrimAction() {
	for (auto const &vec : selectedVectorsList) {
		VectorTrimmerDialog *vtd = new VectorTrimmerDialog(vec, this);
		connect(vtd, &VectorTrimmerDialog::vectorTrimmed, this,
					&VectorContainerWidget::appendVector);
		connect(this, &VectorContainerWidget::vectorDeleted, vtd,
					&VectorTrimmerDialog::vectorDeletedHandler);
	}
}

void VectorContainerWidget::vectorRemoveOutliersAction() {
	for (auto const &vec : selectedVectorsList) {
		ss::Vector newVector(*vec->vector());
		bool ok = newVector.removeOutliers();

		emit outliersRemoved(ok);

		if (!ok) // no entries removed
			return;

		placeVector(newVector, QString("RMOUT(%1)").arg(vec->name()));
	}
}

void VectorContainerWidget::vectorInfoAction() {
	for (auto const &vec : selectedVectorsList) {
		VectorInfoDialog *tfe = new VectorInfoDialog(vec, this);
		connect(this, &VectorContainerWidget::vectorDeleted, tfe,
					&VectorInfoDialog::vectorDeletedHandler);
	}
}

void VectorContainerWidget::vectorMergePairAction() {
	ss::VectorPair vp; 

	try {
		vp = ss::VectorPair(
			*selectedVectorsList[0]->vector(), 
			*selectedVectorsList[1]->vector()
		);
	} catch (std::logic_error& ex) {
		message("Вектори різного розміру. Сформувати пару не вдалося");
		return;
	}
	placeVectorPair(
		vp, 
		"VP(" + selectedVectorsList[0]->name() + "+" + selectedVectorsList[1]->name() + ")"
	);
}

void VectorContainerWidget::vectorMergeChainAction() {
	ss::VectorChain vc; 

	QList<ss::Vector*> vv;
	for (auto i: selectedVectorsList) {
		vv.push_back(i->vector());
	}

	try {
		vc = ss::VectorChain(
			vv.begin(), vv.end()
		);
	} catch (std::logic_error& ex) {
		message("Вектори різного розміру. Сформувати багатовимірний об'єкт не вдалося");
		return;
	}
	placeVectorChain(
		vc
	);
}

void VectorContainerWidget::vectorWriteAction() {
	QString names;
	for (auto const& v : selectedVectorsList) {
		names.append(QString("%1(%2),")
							 .arg(v->name())
							 .arg(v->vector()->size()));
	}
	names.chop(1);

	QString filename = QFileDialog::getSaveFileName(
		this, "Зберегти вектор",
		QDir::homePath() + "/" + names + ".txt",
		"Текстові файли (*.txt) ;; CSV файли (*.csv)");

	if (filename.length() == 0)
		return;

	ss::VectorChain set;
	for (auto const &v : selectedVectorsList)
	set.push_back(v->vector()->list());

	try {
		set.writeToFile(filename.toStdString());
	} catch (std::logic_error& ex) {
		message(ex.what());
	}
}

void VectorContainerWidget::vectorPairRegressionAction() {
	for (auto vec : selectedVectorPairsList) {
		VectorPairRegressionReproducerDialog *reg = new VectorPairRegressionReproducerDialog(vec, this);
		connect(this, &VectorContainerWidget::vectorPairDeleted, reg,
					&VectorPairRegressionReproducerDialog::vectorDeletedHandler);
		connect(reg, &VectorPairRegressionReproducerDialog::modelSelected,
					[=]() { emit redrawVector(vec); });
	}
}

void VectorContainerWidget::vectorHypothesisAction(ss::VectorHypothesis::Procedure p) {
	VectorHypothesisDialog *hmd = new VectorHypothesisDialog(
		selectedVectorsList, p, this);
	connect(this, &VectorContainerWidget::vectorDeleted, hmd,
				 &VectorHypothesisDialog::vectorDeletedHandler);
}

void VectorContainerWidget::vectorPairHypothesisAction(ss::VectorPairHypothesis::Procedure p) {
	VectorPairHypothesisDialog *hmd = new VectorPairHypothesisDialog(
		selectedVectorPairsList, p, this);
	connect(this, &VectorContainerWidget::vectorDeleted, hmd,
				 &VectorHypothesisDialog::vectorDeletedHandler);
}

void VectorContainerWidget::vectorPairBreak() {
	for (auto const& v : selectedVectorPairsList) {
		QString postfix =  QString::number(++vectorCount) + "(" + v->name() + ")";
		placeVector(
			v->vectorPair()->x, "Bx" + postfix
		);
		placeVector(
			v->vectorPair()->y, "By" + postfix
		);
	}
}

void VectorContainerWidget::vectorChainBreak() {
	for (auto const& v : selectedVectorChainsList) {
		QString postfix =  QString::number(++vectorCount) + "(" + v->name() + ")";
		std::size_t no = 1;
		for (auto& vi: *v->chain()) {
			placeVector(vi, "B" + postfix + ":" + QString::number(no++));
		}
	}
}

HorizontalHeaderItem::HorizontalHeaderItem(int type) : QTableWidgetItem(type) {
	QColor col;

	if (QGuiApplication::styleHints()->colorScheme() == Qt::ColorScheme::Dark)
		col.setRgb(65, 65, 65);
	else
		col.setRgb(219, 219, 219);

	this->setBackground(col);
}
