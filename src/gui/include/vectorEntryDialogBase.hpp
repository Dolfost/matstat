#ifndef _VECTOR_ENTRY_DIALOG_BASE_
#define _VECTOR_ENTRY_DIALOG_BASE_

#include<dialogBase.hpp>

#include "guiTypes.hpp"
#include "vector.hpp"

class VectorEntryDialogBase: public DialogBase {
	Q_OBJECT
public:
	VectorEntryDialogBase(
		VectorEntry*,
		QWidget* = nullptr,
		Qt::WindowFlags = Qt::WindowFlags()
	);

public slots:
	virtual void sync(VectorEntry* ve) {
		if (ve == v_vectorEntry)
			fill();
	}
	virtual void vectorDeletedHandler(VectorEntry*);

protected:
	VectorEntry* v_vectorEntry = nullptr;
};

#endif // !_VECTOR_ENTRY_DIALOG_BASE_
