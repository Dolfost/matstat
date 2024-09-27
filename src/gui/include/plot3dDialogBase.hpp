#ifndef _PLOT_3D_DIALOG_BASE_HPP_
#define _PLOT_3D_DIALOG_BASE_HPP_

#include<QMenuBar>

#include<vectorEntryDialogBase.hpp>
#include<plot3dBase.hpp>

class Plot3dDialogBase: public VectorEntryDialogBase {
	Q_OBJECT
public:
	Plot3dDialogBase(Plot3dBase*,
						VectorEntry*, 
						QWidget* = nullptr, 
						Qt::WindowFlags = Qt::WindowFlags());
// public slots:
// 	void saveToPng();
// 	void saveToJpg();
// 	void saveToPdf();
	virtual void fill() override;
protected:
	Plot3dBase* p_plot = nullptr;
	// QMenuBar* p_menuBar = nullptr;
	// QMenu* p_viewMenu = nullptr;
	// QMenu* p_saveMenu = nullptr;
};

#endif // !_PLOT_3D_DIALOG_BASE_HPP_
