#ifndef _VECTOR_CHAIN_INFO_DIALOG_HPP_
#define _VECTOR_CHAIN_INFO_DIALOG_HPP_

#include <infoDialogBase.hpp>

class VectorChainInfoDialog: public InfoDialogBase {
public:
	VectorChainInfoDialog(
		VectorChain*,
		QWidget* = nullptr,
		Qt::WindowFlags = Qt::WindowFlags()
	);

protected:
	VectorChain* v_chain = nullptr;

	QString v(std::function<double(ss::Vector&)> f);
	InfoTableWidget* v_table = nullptr;
	// IntervalTableWidget* v_interval = nullptr;

public slots:
	virtual void fill() override;
};

#endif // !_VECTOR_CHAIN_INFO_DIALOG_HPP_
