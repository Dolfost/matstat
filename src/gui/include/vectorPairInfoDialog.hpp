#ifndef _VECTOR_PAIR_INFO_DIALOG_HPP_
#define _VECTOR_PAIR_INFO_DIALOG_HPP_

#include <infoDialogBase.hpp>

class VectorPairInfoDialog: public InfoDialogBase {
public:
	VectorPairInfoDialog(
		VectorPair*,
		QWidget* = nullptr,
		Qt::WindowFlags = Qt::WindowFlags()
	);

protected:
	VectorPair* v_pair = nullptr;

	QString v(double, double);

public slots:
	virtual void fill() override;
};

#endif // !_VECTOR_PAIR_INFO_DIALOG_HPP_
