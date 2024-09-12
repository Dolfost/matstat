#ifndef _DISTRIBUTION_DIALOG_HPP_
#define _DISTRIBUTION_DIALOG_HPP_

#include <vector.hpp>
#include <qcustomplot.h>
#include <vectorDialog.hpp>
#include <distributionChart.hpp>

#include <guiTypes.hpp>

class DistributionDialog : public VectorDialog {
	Q_OBJECT
public:
	DistributionDialog(VectorEntry*, QWidget* = nullptr, 
										Qt::WindowFlags = Qt::WindowFlags());
public slots:
	virtual void fill() override;
private:
	DistributionChart* d_chart = nullptr;
};

#endif // !_DISTRIBUTION_DIALOG_HPP_
