#include <vectorEntryDialogBase.hpp>

VectorEntryDialogBase::VectorEntryDialogBase(
	VectorEntry* v, 
	QWidget* parent,
	Qt::WindowFlags wflags): DialogBase(parent, wflags) {
	v_vectorEntry = v;
}

void VectorEntryDialogBase::vectorDeletedHandler(VectorEntry* vectorEntry) {
	if (v_vectorEntry == vectorEntry)
		this->close();
}
