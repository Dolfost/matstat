#ifndef _VECTOR_CHAIN_FIELD_PLOT_3D_DIALOG_HPP_
#define _VECTOR_CHAIN_FIELD_PLOT_3D_DIALOG_HPP_

#include<plot3dDialogBase.hpp>
#include<vectorChainFieldPlot3d.hpp>
#include<vectorChain.hpp>

class VectorChainField3dDialog: public Plot3dDialogBase {
public:
	VectorChainField3dDialog(
		VectorChain* v,
		QWidget* p = nullptr,
		Qt::WindowFlags f = Qt::WindowFlags())
	: Plot3dDialogBase(new VectorChainFieldPlot3d(v->chain()), v, p, f) {
		setWindowTitle("Поле трохвимірного вектора" + v_vectorEntry->name());
	}
};

#endif // !_VECTOR_PAIR_CHAIN_FIELD_3D_DIALOG_HPP_
