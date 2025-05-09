#ifndef _VECTOR_CHAIN_PCA_INFO_DIALOG_HPP_
#define _VECTOR_CHAIN_PCA_INFO_DIALOG_HPP_

#include <infoDialogBase.hpp>

class VectorChainPCAInfoDialog: public InfoDialogBase {
public:
	VectorChainPCAInfoDialog(
		VectorChain*,
		QWidget* = nullptr,
		Qt::WindowFlags = Qt::WindowFlags()
	);

protected:
	VectorChain* v_chain = nullptr;

	QTableWidget* m_table = nullptr;

public slots:
	virtual void fill() override;
};

#endif // !_VECTOR_CHAIN_PCA_INFO_DIALOG_HPP_
