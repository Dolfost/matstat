#ifndef _DENSITY_DIALOG_HPP_
#define _DENSITY_DIALOG_HPP_

#include <vector.hpp>
#include <qcustomplot.h>
#include <densityChart.hpp>
#include <plotDialog.hpp>

#include <guiTypes.hpp>

class DensityDialog : public PlotDialog {
	Q_OBJECT
public:
	DensityDialog(VectorEntry*, QWidget* = nullptr, 
										Qt::WindowFlags = Qt::WindowFlags());
};

#endif // !_DENSITY_DIALOG_HPP_
