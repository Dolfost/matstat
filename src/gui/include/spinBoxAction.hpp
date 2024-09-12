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
		pLayout->setContentsMargins(3,1,3,1);
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

#endif // !_SPIN_BOX_ACTION_HPP_

