#include "vector.hpp"
#include "vector/exprtk_quantile.hpp"
#include "vector/exprtk_vector.hpp"

namespace ss {

double exprtk::NormQuantile::operator()(const double& alpha) {
	return normQuantile(alpha);
}

void Vector::setExprtkSymbolTable() {
  v_exprtkSymbolTable.add_constant("e", M_E);
  v_exprtkSymbolTable.add_constant("pi", M_PI);

  exprtkMean *eMean = new exprtkMean(this);
  v_exprtkSymbolTable.add_function("mean", *eMean);

  exprtkMed *eMed = new exprtkMed(this);
  v_exprtkSymbolTable.add_function("med", *eMed);

  exprtkMad *eMad = new exprtkMad(this);
  v_exprtkSymbolTable.add_function("mad", *eMad);

  exprtkKurtosis *eKurtosis = new exprtkKurtosis(this);
  v_exprtkSymbolTable.add_function("kurtosis", *eKurtosis);

  exprtkSkew *eSkew = new exprtkSkew(this);
  v_exprtkSymbolTable.add_function("skew", *eSkew);

  exprtkWalshAveragesMed *eWalshAveragesMed = new exprtkWalshAveragesMed(this);
  v_exprtkSymbolTable.add_function("wam", *eWalshAveragesMed);

  exprtkVariance *eVariance = new exprtkVariance(this);
  v_exprtkSymbolTable.add_function("variance", *eVariance);

  exprtkXmin *eXmin = new exprtkXmin(this);
  v_exprtkSymbolTable.add_function("xmin", *eXmin);

  exprtkXmax *eXmax = new exprtkXmax(this);
  v_exprtkSymbolTable.add_function("xmax", *eXmax);

  exprtkVariationCoef *eVariationCoef = new exprtkVariationCoef(this);
  v_exprtkSymbolTable.add_function("cv", *eVariationCoef);

  exprtkSize *eSize = new exprtkSize(this);
  v_exprtkSymbolTable.add_function("size", *eSize);

  exprtkStandartDeviation *eStandartDeviation =
      new exprtkStandartDeviation(this);
  v_exprtkSymbolTable.add_function("standartDeviation",
                                         *eStandartDeviation);

  exprtkRawMoment *eRawMoment = new exprtkRawMoment(this);
  v_exprtkSymbolTable.add_function("rawMoment", *eRawMoment);

  exprtkCentralMoment *eCentralMoment = new exprtkCentralMoment(this);
  v_exprtkSymbolTable.add_function("centralMoment", *eCentralMoment);

  exprtkTurncatedMean *eTurncatedMean = new exprtkTurncatedMean(this);
  v_exprtkSymbolTable.add_function("turncatedMean", *eTurncatedMean);

	ss::exprtk::NormQuantile *eNormQuantile = new ss::exprtk::NormQuantile;
  v_exprtkSymbolTable.add_function("normQuantile", *eNormQuantile);

	ss::exprtk::StudQuantile *eStudQuantile = new ss::exprtk::StudQuantile;
  v_exprtkSymbolTable.add_function("studQuantile", *eStudQuantile);

	ss::exprtk::PearQuantile *ePearQuantile = new ss::exprtk::PearQuantile;
  v_exprtkSymbolTable.add_function("pearQuantile", *ePearQuantile);

	ss::exprtk::FishQuantile *eFishQuantile = new ss::exprtk::FishQuantile;
  v_exprtkSymbolTable.add_function("fishQuantile", *eFishQuantile);

  exprtkBeta *eBeta = new exprtkBeta(this);
  v_exprtkSymbolTable.add_function("beta", *eBeta);

  exprtkCounterKurtosis *eCounterKurtosis = new exprtkCounterKurtosis(this);
  v_exprtkSymbolTable.add_function("counterKurtosis", *eCounterKurtosis);

  exprtkNonparametricVariationCoef *eNonparametricVariationCoef =
      new exprtkNonparametricVariationCoef(this);
  v_exprtkSymbolTable.add_function("nonparametricCv",
                                         *eNonparametricVariationCoef);

	ss::exprtk::NormalDistributionCdf *eNormalDistribtuionCdf =
      new ss::exprtk::NormalDistributionCdf();

  v_exprtkSymbolTable.add_function("normCfd", *eNormalDistribtuionCdf);

  v_exprtkSymbolTable.add_function("uRand", *new ss::exprtkUniformRandom);
}

const std::string Vector::exprtkFuncitons =
    "Аргументи:\n "
    "m — тип оцінки. 'pop' – зсунена, 'spl' – не зсунена\n"
    "Функції:\n"
    "med() — медіана\n"
    "xmin() — наймешний xᵢ\n"
    "xmax() — найбільший xᵢ\n"
    "size() — розмір вектора\n"
    "variance(m) — варіабельніть\n"
    "skew(m) — коефіцієнт асиметрії\n"
    "wam() — медіана середніх Уолша\n"
    "kurtosis(m) —  коеіцієнт ексцесу\n"
    "counterKurtosis(m) —  коеіцієнт контрексцесу\n"
    "mean() — математичне сподівання\n"
    "mad() — абсолютне відхилення медіани\n"
    "cv(m) — коефіцієнт варіації (Пірсона)\n"
    "counterCv(m) — непараметричний коефіцієнт варіації\n"
    "standartDeviation(m) — середньоквадратичне відхилення\n"
    "turncatedMean(k) — усічене середнє (k ∈ (0;0.5])\n"
    "rawMoment(n) — початковий момент n-го порядку (n ∈ R)\n"
    "centralMoment(n, m) — центральний момент n-го порядку (n ∈ R)\n"
    "beta(k) — бета–коефіцієнт\n"
    "uRand(a, b) — рівномірно розподілена випадкова величина";

}
