#ifndef _DISTRIBUTION_DIALOG_HPP_
#define _DISTRIBUTION_DIALOG_HPP_

#include <vector.hpp>
#include <qcustomplot.h>
#include <vectorDistributionPlot.hpp>
#include <plot2dDialogBase.hpp>

#include <guiTypes.hpp>

class VectorDistributionDialog : public Plot2dDialogBase {
	Q_OBJECT
public:
	VectorDistributionDialog(Vector*, QWidget* = nullptr, 
										Qt::WindowFlags = Qt::WindowFlags());
};

#endif // !_DISTRIBUTION_DIALOG_HPP_
