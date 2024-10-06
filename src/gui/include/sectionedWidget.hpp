#ifndef _SECTIONED_WIDGET_HPP_
#define _SECTIONED_WIDGET_HPP_

#include <QGroupBox>
#include <QVBoxLayout>

#include <Section.h>

template<class W>
class SectionedWidget: public ui::Section {
public:
	SectionedWidget(
		QWidget* p = nullptr,
		QString title = ""
	): ui::Section(title, 100, p) {
		QVBoxLayout* l = new QVBoxLayout;
		l->setContentsMargins(0,0,0,0);
		l->addWidget(n_widget);
		setSizePolicy(
			QSizePolicy::MinimumExpanding,
			QSizePolicy::Fixed
		);
		setContentLayout(*l);
	}

	W* widget() const { return n_widget; };
protected:
	W* n_widget = new W;
};

#endif // !_SECTIONED_WIDGET_HPP_
