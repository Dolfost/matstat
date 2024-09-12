#ifndef _DISTRIBUTION_DIALOG_HPP_
#define _DISTRIBUTION_DIALOG_HPP_

#include <vector.hpp>
#include <qcustomplot.h>
#include <distributionChart.hpp>
#include <plotDialog.hpp>

#include <guiTypes.hpp>

class DistributionDialog : public PlotDialog {
	Q_OBJECT
public:
	DistributionDialog(Vector*, QWidget* = nullptr, 
										Qt::WindowFlags = Qt::WindowFlags());
};

#endif // !_DISTRIBUTION_DIALOG_HPP_
