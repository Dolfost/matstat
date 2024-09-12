#ifndef _SPIN_BOX_ACTION_HPP_
#define _SPIN_BOX_ACTION_HPP_

#include<QWidgetAction>
#include<QHBoxLayout>
#include<QWidget>
#include<QLabel>
#include<QSpinBox>

class SpinBoxAction : public QWidgetAction {
public:
	SpinBoxAction (const QString& title) : 
		QWidgetAction (nullptr) {
		QWidget* pWidget = new QWidget (nullptr);
		pWidget->setContentsMargins(0,0,0,0);
		QHBoxLayout* pLayout = new QHBoxLayout();
		pLayout->setContentsMargins(6,2,6,2);
		QLabel* pLabel = new QLabel (title);
		pLayout->addWidget (pLabel);
		pSpinBox = new QSpinBox(nullptr);
		pLayout->addWidget (pSpinBox);
		pWidget->setLayout (pLayout);

		setDefaultWidget(pWidget);
	}

	QSpinBox * spinBox () {
		return pSpinBox;
	}

private:
	QSpinBox * pSpinBox;
};

class DoubleSpinBoxAction : public QWidgetAction {
public:
	DoubleSpinBoxAction (const QString& title) : 
		QWidgetAction (nullptr) {
		QWidget* pWidget = new QWidget (nullptr);
		pWidget->setContentsMargins(0,0,0,0);
		QHBoxLayout* pLayout = new QHBoxLayout();
		pLayout->setContentsMargins(6,2,6,2);
		QLabel* pLabel = new QLabel (title);
		pLayout->addWidget (pLabel);
		pSpinBox = new QDoubleSpinBox(nullptr);
		pLayout->addWidget (pSpinBox);
		pWidget->setLayout (pLayout);

		setDefaultWidget(pWidget);
	}

	QDoubleSpinBox* spinBox () {
		return pSpinBox;
	}

private:
	QDoubleSpinBox* pSpinBox;
};

#endif // !_SPIN_BOX_ACTION_HPP_

