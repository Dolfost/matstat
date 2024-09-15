#ifndef _VECTOR_DIALOG_HPP_
#define _VECTOR_DIALOG_HPP_

#include<Qt>
#include<QDialog>
#include<QVBoxLayout>

#include "guiTypes.hpp"
#include "vector.hpp"

class DialogBase: public QDialog {
	Q_OBJECT
public:
	DialogBase(
		VectorEntry*,
		QWidget* = nullptr,
		Qt::WindowFlags = Qt::WindowFlags()
	);

public slots:
	virtual void sync(VectorEntry* ve) {
		if (ve == v_vectorEntry)
			fill();
	}
	virtual void fill() = 0;
	virtual void vectorDeletedHandler(VectorEntry*);

protected:
	VectorEntry* v_vectorEntry = nullptr;
	QVBoxLayout* v_mainLayout = nullptr;
};

#endif // !_VECTOR_DIALOG_HPP_
