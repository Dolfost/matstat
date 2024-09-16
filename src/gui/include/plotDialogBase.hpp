#ifndef _PLOT_DIALOG_BASE_HPP_
#define _PLOT_DIALOG_BASE_HPP_

#include<vectorEntryDialogBase.hpp>
#include<plotBase.hpp>

class PlotDialogBase: public VectorEntryDialogBase {
	Q_OBJECT
public:
	PlotDialogBase(PlotBase*,
						VectorEntry*, 
						QWidget* = nullptr, 
						Qt::WindowFlags = Qt::WindowFlags());
public slots:
	void saveToPng();
	void saveToJpg();
	void saveToPdf();
	virtual void fill() override;
protected:
	PlotBase* p_plot = nullptr;
	QMenuBar* p_menuBar = nullptr;
	QMenu* p_viewMenu = nullptr;
	QMenu* p_saveMenu = nullptr;
};

#endif // !_PLOT_DIALOG_BASE_HPP_
