#ifndef _CHARTS_HPP_
#define _CHARTS_HPP_

#include "densityChart.hpp"
#include "distributionChart.hpp"

#include "gui/guiTypes.hpp"

class Charts : public QStackedWidget {
public:
	Charts(QWidget* = nullptr);

private:
	DensityChart* densityChart = nullptr;
	DistributionChart* distributionChart = nullptr;

	QVector<QMenuBar*> menuBar;
	QVector<QWidget*> tabs;
	QVector<QHBoxLayout*> chartLayout;
	QVector<QVBoxLayout*> tabLayout;

	QMenuBar* createMenuBar1();
	QMenuBar* createMenuBar2();
	QMenuBar* createMenuBar3();

public slots:
	void plot2D(VectorEntry*);

private slots:
	void saveDensityToPng();
	void saveDensityToJpg();
	void saveDensityToPdf();

	void saveDistributionToPng();
	void saveDistributionToJpg();
	void saveDistributionToPdf();
};

#endif // !_CHARTS_HPP_
