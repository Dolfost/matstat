#include "charts.hpp"
#include <QWidget>
#include <QtWidgets/qlabel.h>

Charts::Charts(QWidget* parent) : QStackedWidget(parent) {
	tabs = QVector<QWidget*>(Tab::Count);
	tabLayout = QVector<QVBoxLayout*>(Tab::Count);
	chartLayout = QVector<QHBoxLayout*>(Tab::Count);

	for (short tab = Tab::TwoD; tab < Tab::Count; tab++) {
		tabs[tab] = new QWidget;
		tabLayout[tab] = new QVBoxLayout;
		tabs[tab]->setLayout(tabLayout[tab]);
		tabLayout[tab]->setSpacing(0);
		tabLayout[tab]->setContentsMargins(0,0,0,0);
		chartLayout[tab] = new QHBoxLayout;
	}

	densityChart = new DensityChart(this);
	distributionChart = new DistributionChart(this);

	chartLayout[Tab::TwoD]->addWidget(densityChart);
	chartLayout[Tab::TwoD]->addWidget(distributionChart);

	chartLayout[Tab::ThreeD]->addWidget(new QLabel("TAB 2"));
	chartLayout[Tab::FourD]->addWidget(new QLabel("TAB 3"));
	
	menuBar.push_back(createMenuBar1());
	menuBar.push_back(createMenuBar2());
	menuBar.push_back(createMenuBar3());

	for (short tab = Tab::TwoD; tab < Tab::Count; tab++) {
		tabLayout[tab]->setMenuBar(menuBar[tab]);
		tabLayout[tab]->addLayout(chartLayout[tab]);
		this->addWidget(tabs[tab]);
	}
}

QMenuBar* Charts::createMenuBar1() {
	QMenuBar* menuBar = new QMenuBar(this);
	menuBar->setNativeMenuBar(false);


	QMenu *viewMenu = menuBar->addMenu("Вигляд");

	QAction* toogleDensityLogAct = 
		viewMenu->addAction("Логарифмічна сітка щільності");
	toogleDensityLogAct->setCheckable(true);
	connect(toogleDensityLogAct, &QAction::toggled,
			densityChart, &DensityChart::toggleLog);

	QAction* toogleDistributionLogAct = 
		viewMenu->addAction("Логарифмічна сітка розподілу");
	toogleDistributionLogAct->setCheckable(true);
	connect(toogleDistributionLogAct, &QAction::toggled,
			distributionChart, &DistributionChart::toggleLog);

	QAction* zoomHomeAction = viewMenu->addAction("Відмаштабувати графіки");
	connect(zoomHomeAction, &QAction::triggered,
			densityChart, &DensityChart::zoomHome);
	connect(zoomHomeAction, &QAction::triggered,
			distributionChart, &DistributionChart::zoomHome);

	QAction* clearPlotsAction = viewMenu->addAction("Очистити графіки");
	connect(clearPlotsAction, &QAction::triggered,
			densityChart, &DensityChart::clear);
	connect(clearPlotsAction, &QAction::triggered,
			distributionChart, &DistributionChart::clear);


	QMenu* saveMenu = menuBar->addMenu("Зберегти");
	QMenu* saveDensityMenu = saveMenu->addMenu("Графік функції щільності…");
	QAction* saveDensityToPngAction = saveDensityMenu->addAction("Зберегти як .png");
	connect(saveDensityToPngAction, &QAction::triggered,
			this, &Charts::saveDensityToPng);
	QAction* saveDensityToJpgAction = saveDensityMenu->addAction("Зберегти як .jpg");
	connect(saveDensityToJpgAction, &QAction::triggered,
			this, &Charts::saveDensityToJpg);
	QAction* saveDensityToPdfAction = saveDensityMenu->addAction("Зберегти як .pdf");
	connect(saveDensityToPdfAction, &QAction::triggered,
			this, &Charts::saveDensityToPdf);

	QMenu* saveDistributionMenu = saveMenu->addMenu("Графік функції розподілу…");
	QAction* saveDistributionToPngAction = saveDistributionMenu->addAction("Зберегти як .png");
	connect(saveDistributionToPngAction, &QAction::triggered,
			this, &Charts::saveDistributionToPng);
	QAction* saveDistributionToJpgAction = saveDistributionMenu->addAction("Зберегти як .jpg");
	connect(saveDistributionToJpgAction, &QAction::triggered,
			this, &Charts::saveDistributionToJpg);
	QAction* saveDistributionToPdfAction = saveDistributionMenu->addAction("Зберегти як .pdf");
	connect(saveDistributionToPdfAction, &QAction::triggered,
			this, &Charts::saveDistributionToPdf);

	return menuBar;
}

QMenuBar* Charts::createMenuBar2() {
	return new QMenuBar(this);
}

QMenuBar* Charts::createMenuBar3() {
	return new QMenuBar(this);
}

void Charts::plot2D(Vector* ve) {
	densityChart->fill(ve->vector());
	distributionChart->fill(ve->vector());
}

void Charts::saveDensityToPng() {
  auto al = densityChart->antialiasedElements();
  densityChart->setAntialiasedElements(QCP::aeAll);
  QString filename = QFileDialog::getSaveFileName(
      this, "Зберегти графік функції щільності",
      QDir::homePath() + "/density.png",
      "Файли фото (*.png)");

  if (filename.length())
	  densityChart->savePng(filename, 0, 0, 4, 100);

  densityChart->setAntialiasedElements(al);
}

void Charts::saveDensityToJpg() {
  auto al = densityChart->antialiasedElements();
  densityChart->setAntialiasedElements(QCP::aeAll);
  QString filename = QFileDialog::getSaveFileName(
      this, "Зберегти графік функції щільності",
      QDir::homePath() + "/density.jpg",
      "Файли фото (*.jpg)");

  if (filename.length())
	  densityChart->saveJpg(filename, 0, 0, 4, 100);
  densityChart->setAntialiasedElements(al);
}

void Charts::saveDensityToPdf() {
  auto al = densityChart->antialiasedElements();
  densityChart->setAntialiasedElements(QCP::aeAll);
  QString filename = QFileDialog::getSaveFileName(
      this, "Зберегти графік функції щільності",
      QDir::homePath() + "/density.pdf",
      "Файли документів (*.pdf)");

  if (filename.length())
	  densityChart->savePdf(filename);
  densityChart->setAntialiasedElements(al);
}

void Charts::saveDistributionToPng() {
  auto al = distributionChart->antialiasedElements();
  distributionChart->setAntialiasedElements(QCP::aeAll);
  QString filename = QFileDialog::getSaveFileName(
      this, "Зберегти графік функції розподілу",
      QDir::homePath() + "/distribution.png",
      "Файли фото (*.png)");

  if (filename.length())
	  distributionChart->savePng(filename, 0, 0, 4, 100);
  distributionChart->setAntialiasedElements(al);
}

void Charts::saveDistributionToJpg() {
  auto al = distributionChart->antialiasedElements();
  distributionChart->setAntialiasedElements(QCP::aeAll);
  QString filename = QFileDialog::getSaveFileName(
      this, "Зберегти графік функції розподілу",
      QDir::homePath() + "/distribution.jpg",
      "Файли фото (*.jpg)");

  if (filename.length())
	  distributionChart->saveJpg(filename, 0, 0, 4, 100);
  distributionChart->setAntialiasedElements(al);
}

void Charts::saveDistributionToPdf() {
  auto al = distributionChart->antialiasedElements();
  distributionChart->setAntialiasedElements(QCP::aeAll);
  QString filename = QFileDialog::getSaveFileName(
      this, "Зберегти графік функції розподілу",
      QDir::homePath() + "/distribution.pdf",
      "Файли документів (*.pdf)");

  if (filename.length())
	  distributionChart->savePdf(filename);
  distributionChart->setAntialiasedElements(al);
}
