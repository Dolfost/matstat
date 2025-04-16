#include <vectorChainInfoDialog.hpp>

#include <namedWidget.hpp>
#include <sectionedWidget.hpp>

VectorChainInfoDialog::VectorChainInfoDialog(
	VectorChain* vp, 
	QWidget* p,
	Qt::WindowFlags f 
): InfoDialogBase(vp, p, f) {
	v_chain = vp;
	v_mainLayout->addWidget(i_additionalSection);

	auto tw = new NamedWidget<InfoTableWidget>;
	tw->setTitle("Точкові оцінки");
	tw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	v_table = tw->widget();
	v_mainLayout->insertWidget(0, tw);

	// auto iw = new SectionedWidget<IntervalTableWidget>;
	// iw->setTitle("Інтервальні оцінки");
	// v_interval = iw->widget();
	// v_mainLayout->insertWidget(1, iw);

	fill();
};

QString VectorChainInfoDialog::v(std::function<double(ss::Vector&)> f) {
	QString str = "(";
	for (auto& v: *v_chain->chain()) {
		str.append(n(f(v)) + ", ");
	}
	str.chop(2);
	str.append(")");
	return str;
}

void VectorChainInfoDialog::fill() {
	ss::VectorChain& vc = *v_chain->chain();
	QList<QStringList> t = {
		{
			"Вектор математичного сподівання", "E{ξ}",
			v([](ss::Vector& v) { return v.mean(); }),
			v([](ss::Vector& v) { return v.meanDeviation(); }),
			v([this](ss::Vector& v) { return v.meanConfidence(i_prob, ss::Bound::Lower); }),
			"",
			v([this](ss::Vector& v) { return v.meanConfidence(i_prob, ss::Bound::Upper); })
		},
		{
			"Дисперсійно-коваріаційна матриця", "DC{ξ}",
			m(vc.dc()),
			"",
			"",
			"",
			"",
		},
		{
			"Кореляційна матриця", "R{ξ}",
			m(vc.r()),
			"",
			"",
			"",
			"",
		}
	};

	v_table->fill(t);
	v_table->resizeColumnsToContents();
	v_table->resizeRowsToContents();
}
