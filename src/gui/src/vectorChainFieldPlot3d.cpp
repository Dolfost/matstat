#include <vectorChainFieldPlot3d.hpp>

#include <QVBoxLayout>
#include <QScatter3DSeries>
#include <Q3DScatter>
#include <QScatterDataProxy>

VectorChainFieldPlot3d::VectorChainFieldPlot3d(
	ss::VectorChain* v
): Plot3dBase(v) {
	auto series = new QScatter3DSeries;
	s_series = series;
	auto scatter = new Q3DScatter;
	s_graph = scatter;
	layout()->addWidget(QWidget::createWindowContainer(s_graph));
	scatter->addSeries(series);
	scatter->axisX()->setTitleVisible(true);
	scatter->axisY()->setTitleVisible(true);
	scatter->axisZ()->setTitleVisible(true);
	scatter->axisX()->setTitle(QStringLiteral("X"));
	scatter->axisY()->setTitle(QStringLiteral("Z"));
	scatter->axisZ()->setTitle(QStringLiteral("Y"));

	scatter->axisX()->setSegmentCount(
		15
	);
	scatter->axisZ()->setSegmentCount(
		15
	);
	scatter->axisY()->setSegmentCount(
		15
	);
	s_graph->setAspectRatio(1.0);
	s_graph->setHorizontalAspectRatio(1.0);
	s_graph->setShadowQuality(QAbstract3DGraph::ShadowQuality::ShadowQualityNone);
	static_cast<QScatter3DSeries*>(s_series)->setItemSize(0.04);
}

void VectorChainFieldPlot3d::fill() {
	auto dataArray = new QScatterDataArray ;

	ss::VectorChain& vc = *s_vectorChain;

	if (vc.size() != 3) {
		throw std::logic_error("Дані не 3-вимірні!");
		close();
	}

	const std::size_t n = vc[0].size();
	dataArray->reserve(n);
	for (int i = 0 ; i < n ; i++) {
		QScatterDataItem item;
		item.setX(vc[0].list()[i]);
		item.setY(vc[1].list()[i]);
		item.setZ(vc[2].list()[i]);
		dataArray->push_back(item);
	}

	static_cast<QScatter3DSeries*>(s_series)->dataProxy()->resetArray(dataArray);
}
