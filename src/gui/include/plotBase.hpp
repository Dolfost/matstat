#ifndef _PLOT_BASE_HPP_
#define _PLOT_BASE_HPP_

#include<qcustomplot.h>

class PlotBase: public QCustomPlot {
public:
	PlotBase(QWidget* parent = nullptr);
	void setSaveFilename(QString s) {
		p_saveFilename = s;
	}

protected:
	QCPRange xRange;
	QCPRange xRange2;
	QCPRange yRange;
	QCPRange yRange2;

	QString coordinatesLabelString = "${X}\n${Y}";

	QLabel* coordinatesLabel = nullptr;
	QTimer* coordinatesTimer = nullptr;

	QCPScatterStyle statScatter;
	QPen statScatterPen;

	void mouseMoveEvent(QMouseEvent*) override;
	QString p_saveFilename = "plot";

protected slots:
	void handleZoomX(const QCPRange & newRange);
	void handleZoomX2(const QCPRange & newRange);
	void handleZoomY(const QCPRange & newRange);
	void handleZoomY2(const QCPRange& newRange);

public slots:
	virtual void fill();
	void saveToPng();
	void saveToJpg();
	void saveToPdf();
	virtual void toggleLog(bool state) = 0;
	void zoomHome();
	void clear();
};

#endif // !_PLOT_BASE_HPP_
