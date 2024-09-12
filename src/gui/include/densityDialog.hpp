#ifndef _DENSITY_DIALOG_HPP_
#define _DENSITY_DIALOG_HPP_

#include <vector.hpp>
#include <qcustomplot.h>
#include <vectorDialog.hpp>
#include <densityChart.hpp>

#include <guiTypes.hpp>

class DensityDialog : public VectorDialog {
	Q_OBJECT
public:
	DensityDialog(VectorEntry*, QWidget* = nullptr, 
										Qt::WindowFlags = Qt::WindowFlags());
public slots:
	virtual void fill() override;
private:
	DensityChart* d_chart = nullptr;
};

#endif // !_DENSITY_DIALOG_HPP_
