#ifndef _VECTOR_CHAIN_CORELATION_COEFICIESNTS_DIALOG_HPP_
#define _VECTOR_CHAIN_CORELATION_COEFICIESNTS_DIALOG_HPP_

#include<vectorChain.hpp>
#include<infoDialogBase.hpp>

#include <QDoubleSpinBox>

class VectorChainCorelationCoeficientsDialog: public InfoDialogBase {

	enum rType {
		plural,
		partial
	};

public:
	VectorChainCorelationCoeficientsDialog(
		VectorChain* data = nullptr, 
		QWidget* parent = nullptr, 
		Qt::WindowFlags f = Qt::WindowFlags()
	);

protected:
	VectorChain* v_chain = nullptr;

protected:
	rType currentType;
	QLineEdit* iEdit = nullptr;
	QLineEdit* jEdit = nullptr;
	QLineEdit* dEdit = nullptr;
	QLineEdit* cEdit = nullptr;
	QLineEdit* kEdit = nullptr;
	QTextEdit* textEdit = nullptr;
	QTextEdit* alphaEdit = nullptr;
	QDoubleSpinBox* alphaSpinBox = nullptr;

public slots:
	void fill() override;
};

#endif // _VECTOR_CHAIN_CORELATION_COEFICIESNTS_DIALOG_HPP_
