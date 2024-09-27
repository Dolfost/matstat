#include<plot3dDialogBase.hpp>

Plot3dDialogBase::Plot3dDialogBase(Plot3dBase* p,
											 VectorEntry* v,
											 QWidget* w,
											 Qt::WindowFlags f 
											 ): VectorEntryDialogBase(v, w, f) {
	// p_menuBar = new QMenuBar(this);
	// p_menuBar->setNativeMenuBar(false);
	// p_viewMenu = p_menuBar->addMenu("Вигляд");
	p_plot = p;
	p_plot->fill();
	v_mainLayout->addWidget(p_plot);

	// QAction* zoomHomeAction = p_viewMenu->addAction("Відмаштабувати");
	// connect(zoomHomeAction, &QAction::triggered,
	// 		p_plot, &Plot3dBase::zoomHome);
	//
	// QAction* clearPlotsAction = p_viewMenu->addAction("Очистити");
	// connect(clearPlotsAction, &QAction::triggered,
	// 		p_plot, &Plot3dBase::clear);
	//
	// QAction* toogleDensityLogAct = 
	// 	p_viewMenu->addAction("Логарифмічна сітка щільності");
	// toogleDensityLogAct->setCheckable(true);
	// connect(toogleDensityLogAct, &QAction::toggled,
	// 		p_plot, &Plot3dBase::toggleLog);
	//
	// p_saveMenu = p_menuBar->addMenu("Зберегти");
	// QAction* saveDensityToPngAction = p_saveMenu->addAction("Зберегти як .png");
	// connect(saveDensityToPngAction, &QAction::triggered,
	// 		p_plot, &Plot3dBase::saveToPng);
	// QAction* saveDensityToJpgAction = p_saveMenu->addAction("Зберегти як .jpg");
	// connect(saveDensityToJpgAction, &QAction::triggered,
	// 	p_plot, &Plot3dBase::saveToJpg);
	// QAction* saveDensityToPdfAction = p_saveMenu->addAction("Зберегти як .pdf");
	// connect(saveDensityToPdfAction, &QAction::triggered,
	// 		p_plot, &Plot3dBase::saveToPdf);

	// v_mainLayout->setMenuBar(p_menuBar);
}

void Plot3dDialogBase::fill() {
	p_plot->fill();
}

// void Plot3dDialogBase::saveToPng() {
// 	p_plot->saveToPng();
// }
// void Plot3dDialogBase::saveToJpg() {
// 	p_plot->saveToJpg();
// }
// void Plot3dDialogBase::saveToPdf() {
// 	p_plot->saveToPdf();
// }
