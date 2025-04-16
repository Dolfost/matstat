#include <vectorChainCorelationCoeficientDialog.hpp>

#include <QMenuBar>
#include <QStackedWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

VectorChainCorelationCoeficientsDialog::VectorChainCorelationCoeficientsDialog(
	VectorChain* vc, 
	QWidget* parent, 
	Qt::WindowFlags f
): InfoDialogBase(vc, parent, f) {
	v_chain = vc;
	setWindowTitle("Кореляційні коефіцієнти вектора " + v_chain->name());
	QMenuBar *menuBar = new QMenuBar(this);
	QMenu *fileMenu = menuBar->addMenu("Коефіцієнти");

	QAction *plural = new QAction("Множинний");
	QAction *partial = new QAction("Частковий");

	fileMenu->addAction(plural);
	fileMenu->addAction(partial);

	QStackedWidget* stackedWidget = new QStackedWidget;
	QWidget* pluralWidget = new QWidget;
	QHBoxLayout* pluralLayout = new QHBoxLayout(pluralWidget);
	QLabel *pluralLabel = new QLabel("r̂xₖ, k =");
	QFont font;
	font.setPointSize(24);
	pluralLabel->setFont(font);
	kEdit = new QLineEdit;
	pluralLayout->addWidget(pluralLabel);
	pluralLayout->addWidget(kEdit);

	QWidget* partialWidget = new QWidget;
	QVBoxLayout* v_partialLayout = new QVBoxLayout(partialWidget);
	QHBoxLayout* partialLayout = new QHBoxLayout;
	QLabel *partialLabel = new QLabel("<html><body>r̂<sub>i, j &middot; cd</sub></body></html>");
	partialLabel->setStyleSheet("font-size: 24px;");
	partialLabel->setFont(font);

	QHBoxLayout* iLayout = new QHBoxLayout;
	QLabel *iLabel = new QLabel("i = ");
	iEdit = new QLineEdit;
	iLayout->addWidget(iLabel);
	iLayout->addWidget(iEdit);

	QHBoxLayout* jLayout = new QHBoxLayout;
	QLabel *jLabel = new QLabel("j = ");
	jEdit = new QLineEdit;
	jLayout->addWidget(jLabel);
	jLayout->addWidget(jEdit);

	QHBoxLayout* dLayout = new QHBoxLayout;
	QLabel *dLabel = new QLabel("d = ");
	dEdit = new QLineEdit;
	dLayout->addWidget(dLabel);
	dLayout->addWidget(dEdit);

	QHBoxLayout* cLayout = new QHBoxLayout;
	QLabel *cLabel = new QLabel("c = ");
	cEdit = new QLineEdit;
	cLayout->addWidget(cLabel);
	cLayout->addWidget(cEdit);

	partialLayout->addWidget(partialLabel);
	partialLayout->addSpacing(50);
	partialLayout->addLayout(iLayout);
	partialLayout->addLayout(jLayout);
	partialLayout->addLayout(dLayout);

	v_partialLayout->addLayout(partialLayout);
	v_partialLayout->addLayout(cLayout);

	connect(partial, &QAction::triggered, [this, stackedWidget]() {
		stackedWidget->setCurrentIndex(0);
		currentType = rType::partial;
	});

	connect(plural , &QAction::triggered, [this, stackedWidget]() {
		stackedWidget->setCurrentIndex(1);
		currentType = rType::plural;
	});

	currentType = rType::partial;
	stackedWidget->addWidget(partialWidget);
	stackedWidget->addWidget(pluralWidget);

	QPushButton* button = new QPushButton("Порахувати");
	connect(
		button, &QPushButton::pressed, 
		this, &VectorChainCorelationCoeficientsDialog::fill
	);
	textEdit = new QTextEdit;
	textEdit->setReadOnly(true);

	QHBoxLayout* alphaLayout = new QHBoxLayout;
	alphaLayout->addWidget(new QLabel(" α = "));
	alphaSpinBox = new QDoubleSpinBox;
	alphaSpinBox->setRange(0.001, 0.999);
	alphaSpinBox->setValue(0.95);
	alphaSpinBox->setSingleStep(0.01);
	connect(
		alphaSpinBox, &QDoubleSpinBox::valueChanged, 
		this, &VectorChainCorelationCoeficientsDialog::fill
	);
	alphaLayout->addWidget(alphaSpinBox);
	alphaEdit = new QTextEdit;
	alphaEdit->setReadOnly(true);

	v_mainLayout->addWidget(stackedWidget);
	v_mainLayout->addWidget(button);
	v_mainLayout->addWidget(textEdit);
	v_mainLayout->addLayout(alphaLayout);
	v_mainLayout->addWidget(alphaEdit);
}

inline std::pair<double, double> rPartial_confidence(double r, double quantile, int N, int w){
	double v_1 = std::log((1+r)/(1-r))/2.0 - quantile/(N - w - 3.0);
	double v_2 = std::log((1+r)/(1-r))/2.0 + quantile/(N - w - 3.0);
	return std::make_pair((std::exp(2*v_1) - 1)/(std::exp(2*v_1) + 1), (std::exp(2*v_2) - 1)/(std::exp(2*v_2) + 1));
}

void VectorChainCorelationCoeficientsDialog::fill() {
	QString str, confidance = "";
	double r;
	double t;
	double quantile;
	double alpha = alphaSpinBox->value();
	double left_bound;
	double right_bound;

	switch (currentType) {
		case rType::partial: {

			std::size_t i = iEdit->text().toInt();
			std::size_t j = jEdit->text().toInt();
			std::size_t d = dEdit->text().toInt();

			QString input = cEdit->text();
			QStringList stringNumbers = input.split(" ,");

			std::vector<std::size_t> c;
			for (const QString& str : stringNumbers) {
				c.push_back(str.toInt());
			}

			r = v_chain->chain()->partial_corelation({i, j, c, d});

			int N = v_chain->chain()->size();
			t = std::abs(r*std::sqrt(N - c.size() - 2)/std::sqrt(1.0 - r));
			quantile = ss::studQuantile(alpha, N - c.size() - 2);
			std::pair<double, double> bounds = rPartial_confidence(r, quantile, N, c.size());
			left_bound = bounds.first;
			right_bound = bounds.second;

			str = QString::number(t);
			str += t < quantile ? " < " : " > ";
			str += QString::number(quantile) + "\t";
			str += t < quantile ? "" : "не ";
			str += "значущий";

			confidance += "\n Довірчий інтервал: \n";
			confidance += QString::number(left_bound) + " < " + QString::number(r) + " < " + QString::number(right_bound);
		}
			break;
		case rType::plural: {
			int k = kEdit->text().toInt();


			int n = v_chain->chain()->at(0).size();
			int N = v_chain->chain()->size();

			if (k >= N) {
				err("k не в області допустимих значень");
				return;
			}

			r = v_chain->chain()->plural_corelation(k);
			t = ((N - n - 1.0)/n)*(r*r/(1-r*r));
			quantile = ss::fishQuantile(alpha, n, std::abs(n-N-1));

			str = QString::number(t);
			str += t < quantile ? " < " : " > ";
			str += QString::number(quantile) + " -> ";
			str += t < quantile ? "не " : "";
			str += "значущий";
		}
			break;
		default:
			break;
	}

	str += confidance;

	textEdit->setText(QString::number(r));
	alphaEdit->setText(str);
}
