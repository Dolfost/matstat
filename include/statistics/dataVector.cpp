#include "dataVector.hpp"
#include <cmath>

DataVector::DataVector(const std::list<double>& input) {
	setVector(input);
}

DataVector::DataVector(DataVector& dv) {
	setVector(dv.vector());
}

void DataVector::setVector(const std::list<double>& input) {
	dataVector = input;
	dataVector.sort();
	clearStatistics();
}

const std::list<double>& DataVector::vector() {
	return dataVector;
}


////// Statistics ////// 
double DataVector::min() {
	if (!stat.min.second)
		computeMinMaxSize();
	return stat.min.first;
}

double DataVector::max() {
	if (!stat.max.second)
		computeMinMaxSize();
	return stat.max.first;
}

size_t DataVector::size() {
	if (!stat.size.second)
		computeMinMaxSize();
	return stat.size.first;
}

double DataVector::mean() {
	return rawMoment(1);
}

double DataVector::variance() {
	return centralMoment(2);
}

double DataVector::standardDeviation() {
	if (!stat.standardDeviation.second)
		computeStandardDeviation();
	return stat.standardDeviation.first;
}

double DataVector::rawMoment(double degree) {
	if (stat.rawMoment.count(degree) != 1)
		computeRawMoment(degree);

	return stat.rawMoment[degree];
}

double DataVector::centralMoment(double degree) {
	if (stat.centralMoment.count(degree) != 1)
		computeCentralMoment(degree);

	return stat.centralMoment[degree];
}

double DataVector::turncatedMean(double degree) {
	size_t k = degree*size() - (size()%2 ? 0 : 1);
	if (stat.turncatedMean.count(k) != 1)
		computeTurncatedMean(k);

	return stat.turncatedMean[k];
}

double DataVector::med() {
	return turncatedMean(0.5);
}

double DataVector::mad() {
	if (!stat.mad.second)
		computeMad();

	return stat.mad.first;
}

double DataVector::skew() {
	if (!stat.skew.second)
		computeSkew();

	return stat.skew.first;
}

double DataVector::kurtosis() {
	if (!stat.kurtosis.second)
		computeKurtosis();

	return stat.kurtosis.first;
}

std::list<double> DataVector::walshAverages() {
	if (!stat.walshAverages.second)
		computeWalshAverages();

	return stat.walshAverages.first;
}

double DataVector::walshAveragesMed() {
	if (!stat.walshAveragesMed.second)
		computeWalshAveragesMed();

	return stat.walshAveragesMed.first;
}

double DataVector::variationCoef() {
	if (!stat.variationCoef.second)
		computeVariationCoef();

	return stat.variationCoef.first;
}

double DataVector::normQuantile(double alpha) {
	if (stat.normQuantile.count(alpha) != 1)
		computeNormQuantile(alpha);

	return stat.normQuantile[alpha];
}

double DataVector::pearQuantile(double alpha, int v) {
	if (stat.pearQuantile.count({alpha, v}) != 1)
		computePearQuantile(alpha, v);

	return stat.pearQuantile[{alpha, v}];
}

double DataVector::studQuantile(double alpha, int v) {
	if (stat.studQuantile.count({alpha, v}) != 1)
		computeStudQuantile(alpha, v);

	return stat.studQuantile[{alpha, v}];
}

double DataVector::fishQuantile(double alpha, int v1, int v2) {
	if (stat.fishQuantile.count({alpha, v1, v2}) != 1)
		computeFishQuantile(alpha, v1, v2);

	return stat.fishQuantile[{alpha, v1, v2}];
}

// statistic computers //
void DataVector::computeMinMaxSize() {
	stat.min.first = dataVector.front();
	stat.max.first = dataVector.back();
	stat.size.first = dataVector.size();

	stat.min.second = true;
	stat.max.second = true;
	stat.size.second = true;
}

void DataVector::computeRawMoment(double degree) {
	double* moment = &stat.rawMoment[degree];

	for (auto const& i : dataVector) {
		*moment += std::pow(i, degree);
	}

	*moment /= size();
}

void DataVector::computeCentralMoment(double degree) {
	double* moment = &stat.centralMoment[degree];
	double meanValue = mean();

	for (auto const& i : dataVector) {
		*moment += std::pow(i - meanValue, degree);
	}

	*moment /= (size() - 1);
}

void DataVector::computeStandardDeviation() {
	stat.standardDeviation.first = std::sqrt(centralMoment(2));
	stat.standardDeviation.second = true;
}

void DataVector::computeTurncatedMean(size_t k) {
	double* turncatedMean = &stat.turncatedMean[k];

	auto front = dataVector.begin();
	auto back = dataVector.end();
	std::advance(front, k);
	std::advance(back, -k);

	while (front != back) {
		*turncatedMean += *front;
		front++;
	}

	*turncatedMean /= (size() - 2*k);
}

void DataVector::computeMad() {
	std::list<double> madVector;
	double medValue = med();

	for (auto const& i : dataVector) {
		madVector.push_back(i - medValue);
	}

	DataVector madDataVector(madVector);

	stat.mad.first = madDataVector.med();
	stat.mad.second = true;
}

void DataVector::computeSkew() {
	double N = size();

	stat.skew.first = (std::sqrt(N*(N-1))*centralMoment(3)) / 
		(rawMoment(3)*(N-2));
	stat.skew.second = true;
}

void DataVector::computeKurtosis() {
	double N = size();

	stat.kurtosis.first = ((std::pow(N, 2)-1)/((N-2)*(N-3))) * 
		((centralMoment(4)/rawMoment(4) - 3) + 6/(N+1));
	stat.kurtosis.second = true;
}

void DataVector::computeWalshAverages() {
	for (auto const& i : dataVector) {
		for (auto const& j : dataVector) {
			stat.walshAverages.first.push_back((i+j)*0.5);
		}
	}

	stat.walshAverages.second = true;
}

void DataVector::computeWalshAveragesMed() {
	DataVector walshAveragesVector(walshAverages());
	stat.walshAveragesMed.first = walshAveragesVector.med();

	stat.walshAveragesMed.second = true;
}

void DataVector::computeVariationCoef() {
	if (mean() == 0)
		stat.variationCoef.first = DBL_MAX;
	else
		stat.variationCoef.first = variance()/mean();

	stat.variationCoef.second = true;
}

void DataVector::clearStatistics() {
	stat.rawMoment.clear();
	stat.centralMoment.clear();
	stat.turncatedMean.clear();
	stat.walshAverages.first.clear();

	stat.normQuantile.clear();
	stat.studQuantile.clear();
	stat.pearQuantile.clear();
	stat.fishQuantile.clear();

	stat.standardDeviation.second = false;
	stat.mad.second = false;
	stat.skew.second = false;
	stat.kurtosis.second = false;
	stat.variationCoef.second = false;
	stat.walshAverages.second = false;
	stat.walshAveragesMed.second = false;

	stat.min.second = false;
	stat.max.second = false;
	stat.size.second = false;
}

QString DataVector::report() {
	return QString(
			"Мат. сподівння (v₁) %1\n"
			"Варіабельність (u₂) %2\n"
			"Медіана (MED) %3\n"
			"Усічене середнє (α=0.25) %4\n"
			"Медіана середніх Уолша (MED*) %5\n"
			"CКВ (σ) %6\n"
			"Абсолютне відхилення медіани (MAD) %7\n"
			"Коеф. асиметрії (A) %8\n"
			"Ексцесс %9\n"
			"Коефіцієнт варіації (Пірсона) (W) %10\n"
			).arg(mean())
		.arg(variance())
		.arg(med())
		.arg(turncatedMean(0.25))
		.arg(walshAveragesMed())
		.arg(standardDeviation())
		.arg(mad())
		.arg(skew())
		.arg(kurtosis())
		.arg(variationCoef());
}

void DataVector::computeNormQuantile(double alpha) {
	double* quantile = &stat.normQuantile[alpha];

	const double 
		c0 = 2.515517,
		c1 = 0.802853,
		c2 = 0.010328,
		d1 = 1.432788,
		d2 = 0.1892659,
		d3 = 0.001308,
		t = sqrt(log(1/(alpha*alpha))),
		ea = 4.5e-4;

	*quantile = t - (c0 + c1*t + c2*t*t) /
		(1 + d1*t+d2*t*t + d3*t*t*t) + ea;
}

void DataVector::computeStudQuantile(double alpha, int v) {
	double *quantile = &stat.studQuantile[{alpha, v}];

	const double
		nq = normQuantile(alpha),
		nq2 = nq*nq,
		nq3 = nq2*nq,
		nq5 = nq3*nq2,
		nq7 = nq5*nq2,
		nq9 = nq7*nq2,
		g1 = (nq3+ nq)/4,
		g2 = (5*nq5 + 16*nq3 + 3*nq)/96,
		g3 = (3*nq7 + 19*nq5 + 17*nq3 - 15*nq)/384,
		g4 = (79*nq9 + 779*nq7 + 1482*nq5 - 1920*nq3 - 945*nq)/92160;

	*quantile = nq + g1/v + g2/pow(v, 2) + g3/pow(v, 3) + g4/pow(v, 4);
}

void DataVector::computePearQuantile(double alpha, int v) {
	double* quantile = &stat.pearQuantile[{alpha, v}];

	*quantile = v*pow(1 - 2.0/(9*v) + normQuantile(alpha)*sqrt(2.0/(9*v)), 3);
}

void DataVector::computeFishQuantile(double alpha, int v1, int v2) {
	double* quantile = &stat.fishQuantile[{alpha, v1, v2}];

	const double
		sigma = 1.0/v1 + 1.0/v2,
		delta = 1.0/v1 - 1.0/v2,
		sigmaSqrtBy2 = sqrt(sigma/2),
		nq = normQuantile(alpha),
		nq2 = nq*nq,
		nq3 = nq2*nq,
		nq4 = nq3*nq4,
		nq5 = nq4*nq,
		z = nq*sigmaSqrtBy2 - delta*(nq*nq+2)/6 + 
			sigmaSqrtBy2*((sigma*(nq2 + 3*nq)/24 + 
			(pow(delta, 2)*(nq3 +11*nq))/(72*sigma))) -
			(delta*sigma*(nq4+9*nq2+8))/120 +
			(pow(delta, 3)*(3*nq4 + 7*nq2 - 16))/(3240*sigma) +
			sigmaSqrtBy2*(pow(sigma, 2)*(nq5 + 20*nq3 +15*nq)/1920 + 
			pow(delta, 4)*(nq5 + 44*nq3 + 183*nq)/2880 + 
			pow(delta, 4)*(9*nq5 - 284*nq3 - 1513*nq)/(155520 * pow(sigma, 2)));

	*quantile = exp(2*z);
}

// Vector operations
void DataVector::standardize() {
	double meanValue = mean();
	double standardDeviationValue = standardDeviation();

	for (auto& x : dataVector) {
		x = (x - meanValue)/standardDeviationValue;
	}

	clearStatistics();
}

bool DataVector::removeOutliers() {
	double a, b,
		   t1 = 2+0.2*log10(0.04*size()),
		   t2 = sqrt(19*sqrt(kurtosis()+2)+1);

	if (skew() < -0.2) {
		a = mean() - t2*variance();
		b = mean() + t1*variance();
	} else if (skew() <= 0.2) { // skew in [-0.2;0.2]
		a = mean() - t1*variance();
		b = mean() + t1*variance();
	} else {
		a = mean() - t1*variance();
		b = mean() + t2*variance();
	}

	std::list<double> newVector;

	std::list<double>::iterator startIt = dataVector.begin();
	std::list<double>::iterator endIt = dataVector.end();

	while (startIt != dataVector.end()) {
		if (*startIt > a)
			break;
		startIt++;
	}

	while (endIt != dataVector.begin()) {
		if (*endIt < b)
			break;
		endIt--;
	}

	if (endIt == dataVector.end() and startIt == dataVector.begin())
		return false;

	dataVector.assign(startIt, endIt);

	clearStatistics();
	return true;
}

QString DataVector::transform(QString expression) {
	QString msg;

	exprtk::expression<double> expr;
	exprtk::parser<double> parser;
	setTransformationSymbolTable();

	double x;
	transformationSymbolTable.remove_variable("x");
	transformationSymbolTable.add_variable("x", x);

	expr.register_symbol_table(transformationSymbolTable);

	if (!parser.compile(expression.toStdString(), expr)) {
		msg.append(
				"Error computing xₙ: " + QString(parser.error().c_str()) +
				"\nExpression: '" + QString(expression.toStdString().c_str()) + "'\n");
		return msg;
	}

	for (auto& vectorValue : dataVector) {
		x = vectorValue;
		vectorValue = expr.value();
	}

	clearStatistics();

	return msg;
}

void DataVector::setTransformationSymbolTable() {
	if (transformationSymbolTableReady)
		return;

	transformationSymbolTable.add_constant("e", M_E);
	transformationSymbolTable.add_constant("pi", M_PI);

	exprtkMean* eMean = new exprtkMean(this);
	transformationSymbolTable
		.add_function("mean", *eMean);

	exprtkMed* eMed = new exprtkMed(this);
	transformationSymbolTable
	.add_function("med", *eMed);

	exprtkMad* eMad = new exprtkMad(this);
	transformationSymbolTable
	.add_function("mad", *eMad);

	exprtkKurtosis* eKurtosis = new exprtkKurtosis(this);
	transformationSymbolTable
	.add_function("kurtosis", *eKurtosis);

	exprtkSkew* eSkew = new exprtkSkew(this);
	transformationSymbolTable
	.add_function("skew", *eSkew);

	exprtkWalshAveragesMed* eWalshAveragesMed = new exprtkWalshAveragesMed(this);
	transformationSymbolTable
	.add_function("wam", *eWalshAveragesMed);

	exprtkVariance* eVariance = new exprtkVariance(this);
	transformationSymbolTable
	.add_function("variance", *eVariance);

	exprtkXmin* eXmin = new exprtkXmin(this);
	transformationSymbolTable
	.add_function("xmin", *eXmin);

	exprtkXmax* eXmax = new exprtkXmax(this);
	transformationSymbolTable
	.add_function("xmax", *eXmax);

	exprtkVariationCoef* eVariationCoef = new exprtkVariationCoef(this);
	transformationSymbolTable
	.add_function("cv", *eVariationCoef);

	exprtkSize* eSize = new exprtkSize(this);
	transformationSymbolTable
	.add_function("size", *eSize);

	exprtkStandartDeviation* eStandartDeviation = new exprtkStandartDeviation(this);
	transformationSymbolTable
	.add_function("standartDeviation", *eStandartDeviation);

	exprtkRawMoment* eRawMoment = new exprtkRawMoment(this);
	transformationSymbolTable
	.add_function("rawMoment", *eRawMoment);

	exprtkCentralMoment* eCentralMoment = new exprtkCentralMoment(this);
	transformationSymbolTable
	.add_function("centralMoment", *eCentralMoment);

	exprtkTurncatedMean* eTurncatedMean = new exprtkTurncatedMean(this);
	transformationSymbolTable
	.add_function("turncatedMean", *eTurncatedMean);

	exprtkNormQuantile* eNormQuantile = new exprtkNormQuantile(this);
	transformationSymbolTable
	.add_function("normQuantile", *eNormQuantile);

	exprtkStudQuantile* eStudQuantile = new exprtkStudQuantile(this);
	transformationSymbolTable
	.add_function("studQuantile", *eStudQuantile);

	exprtkPearQuantile* ePearQuantile = new exprtkPearQuantile(this);
	transformationSymbolTable
	.add_function("pearQuantile", *ePearQuantile);

	exprtkFishQuantile* eFishQuantile = new exprtkFishQuantile(this);
	transformationSymbolTable
	.add_function("fishQuantile", *eFishQuantile);

	transformationSymbolTableReady = true;
}

const QString DataVector::exprtkFuncitons = 
		"med() — медіана\n"
		"xmin() — наймешний xᵢ\n"
		"xmax() — найбільший xᵢ\n"
		"size() — розмір вектора\n"
		"variance() — варіабельніть\n"
		"skew() — коефіцієнт асиметрії\n"
		"wam() — медіана середніх Уолша\n"
		"kurtosis() —  коеіцієнт ексцесу\n"
		"mean() — математичне сподівання\n"
		"mad() — абсолютне відхилення медіани\n"
		"cv() — коефіцієнт варіації (Пірсона)\n"
		"standartDeviation() — середньоквадратичне відхилення\n"
		"turncatedMean(k) — усічене середнє (k ∈ (0;0.5])\n"
		"rawMoment(n) — початковий момент n-го порядку (n ∈ R)\n"
		"centralMoment(n) — центральний момент n-го порядку (n ∈ R)\n"
		"normQuantile(a) — квантиль нормального розподілу\n"
		"studQuantile(a,v) — квантиль розподілу Стьюдента\n"
		"pearQuantile(a,v) — квантиль розподілу Пірсона\n"
		"fishQuantile(a,v1,v2) — квантиль розподілу Фішера\n";
