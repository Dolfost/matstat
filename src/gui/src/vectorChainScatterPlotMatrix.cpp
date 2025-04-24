#include <vectorChainScatterPlotMatrix.hpp>

#include <QVBoxLayout>
#include <QScatter3DSeries>
#include <Q3DScatter>
#include <QScatterDataProxy>

VectorChainScatterPlotMatrix::VectorChainScatterPlotMatrix(
	ss::VectorChain* v
): Plot3dBase(v) {
	std::size_t N = s_vectorChain->size();

	m_dist_plot.resize(N);

	for (std::size_t i = 0; i < N; i++) {
		m_dist_plot[i] = new VectorDensityPlot(&s_vectorChain->at(i));
		m_dist_plot[i]->legend->setVisible(false);
		m_lay->addWidget(m_dist_plot[i], i, i);
		for (std::size_t j = 0; j < N; j++) {
			if (i > j) {
				m_pairs[{i, j}] = ss::VectorPair(s_vectorChain->at(i), s_vectorChain->at(j)); 
				m_corr_plot[{i, j}] = new VectoPairCorelationPlot(&m_pairs[{i, j}]);
				m_corr_plot[{i, j}]->legend->setVisible(false);
				m_lay->addWidget(m_corr_plot[{i, j}], i, j);
			} else if (i < j) {
				m_corr_label[{i, j}] = new QLabel("ABABAGALAMAGA");
				m_corr_label[{i, j}]->setAlignment(Qt::AlignCenter);
				m_lay->addWidget(m_corr_label[{i, j}], i, j);
			}
		}
	}

	delete layout();
	setLayout(m_lay);
}

void VectorChainScatterPlotMatrix::fill() {
	std::size_t N = s_vectorChain->size();
	for (std::size_t i = 0; i < N; i++) {
		m_dist_plot[i]->fill();
		for (std::size_t j = 0; j < N; j++) {
			if (i > j) {
				m_corr_plot[{i, j}]->fill();
			} else if (i < j) {
				m_corr_label[{i, j}]->setText(QString::number(m_pairs[{j, i}].cor()));
			}
		}
	}
}
