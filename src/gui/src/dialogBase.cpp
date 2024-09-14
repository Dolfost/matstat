#include <dialogBase.hpp>

DialogBase::DialogBase(
	VectorEntry* v, 
	QWidget* parent,
	Qt::WindowFlags wflags): QDialog(parent, wflags) {
	v_vector = v;
	setAttribute(Qt::WA_DeleteOnClose, true);
	v_mainLayout = new QVBoxLayout();
	setLayout(v_mainLayout);
	v_mainLayout->setContentsMargins(0, 0, 0, 0);
	show();
	resize(500, 400);
}

void DialogBase::vectorDeletedHandler(VectorEntry* vectorEntry) {
	if (v_vector == vectorEntry)
		this->close();
}
