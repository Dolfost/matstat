#ifndef _CALCULATOR_HPP_
#define _CALCULATOR_HPP_

#include <QApplication>
#include <QWidget>
#include <QtWidgets/qlabel.h>

#include "gui/vectorContainerWidget.hpp"
#include "gui/graphVectorContainerWidget.hpp"
#include "gui/vectorReaderWindow.hpp"

class Calculator : public QWidget {
public:
    Calculator(QWidget* parent);

private:
	VectorContainerWidget* vectorContainerWidget = nullptr;
};

#endif // !_CALCULATOR_HPP_
