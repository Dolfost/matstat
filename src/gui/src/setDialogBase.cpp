#include <setDialogBase.hpp>

SetDialogBase::SetDialogBase(
	QList<VectorEntry*> v, 
	QWidget* p,
	Qt::WindowFlags f): DialogBase(p, f) {
	v_vectorEntry = v;
}

void SetDialogBase::vectorDeletedHandler(VectorEntry* ve) {
	if (v_vectorEntry.removeAll(ve)) {
		if (!v_vectorEntry.size()) {
			this->close();
			return;
		}
		fill();
	}
}

void SetDialogBase::sync(VectorEntry* ve) {
	if (std::find(
		v_vectorEntry.begin(), 
		v_vectorEntry.end(), 
		ve) != v_vectorEntry.end()
	) fill();
}
