#ifndef _VECTOR_PAIR_DENSITY_PLOT_3D_DIALOG_HPP_
#define _VECTOR_PAIR_DENSITY_PLOT_3D_DIALOG_HPP_

#include<plot3dDialogBase.hpp>
#include<vectorPairDensityPlot3d.hpp>
#include<vectorPair.hpp>

class VectorPairDensity3dDialog: public Plot3dDialogBase {
public:
	VectorPairDensity3dDialog(
		VectorPair* v,
		QWidget* p = nullptr,
		Qt::WindowFlags f = Qt::WindowFlags())
	: Plot3dDialogBase(new VectorPairDensityPlot3d(v->vectorPair()), v, p, f) {
		// p_plot->setSaveFilename("2d-density");
		setWindowTitle("Відтворена щільність двовимірного вектора " + v_vectorEntry->name());
	}
};

#endif // !_VECTOR_PAIR_DENSITY_PLOT_3D_DIALOG_HPP_
