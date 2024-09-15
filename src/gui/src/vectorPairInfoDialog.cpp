#include <vectorPairInfoDialog.hpp>

VectorPairInfoDialog::VectorPairInfoDialog(
	VectorPair* vp, 
	QWidget* p,
	Qt::WindowFlags f 
): InfoDialogBase(vp, p, f) {
	v_pair = vp;
	v_mainLayout->addWidget(i_additionalSection);

	fill();
};

void VectorPairInfoDialog::fill() {
	fillTable({
		{
			"Коефіцієнт кореляції", "r",
			n(v_pair->vectorPair()->cor()), 
			"—",
			"—",
			"—",
			"—",
		},
	});

	i_additionalText->setText("Вектор імпортовано у програму.");
}
