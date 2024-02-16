#include <QTabWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QtCore/qnamespace.h>
#include <QtWidgets/qtextedit.h>
#include <vector>

#include "calculator.hpp"
#include "gui/vectorContainerWidget.hpp"
#include "gui/vectorReaderWindow.hpp"

Calculator::Calculator(QWidget *parent) : QWidget(parent) {
	QVBoxLayout* mainLayout = new QVBoxLayout(this);
	mainLayout->setContentsMargins(0,0,0,0);

	// graphs 
	QHBoxLayout* graphsLayout = new QHBoxLayout();
	graphsLayout->setContentsMargins(0,0,0,0);

	// vector containers tab widget
	QTabWidget* vectorContainersTabWidget = new QTabWidget();
	vectorContainersTabWidget->setDocumentMode(true);
	vectorContainersTabWidget->setMovable(true);
	QWidget* objectsTab = new QWidget();
	QWidget* dataReportTab = new QWidget();
	QHBoxLayout* objectsTabLayout = new QHBoxLayout();
	objectsTabLayout->setContentsMargins(0,0,0,0);
	QVBoxLayout* dataReportTabLayout = new QVBoxLayout();
	dataReportTabLayout->setContentsMargins(0,0,0,0);
	objectsTab->setLayout(objectsTabLayout);
	dataReportTab->setLayout(dataReportTabLayout);
	vectorContainersTabWidget->addTab(objectsTab, "Objects");
	vectorContainersTabWidget->addTab(dataReportTab, "Data report");

	// vector containers tab widget : objects tab
	vectorContainerWidget = new VectorContainerWidget(); //  NOTE: VectorContainerWidget
	objectsTabLayout->addWidget(vectorContainerWidget);
	connect(vectorContainerWidget, &VectorContainerWidget::cellDoubleClicked, [=](){
			VectorReaderWindow vectorReaderWindow;
			vectorReaderWindow.readData("/Users/vladyslav/Lib/NAU/Mathematical_statistics/Labs/Lab_1/data.txt");
			vectorReaderWindow.exec();

			std::vector<VectorDataSeries> newVectors = vectorReaderWindow.vectors();
			});


	mainLayout->addLayout(graphsLayout);
	mainLayout->addWidget(vectorContainersTabWidget);
}
