#include <vectorPairInfoDialog.hpp>

#include <namedWidget.hpp>
#include <sectionedWidget.hpp>

VectorPairInfoDialog::VectorPairInfoDialog(
	VectorPair* vp, 
	QWidget* p,
	Qt::WindowFlags f 
): InfoDialogBase(vp, p, f) {
	v_pair = vp;
	v_mainLayout->addWidget(i_additionalSection);

	auto tw = new NamedWidget<InfoTableWidget>;
	tw->setTitle("Точкові оцінки");
	tw->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	v_table = tw->widget();
	v_mainLayout->insertWidget(0, tw);

	auto iw = new SectionedWidget<IntervalTableWidget>;
	iw->setTitle("Інтервальні оцінки");
	v_interval = iw->widget();
	v_mainLayout->insertWidget(1, iw);

	fill();
};

QString VectorPairInfoDialog::v(double x, double y) {
	return "(" + n(x) + "," + n(y) + ")";
}

void VectorPairInfoDialog::fill() {
	ss::VectorPair& vp = *v_pair->vectorPair();
	QList<QStringList> t = {
		{
			"Коефіцієнт кореляції", "r",
			n(vp.cor()), 
			"",
			n(vp.corConfidence(i_prob, ss::Bound::Lower)),
			"",
			n(vp.corConfidence(i_prob, ss::Bound::Upper)),
		},
		{
			"Коефіцієнт кореляційного відношення", "ρ",
			n(vp.corRatio()), 
			n(vp.corRatioDeviation()),
			n(vp.corRatioConfidence(i_prob, ss::Bound::Lower)),
			"",
			n(vp.corRatioConfidence(i_prob, ss::Bound::Upper)),
		},
		{
			"Ранговий коефіцієнт кореляції Спірмена", "𝜏ₛ",
			n(vp.corSpearman()), 
			n(vp.corSpearmanDeviation()),
			n(vp.corSpearmanConfidence(i_prob, ss::Bound::Lower)),
			"",
			n(vp.corSpearmanConfidence(i_prob, ss::Bound::Upper)),
		},
		{
			"Ранговий коефіцієнт кореляції Кендалла", "𝜏ₖ",
			n(vp.corKendall()), 
			n(vp.corKendallDeviation()),
			n(vp.corKendallConfidence(i_prob, ss::Bound::Lower)),
			"",
			n(vp.corKendallConfidence(i_prob, ss::Bound::Upper)),
		},
		{
			"Дисперсійно коваріаційна матриця", ms({{"σ²ₓ", "σₓσᵧrₓᵧ"}, {"σₓσᵧrₓᵧ", "σ²ᵧ"}}),
			m(
				{
					{
						vp.x.variance(), vp.x.sd()*vp.y.sd()*vp.cor()
					},
					{
						vp.x.sd()*vp.y.sd()*vp.cor(), vp.y.variance()
					}
				}
			),
			"",
			"",
			"",
			"",
		},
		{
			"Стат. початковий момент першого порядку за x", "vₓ₁",
			n(vp.x.mean()), 
			n(vp.x.meanDeviation()),
			n(vp.x.meanConfidence(i_prob, ss::Bound::Lower)),
			"",
			n(vp.x.meanConfidence(i_prob, ss::Bound::Upper)),
		},
		{
			"Стат. початковий момент першого порядку за y", "vᵧ₁",
			n(vp.y.mean()), 
			n(vp.y.meanDeviation()),
			n(vp.y.meanConfidence(i_prob, ss::Bound::Lower)),
			"",
			n(vp.y.meanConfidence(i_prob, ss::Bound::Upper)),
		},
		{
			"Стат. центральний момент другого порядку x", "μₓ₂",
			n(vp.x.variance()),
			n(vp.x.varianceDeviation()),
			n(vp.x.varianceConfidence(i_prob, ss::Bound::Lower)),
			n(vp.x.variance(ss::Measure::Population)),
			n(vp.x.varianceConfidence(i_prob, ss::Bound::Upper)),
		 },
		{
			"Стат. центральний момент другого порядку y", "μᵧ₂",
			n(vp.y.variance()),
			n(vp.y.varianceDeviation()),
			n(vp.y.varianceConfidence(i_prob, ss::Bound::Lower)),
			n(vp.y.variance(ss::Measure::Population)),
			n(vp.y.varianceConfidence(i_prob, ss::Bound::Upper)),
		 },
		{
			"Середньоквадратичне відхилення x", "СКВₓ",
			n(vp.x.sd()),
			"",
			"", 
			n(vp.x.sd(ss::Measure::Population)),
			""
		},
		{
			"Середньоквадратичне відхилення y", "СКВᵧ",
			n(vp.y.sd()),
			"",
			"", 
			n(vp.y.sd(ss::Measure::Population)),
			""
		},
		{
			"Найменше спостереження x", "xₘᵢₙ", 
			n(vp.x.min()),
			"", 
			"", 
			"", 
			""
		},
		{
			"Найбільше спостереження x", "xₘₐₓ", 
			n(vp.x.max()),
			"", 
			"",
			"",
			""
		},
		{
			"Найменше спостереження y", "yₘᵢₙ", 
			n(vp.y.min()),
			"", 
			"", 
			"", 
			""
		},
		{
			"Найбільше спостереження y", "yₘₐₓ", 
			n(vp.y.max()),
			"", 
			"",
			"",
			""
		},
	};

	if (vp.reg.model != ss::VectorPair::Regression::Model::Unknown) {
		t.push_back({
			"Коефіцієнт детермінації", "R²", 
			n(vp.reg.determination) + "%",
			"", 
			"",
			"",
			""
		});
		t.push_back({
			"Залишкова дисперсія", "Sзал", 
			n(vp.reg.remDispersion),
			"", 
			"",
			"",
			""
		});
	}

	v_table->fill(t);

	v_interval->fill({
		{
			"r",
			"",
			[&](double a, ss::Bound b) { return vp.corConfidence(a, b); },
			n(vp.cor()),
		},
		{
			"ρ",
			n(vp.corRatioDeviation()),
			[&](double a, ss::Bound b) { return vp.corRatioConfidence(a, b); },
			n(vp.corRatio()),
		},
		{
			"𝜏",
			n(vp.corSpearmanDeviation()),
			[&](double a, ss::Bound b) { return vp.corSpearmanConfidence(a, b); },
			n(vp.corSpearman()),
		},
	});

	if (v_pair->isNormalDistribution()) {
		i_additionalText->setText("Вектор змодельвано в програмі за нормальним розподілом:\n  Параметри");
		for (std::size_t i = 0; i < ss::VectorPair::Distribution::parameterName[0].size(); i++) {
			i_additionalText->append("   " + 
			 QString::fromStdString(ss::VectorPair::Distribution::parameterName[0][i]) + 
			 " " + n(v_pair->distributionParameters()[i]));
		}
	} else if (v_pair->regressionModel() != ss::VectorPair::Regression::Model::Unknown) {
		i_additionalText->setText(
			"Вектор змодельвано в програмі:\nМодель:" + 
			QString::fromStdString(ss::VectorPair::Regression::regressionName[(int)v_pair->regressionModel()])
		);
		i_additionalText->append("Параметри:");
		for (std::size_t i = 0; i < ss::VectorPair::Regression::parameterName[(int)v_pair->regressionModel()].size(); i++) {
			i_additionalText->append("   " + 
			 QString::fromStdString(ss::VectorPair::Regression::parameterName[(int)v_pair->regressionModel()][i]) + 
			 " " + n(v_pair->regressionParameters()[i]));
		}
	} else
		i_additionalText->setText("Вектор імпортовано у програму.");
}
