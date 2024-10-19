#ifndef _FUNCTION_REPRODUCER_DIALOG_BASE_
#define _FUNCTION_REPRODUCER_DIALOG_BASE_

#include <QDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QComboBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QDoubleSpinBox>
#include <QStackedWidget>

#include <vectorEntryDialogBase.hpp>
#include <infoDialogBase.hpp>
#include <namedWidget.hpp>

#include <vector/quantile.hpp>

#include "guiTypes.hpp"

class FunctionReproducerDialogBase : public VectorEntryDialogBase {
	Q_OBJECT
	public:
	FunctionReproducerDialogBase(
		VectorEntry*,
		QWidget* = nullptr,
		Qt::WindowFlags = Qt::WindowFlags()
	);

protected:
	QComboBox* modelComboBox = new QComboBox;
	QLabel* reproductName = new QLabel("model name");

	NamedWidget<InfoDialogBase::InfoTableWidget>* parameters = new NamedWidget<InfoDialogBase::InfoTableWidget>;
	NamedWidget<InfoDialogBase::InfoTableWidget>* parametersDeviation = new NamedWidget<InfoDialogBase::InfoTableWidget>;

	class ParametersTest: public QTableWidget {
	public:
		ParametersTest(QWidget* p = nullptr) {
			setColumnCount(h_probs.size() + 1);
			horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
			verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
			QStringList header;
			header.push_back("Парам.");
			for (int i = 0; i < h_probs.size(); i++) {
				header.append(QString::number(h_probs[i]));
			}
			setHorizontalHeaderLabels(header);
		}

		void fill(QList<std::pair<QString, double>> d, std::size_t v) {
			setRowCount(d.size());
			QStringList h;
			for (int i = 0; i < d.size(); i++) {
				h.push_back(d[i].first);
				setItem(i, 0, new QTableWidgetItem(
					d[i].first
				));
				for (int j = 0; j < h_probs.size(); j++) {
					setItem(i, j+1, new QTableWidgetItem(
						std::abs(d[i].second) <= ss::studQuantile(1-h_probs[j]/2, v) ? "✓" : "×"));
					item(i, j+1)->setTextAlignment(Qt::AlignCenter);
				}
			}
		}

	protected:
		QList<double> h_probs = {
			0.01, 0.03, 0.05, 0.1, 0.15, 0.2, 0.3, 0.4, 
			0.5, 0.6, 0.7, 0.8, 0.85, 0.9, 0.95, 0.97, 0.99
		};

	};

	NamedWidget<ParametersTest>* parametersTest = new NamedWidget<ParametersTest>;
	QLabel* parametersTestInfoLabel = new QLabel;
	QWidget* infoWidget = nullptr;

protected slots:
	virtual void distribute(int);
	virtual void makeTtest() = 0;

signals:
	void modelSelected(VectorEntry*);
};

#endif // !_FUNCTION_REPRODUCER_DIALOG_
