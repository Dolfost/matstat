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
			n(v_pair->vectorPair()->corConfidence(i_prob, ss::Bound::Lower)),
			"—",
			n(v_pair->vectorPair()->corConfidence(i_prob, ss::Bound::Upper)),
		},
	});
	
	fillConfidence({
		{
			"r",
			"",
			[=](double a, ss::Bound b) { return v_pair->vectorPair()->corConfidence(a, b); },
			n(v_pair->vectorPair()->cor()),
		},
	});

	i_additionalText->setText("Вектор імпортовано у програму.");
}
