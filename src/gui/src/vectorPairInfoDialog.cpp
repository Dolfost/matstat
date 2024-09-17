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
		{
			"Коефіцієнт кореляційного відношення", "ρ",
			n(v_pair->vectorPair()->corRatio()), 
			"—",
			n(v_pair->vectorPair()->corRatioConfidence(i_prob, ss::Bound::Lower)),
			"—",
			n(v_pair->vectorPair()->corRatioConfidence(i_prob, ss::Bound::Upper)),
		},
	});
	
	fillConfidence({
		{
			"r",
			"",
			[=](double a, ss::Bound b) { return v_pair->vectorPair()->corConfidence(a, b); },
			n(v_pair->vectorPair()->cor()),
		},
		{
			"ρ",
			n(v_pair->vectorPair()->corRatioDeviation()),
			[=](double a, ss::Bound b) { return v_pair->vectorPair()->corRatioConfidence(a, b); },
			n(v_pair->vectorPair()->corRatio()),
		},
	});

	i_additionalText->setText("Вектор імпортовано у програму.");
}
