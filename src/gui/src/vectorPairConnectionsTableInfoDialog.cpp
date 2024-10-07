#include "vectorPairConnectionsTableInfoDialog.hpp"

#include <namedWidget.hpp>
#include <sectionedWidget.hpp>

VectorPairConnectionsTableInfoDialog::VectorPairConnectionsTableInfoDialog(
	VectorPair* v,
	QWidget *p, Qt::WindowFlags f) 
: InfoDialogBase(v, p, f) {
	v_vector = v;

	setWindowTitle("Таблиця сполучень вектора " + v_vector->name());

	v_con = new ConnectionsTableWiget;
	v_mainLayout->addWidget(v_con);

	auto tw = new SectionedWidget<InfoTableWidget>;
	tw->setTitle("Точкові оцінки");
	tw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	v_table = tw->widget();
	v_table->setHeaders(
		{"Назва", "Позначення", "Значення"}
	);
	v_mainLayout->addWidget(tw);

	auto iw = new SectionedWidget<IntervalTableWidget>;
	iw->setTitle("Інтервальні оцінки");
	v_interval = iw->widget();
	v_mainLayout->addWidget(iw);

	resize(200, 100);
	fill();
}

void VectorPairConnectionsTableInfoDialog::fill() {
	ss::VectorPair& v = *v_vector->vectorPair();
	v_con->fill(&v);

	QList<QStringList> t;
	if (v.conTable.is2by2()) {
		t = {
			{"Індекс Фехнера", "I", n(v.conTable.fehnerIndex())},
			{"Коефіцієнт сполучень", "Φ", n(v.conTable.connectionsPhi())},
			{"Q-коефіцієнт звʼязку Юла", "Q", n(v.conTable.copulingQ())},
			{"Y-коефіцієнт звʼязку Юла", "Y", n(v.conTable.copulingY())},
		};
	}

	t.push_back(
		{"Коефіцієнт сполучень Пірсона", "C", n(v.conTable.pearConnecetionsCoef())}
	);
	if (v.conTable.row().size() == v.conTable.col().size())
		t.push_back(
			{"Міра звʼязку Кендалла", "𝜏₆", n(v.conTable.kendallCouplingMeasure())}
		);
	else
		t.push_back(
			{"Статисика Стюарда", "𝜏ₛₜ", n(v.conTable.stuardStatistics())}
		);

	v_table->fill(t);
}

VectorPairConnectionsTableInfoDialog::ConnectionsTableWiget::ConnectionsTableWiget() {
	setEditTriggers(QAbstractItemView::NoEditTriggers);
	horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
}

void VectorPairConnectionsTableInfoDialog::ConnectionsTableWiget::fill(ss::VectorPair* v) {
	std::size_t rows = v->conTable().size(), cols = v->conTable()[0].size();
	setColumnCount(cols+1); setRowCount(rows+1);

	QStringList xh, yh;
	for (std::size_t r = 0; r < rows; r++) {
		for (std::size_t c = 0; c < cols; c++) {
			Item* tableItem = new Item(QString::number(v->conTable()[r][c]));
			setItem(r, c, tableItem);
		}
	}

	double x = v->x.min(), y = v->y.min();
	for (std::size_t c = 0; c < cols; c++) {
		Item* tableItem = new Item(QString::number(v->conTable.col()[c]));
		setItem(rows, c, tableItem);
		yh.push_back(QString::number(x++));
	}
	yh.push_back("Mᵢ");
	for (std::size_t r = 0; r < rows; r++) {
		Item* tableItem = new Item(QString::number(v->conTable.row()[r]));
		setItem(r, cols, tableItem);
		xh.push_back(QString::number(y++));
	}
	xh.push_back("Nᵢ");
	setItem(rows, cols, new Item(QString::number(v->size())));

	setHorizontalHeaderLabels(yh);
	setVerticalHeaderLabels(xh);
}
