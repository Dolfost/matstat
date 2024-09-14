#include <infoDialogBase.hpp>

InfoDialogBase::InfoDialogBase(
	VectorEntry* ve, 
	QWidget* p): DialogBase(ve, p) {
	setWindowTitle("Інформація про вектор " + v_vector->name());
	i_table = new QTableWidget;
	v_mainLayout->addWidget(i_table);
	resize(450, 200);
	show();
}

QString InfoDialogBase::n(double arg) {
	return QString::number(arg, 'f', i_precision);
}
