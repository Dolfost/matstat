#ifndef _HYPOTHESIS_DIALOG_BASE_HPP_
#define _HYPOTHESIS_DIALOG_BASE_HPP_

#include <QHeaderView>
#include <setDialogBase.hpp>

#include <QList>
#include <QLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QTableWidget>
#include <QGroupBox>

#include <functional>

template<class V, class H>
class HypothesisDialogBase: public SetDialogBase {
public:
	HypothesisDialogBase(
		QList<V*> ve, 
		typename H::Procedure proc,
		QWidget* p = nullptr,
		Qt::WindowFlags f = Qt::WindowFlags()
	): SetDialogBase(QList<VectorEntry*>(ve.begin(), ve.end()), p, f) {
		for (auto& v : ve) {
			h_hypot.push_back(v->data());
		}

		QVBoxLayout* secondaryLayout = new QVBoxLayout;
		secondaryLayout->setContentsMargins(5,5,5,5);

		QGroupBox* procedureGroupBox = new QGroupBox("Процедура:");
		procedureGroupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		procedureGroupBox->setLayout(new QHBoxLayout);
		procedureGroupBox->layout()->setContentsMargins(2,2,2,2);
		procedureComboBox = new QComboBox();
		for (int i = 0; i < (int)H::Procedure::Count; i++) {
			procedureComboBox->addItem(QString::fromStdString(H::procedureName[i]));
		}
		procedureGroupBox->layout()->addWidget(procedureComboBox);

		levelSpinBox = new QDoubleSpinBox;
		levelSpinBox->setRange(0.001, 0.999);
		levelSpinBox->setDecimals(5);
		levelSpinBox->setSingleStep(0.05);
		levelSpinBox->setValue(0.95);
		QGridLayout* spinBoxLayout = new QGridLayout;
		spinBoxLayout->addWidget(new QLabel("Критичний рівень значущості:"), 0, 0);
		spinBoxLayout->addWidget(levelSpinBox, 0, 1);

		resTextEdit = new QTextEdit;
		resTextEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		resTextEdit->setReadOnly(true);

		pmTable = new QTableWidget;
		pmTable->setMaximumHeight(80);
		pmTable->setRowCount(1);
		pmTable->setColumnCount(h_probs.size());
		pmTable->setVerticalHeaderLabels({"H"});
		pmTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
		QStringList header;
		for (int i = 0; i < h_probs.size(); i++) {
			header.append(QString::number(h_probs[i]));
		}
		pmTable->setHorizontalHeaderLabels(header);

		secondaryLayout->addWidget(procedureGroupBox);
		secondaryLayout->addWidget(s_vectorsGroupBox);
		secondaryLayout->addLayout(spinBoxLayout);
		v_mainLayout->addLayout(secondaryLayout);
		v_mainLayout->addWidget(resTextEdit);
		v_mainLayout->addWidget(pmTable);

		procedureComboBox->setCurrentIndex((int)proc);

		connect(levelSpinBox, &QDoubleSpinBox::valueChanged,
					this, &HypothesisDialogBase<V, H>::fill);
		connect(procedureComboBox, &QComboBox::currentTextChanged,
					this, &HypothesisDialogBase<V, H>::fill);
	};

	void doTest(
		QString c,
		std::function<double()> criteria, 
		std::function<double(double)> quantile,
		std::function<bool(double, double)> comparator,
		std::pair<QString, QString> implies = {"Прийнято", "Відхилено"}
	) {
		double critLevel = levelSpinBox->value();
		double critValue;
		try {
			critValue = criteria();
		} catch (const char* ex) {
			resTextEdit->setText("Помилка: " + QString(ex));
			return;
		} catch (const std::exception& ex) {
			resTextEdit->setText("Помилка: " + QString(ex.what()));
			return;
		}

		QString res = QString(
			"H₀: %1\nH₁: %2\n\n"
		).arg(implies.first).arg(implies.second);

		res.append(
			QString("Умова: %1 %2 %3 = %4\n")
			.arg(critValue)
			.arg(c)
			.arg(critLevel)
			.arg(QString::number(quantile(critLevel)))
		);

		if (comparator(critValue, quantile(critLevel)))
			res.append(QString("Головна гіпотеза прийнята — %1")
							.arg(implies.first));
		else
			res.append(QString("Головна гіпотеза відхилена — %1")
							.arg(implies.second));

		resTextEdit->setText(res);

		for (int j = 0; j < h_probs.size(); j++) {
			pmTable->setItem(0, j, new QTableWidgetItem(
				comparator(critValue, quantile(h_probs[j])) ? "✓" : "×"));
			pmTable->item(0, j)->setTextAlignment(Qt::AlignCenter);
		}
	}

protected:
	H h_hypot;
	QList<double> h_probs = {
		0.01, 0.03, 0.05, 0.1, 0.15, 0.2, 0.3, 0.4, 
		0.5, 0.6, 0.7, 0.8, 0.85, 0.9, 0.95, 0.97, 0.99
	};

	
protected:
	QComboBox* procedureComboBox = nullptr;
	QTextEdit* resTextEdit = nullptr;
	QDoubleSpinBox* levelSpinBox = nullptr;
	QTableWidget* pmTable = nullptr;
};

#endif // !_HYPOTHESIS_DIALOG_BASE_HPP_
