#ifndef _DENSITY_DIALOG_HPP_
#define _DENSITY_DIALOG_HPP_

#include <vector.hpp>
#include <qcustomplot.h>
#include <vectorDensityPlot.hpp>
#include <plot2dDialogBase.hpp>

#include <guiTypes.hpp>

class VectorDensityDialog : public Plot2dDialogBase {
	Q_OBJECT
public:
	VectorDensityDialog(Vector*, QWidget* = nullptr, 
										Qt::WindowFlags = Qt::WindowFlags());
};

#endif // !_DENSITY_DIALOG_HPP_
