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

	return menuBar;
}

QMenuBar* Charts::createMenuBar2() {
	return new QMenuBar(this);
}

QMenuBar* Charts::createMenuBar3() {
	return new QMenuBar(this);
}

void Charts::plot2D(VectorEntry* ve) {
	densityChart->fill(ve->vector);
	distributionChart->fill(ve->vector);
}
