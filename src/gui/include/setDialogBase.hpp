#ifndef _SET_DIALOG_BASE_HPP_
#define _SET_DIALOG_BASE_HPP_

#include<dialogBase.hpp>

#include "guiTypes.hpp"
#include "vector.hpp"

class SetDialogBase: public DialogBase {
	Q_OBJECT
public:
	SetDialogBase(
		QList<VectorEntry*>,
		QWidget* = nullptr,
		Qt::WindowFlags = Qt::WindowFlags()
	);

public slots:
	virtual void sync(VectorEntry* ve);
	virtual void vectorDeletedHandler(VectorEntry*);

protected:
	QList<VectorEntry*> v_vectorEntry;
};

#endif // !_SET_DIALOG_BASE_HPP_
