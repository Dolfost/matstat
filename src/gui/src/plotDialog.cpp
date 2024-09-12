#include<plotDialog.hpp>

PlotDialog::PlotDialog(PlotBase* p,
											 VectorEntry* v,
											 QWidget* w,
											 Qt::WindowFlags f 
											 ): VectorDialog(v, w, f) {
	p_menuBar = new QMenuBar(this);
	p_menuBar->setNativeMenuBar(false);
	p_viewMenu = p_menuBar->addMenu("Вигляд");
	p_plot = p;
	p_plot->fill(v->vector);
	v_mainLayout->addWidget(p_plot);

	QAction* zoomHomeAction = p_viewMenu->addAction("Відмаштабувати");
	connect(zoomHomeAction, &QAction::triggered,
			p_plot, &PlotBase::zoomHome);

	QAction* clearPlotsAction = p_viewMenu->addAction("Очистити");
	connect(clearPlotsAction, &QAction::triggered,
			p_plot, &PlotBase::clear);

	p_saveMenu = p_menuBar->addMenu("Зберегти");
	QAction* saveDensityToPngAction = p_saveMenu->addAction("Зберегти як .png");
	connect(saveDensityToPngAction, &QAction::triggered,
			p_plot, &PlotBase::saveToPng);
	QAction* saveDensityToJpgAction = p_saveMenu->addAction("Зберегти як .jpg");
	connect(saveDensityToJpgAction, &QAction::triggered,
		p_plot, &PlotBase::saveToJpg);
	QAction* saveDensityToPdfAction = p_saveMenu->addAction("Зберегти як .pdf");
	connect(saveDensityToPdfAction, &QAction::triggered,
			p_plot, &PlotBase::saveToPdf);

	v_mainLayout->setMenuBar(p_menuBar);
}

void PlotDialog::fill() {
	p_plot->fill(v_vector->vector);
}

void PlotDialog::saveToPng() {
	p_plot->saveToPng();
}
void PlotDialog::saveToJpg() {
	p_plot->saveToJpg();
}
void PlotDialog::saveToPdf() {
	p_plot->saveToPdf();
}
