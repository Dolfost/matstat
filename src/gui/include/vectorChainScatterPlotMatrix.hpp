#ifndef _VECTOR_CHAIN_SCATTER_PLOT_MATRIX_HPP_
#define _VECTOR_CHAIN_SCATTER_PLOT_MATRIX_HPP_

#include <plot3dBase.hpp>
#include <QGridLayout>

#include <vectorDensityPlot.hpp>
#include <vectorPairCorelationPlot.hpp>

class VectorChainScatterPlotMatrix: public Plot3dBase {
public:
	VectorChainScatterPlotMatrix(ss::VectorChain*);
	virtual void fill() override;

protected:
	QGridLayout* m_lay = new QGridLayout;
	std::vector<VectorDensityPlot*> m_dist_plot;
	std::map<std::pair<std::size_t, std::size_t>, VectoPairCorelationPlot*> m_corr_plot;
	std::map<std::pair<std::size_t, std::size_t>, QLabel*> m_corr_label;
	std::map<std::pair<std::size_t, std::size_t>, ss::VectorPair> m_pairs;
};

#endif // !_VECTOR_CHAIN_SCATTER_PLOT_MATRIX_HPP_
