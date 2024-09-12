#ifndef _CHART_VIEW_BASE_HPP_
#define _CHART_VIEW_BASE_HPP_

#include "qcustomplot.h"
#include "vector.hpp"

#include "axisTickerExp.hpp"

class PlotBase : public QCustomPlot {
	Q_OBJECT
public:
	PlotBase(QWidget* parent = nullptr);

	ss::Vector* vector();

	void enableMean();
	void plotMean();

	void enableStandartDeviation();
	void plotStandartDeviation();

	void enableMed();
	void plotMed();

	void enableWalshMed();
	void plotWalshMed();

	ss::Vector* dv = nullptr;

	QSharedPointer<QCPAxisTickerFixed> xFixedTicker;
	QSharedPointer<QCPAxisTicker> xTicker;
	QSharedPointer<QCPAxisTicker> yTicker;
	QSharedPointer<AxisTickerExp> yLogTicker;
	QCPRange xRange;
	QCPRange xRange2;
	QCPRange yRange;
	QCPRange yRange2;

	QCPScatterStyle scatterStyle;
	QPen scatterPen;
	QCPGraph* mean = nullptr;
	QCPGraph* standatrDeviation = nullptr;
	QCPGraph* med = nullptr;
	QCPGraph* walshMed = nullptr;

	QString coordinatesLabelString = "${X}\n${Y}";
	virtual void fill(ss::Vector*);
	void setSaveFilename(QString s) {
		p_saveFilename = s;
	}
private:
	QLabel* coordinatesLabel = nullptr;
	QTimer* coordinatesTimer = nullptr;

private slots:
	void handleZoomX(const QCPRange & newRange);
	void handleZoomX2(const QCPRange & newRange);
	void handleZoomY(const QCPRange & newRange);
	void handleZoomY2(const QCPRange& newRange);

public slots:
	void saveToPng();
	void saveToJpg();
	void saveToPdf();
	void toggleLog(bool state);
	void zoomHome();
	void clear();


protected:
	void mouseMoveEvent(QMouseEvent*) override;
	QString p_saveFilename = "plot";
};

#endif // !_CHART_BASE_HPP_
