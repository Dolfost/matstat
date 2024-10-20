#ifndef _NAMED_WIDGET_HPP_
#define _NAMED_WIDGET_HPP_

#include <QGroupBox>
#include <QVBoxLayout>

template<class W>
class NamedWidget: public QGroupBox {
public:
	NamedWidget(
		QWidget* p = nullptr,
		QString title = ""
	): QGroupBox(p) {
		setLayout(new QVBoxLayout);
		layout()->setContentsMargins(0,0,0,0);
		layout()->addWidget(n_widget);
		setTitle(title);
		setSizePolicy(
			QSizePolicy::MinimumExpanding,
			QSizePolicy::Expanding
		);
	}

	W* widget() const { return n_widget; };
protected:
	W* n_widget = new W;
};

#endif // !_NAMED_WIDGET_HPP_
