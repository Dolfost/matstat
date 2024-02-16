#ifndef _VECTOR_CONTAINER_WIDGET_HPP_
#define _VECTOR_CONTAINER_WIDGET_HPP_

#include <QTableWidget>
#include <QtGui/qevent.h>

enum class HeaderColumns { // table headers indecies
	N,
	Min,
	Max,
	Count
};

class VectorContainerWidget : public QTableWidget {
public:
	VectorContainerWidget(QWidget* parent = nullptr);
	~VectorContainerWidget() = default;
private:
	std::vector<std::vector<double>> dataVector;
};

#endif // !_VECTOR_CONTAINER_WIDGET_HPP_
