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

QString VectorPairInfoDialog::v(double x, double y) {
	return "(" + n(x) + "," + n(y) + ")";
}

void VectorPairInfoDialog::fill() {
	fillTable({
		{
			"Вектор стат. центральних моменів другого порядку", "(μₓ,μᵧ)",
			v(v_pair->vectorPair()->x.variance(), v_pair->vectorPair()->y.variance()), 
			v(v_pair->vectorPair()->x.varianceDeviation(), v_pair->vectorPair()->y.varianceDeviation()), 
			v(v_pair->vectorPair()->x.varianceConfidence(i_prob, ss::Bound::Lower), v_pair->vectorPair()->y.varianceConfidence(i_prob, ss::Bound::Lower)), 
			v(v_pair->vectorPair()->x.variance(ss::Measure::Population), v_pair->vectorPair()->y.variance(ss::Measure::Population)), 
			v(v_pair->vectorPair()->x.varianceConfidence(i_prob, ss::Bound::Upper), v_pair->vectorPair()->y.varianceConfidence(i_prob, ss::Bound::Upper)), 
		},
		{
			"Вектор стат. початкових моменів першого порядку", "(vₓ,vᵧ)",
			v(v_pair->vectorPair()->x.mean(), v_pair->vectorPair()->y.variance()), 
			v(v_pair->vectorPair()->x.meanDeviation(), v_pair->vectorPair()->y.varianceDeviation()), 
			v(v_pair->vectorPair()->x.meanConfidence(i_prob, ss::Bound::Lower), v_pair->vectorPair()->y.varianceConfidence(i_prob, ss::Bound::Lower)), 
			"",
			v(v_pair->vectorPair()->x.meanConfidence(i_prob, ss::Bound::Upper), v_pair->vectorPair()->y.varianceConfidence(i_prob, ss::Bound::Upper)), 
		},
		{
			"Коефіцієнт кореляції", "r",
			n(v_pair->vectorPair()->cor()), 
			"",
			n(v_pair->vectorPair()->corConfidence(i_prob, ss::Bound::Lower)),
			"",
			n(v_pair->vectorPair()->corConfidence(i_prob, ss::Bound::Upper)),
		},
		{
			"Коефіцієнт кореляційного відношення", "ρ",
			n(v_pair->vectorPair()->corRatio()), 
			n(v_pair->vectorPair()->corRatioDeviation()),
			n(v_pair->vectorPair()->corRatioConfidence(i_prob, ss::Bound::Lower)),
			"",
			n(v_pair->vectorPair()->corRatioConfidence(i_prob, ss::Bound::Upper)),
		},
		{
			"Ранговий коефіцієнт кореляції Спірмена", "𝜏ₛ",
			n(v_pair->vectorPair()->corSpearman()), 
			n(v_pair->vectorPair()->corSpearmanDeviation()),
			n(v_pair->vectorPair()->corSpearmanConfidence(i_prob, ss::Bound::Lower)),
			"",
			n(v_pair->vectorPair()->corSpearmanConfidence(i_prob, ss::Bound::Upper)),
		},
		{
			"Дисперсійно коваріаційна матриця", ms({{"σ²ₓ", "σₓσᵧrₓᵧ"}, {"σₓσᵧrₓᵧ", "σ²ᵧ"}}),
			m(
				{
					{
						v_pair->vectorPair()->x.variance(), v_pair->vectorPair()->x.sd()*v_pair->vectorPair()->y.sd()*v_pair->vectorPair()->cor()
					},
					{
						v_pair->vectorPair()->x.sd()*v_pair->vectorPair()->y.sd()*v_pair->vectorPair()->cor(), v_pair->vectorPair()->y.variance()
					}
				}
			),
			"",
			"",
			"",
			"",
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
		{
			"𝜏",
			n(v_pair->vectorPair()->corSpearmanDeviation()),
			[=](double a, ss::Bound b) { return v_pair->vectorPair()->corSpearmanConfidence(a, b); },
			n(v_pair->vectorPair()->corSpearman()),
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
