#ifndef _PLOT_DIALOG_BASE_HPP_
#define _PLOT_DIALOG_BASE_HPP_

#include<vectorEntryDialogBase.hpp>
#include<plot2dBase.hpp>

class Plot2dDialogBase: public VectorEntryDialogBase {
	Q_OBJECT
public:
	Plot2dDialogBase(Plot2dBase*,
						VectorEntry*, 
						QWidget* = nullptr, 
						Qt::WindowFlags = Qt::WindowFlags());
public slots:
	void saveToPng();
	void saveToJpg();
	void saveToPdf();
	virtual void fill() override;
protected:
	Plot2dBase* p_plot = nullptr;
	QMenuBar* p_menuBar = nullptr;
	QMenu* p_viewMenu = nullptr;
	QMenu* p_saveMenu = nullptr;
};

#endif // !_PLOT_DIALOG_BASE_HPP_
