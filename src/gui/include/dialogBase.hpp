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

	virtual void fill(VectorEntry*) = 0;
public slots:
	virtual void vectorDeletedHandler(VectorEntry*);

protected:
	VectorEntry* v_vector = nullptr;
	QVBoxLayout* v_mainLayout = nullptr;
};

#endif // !_VECTOR_DIALOG_HPP_
