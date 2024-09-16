#include<dialogBase.hpp>

DialogBase::DialogBase(
	QWidget* parent,
	Qt::WindowFlags wflags): QDialog(parent, wflags) {
	setAttribute(Qt::WA_DeleteOnClose, true);
	v_mainLayout = new QVBoxLayout();
	setLayout(v_mainLayout);
	v_mainLayout->setContentsMargins(0, 0, 0, 0);
	show();
	resize(500, 400);
}
