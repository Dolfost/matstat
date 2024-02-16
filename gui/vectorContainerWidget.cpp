#include "vectorContainerWidget.hpp"

VectorContainerWidget::VectorContainerWidget(QWidget* parent) : QTableWidget(parent) {
	this->setRowCount(1);
	this->setColumnCount(20);
	this->setSelectionBehavior(QAbstractItemView::SelectRows);

	QStringList labels = {"X", "N", "Min", "Max"};
	this->setHorizontalHeaderLabels(labels);
}

