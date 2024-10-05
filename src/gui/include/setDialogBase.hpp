#ifndef _SET_DIALOG_BASE_HPP_
#define _SET_DIALOG_BASE_HPP_

#include <QLineEdit>
#include <QGroupBox>

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
	
protected:
	QLineEdit* s_vectorsLineEdit = nullptr;
	QGroupBox* s_vectorsGroupBox = nullptr;

public slots:
	virtual void sync(VectorEntry* ve);
	virtual void vectorDeletedHandler(VectorEntry*);
	virtual void fill() override;
	void makeVectorNames();

protected:
	QList<VectorEntry*> v_vectorEntry;
};

#endif // !_SET_DIALOG_BASE_HPP_
