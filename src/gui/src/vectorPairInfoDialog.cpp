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
			n(v_pair->vectorPair()->corRatioDeviation()),
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

	if (v_pair->isModeled()) {
		i_additionalText->setText("Вектор змодельвано в програмі:\n  Параметри");
		for (std::size_t i = 0; i < ss::VectorPair::Distribution::parameterName[0].size(); i++) {
			i_additionalText->append("   " + 
			 QString::fromStdString(ss::VectorPair::Distribution::parameterName[0][i]) + 
			 " " + n(v_pair->parameters()[i]));
		}
	} else
		i_additionalText->setText("Вектор імпортовано у програму.");
}
