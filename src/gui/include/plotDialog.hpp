#ifndef _PLOT_DIALOG_HPP_
#define _PLOT_DIALOG_HPP_

#include<dialogBase.hpp>
#include<PlotBase.hpp>

class PlotDialog: public DialogBase {
	Q_OBJECT
public:
	PlotDialog(PlotBase*,
						VectorEntry*, 
						QWidget* = nullptr, 
						Qt::WindowFlags = Qt::WindowFlags());
public slots:
	void saveToPng();
	void saveToJpg();
	void saveToPdf();
	virtual void fill(VectorEntry*) override;
protected:
	PlotBase* p_plot = nullptr;
	QMenuBar* p_menuBar = nullptr;
	QMenu* p_viewMenu = nullptr;
	QMenu* p_saveMenu = nullptr;
};

#endif // !_PLOT_DIALOG_HPP_
