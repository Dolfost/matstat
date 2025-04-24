#ifndef _VECTOR_CHAIN_SCATTER_PLOT_MATRIX_DIALOG_HPP_
#define _VECTOR_CHAIN_SCATTER_PLOT_MATRIX_DIALOG_HPP_

#include<plot3dDialogBase.hpp>
#include<vectorChainScatterPlotMatrix.hpp>
#include<vectorChain.hpp>

class VectorChainScatterPlotMatrixDialog: public Plot3dDialogBase {
public:
	VectorChainScatterPlotMatrixDialog(
		VectorChain* v,
		QWidget* p = nullptr,
		Qt::WindowFlags f = Qt::WindowFlags())
	: Plot3dDialogBase(new VectorChainScatterPlotMatrix(v->chain()), v, p, f) {
		setWindowTitle("Матриця діаграм розкиду векторів" + v_vectorEntry->name());
	}
};

#endif // !_VECTOR_CHAIN_SCATTER_PLOT_MATRIX_DIALOG_HPP_
