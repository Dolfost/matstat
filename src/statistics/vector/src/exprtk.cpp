#include "vector.hpp"
#include "vector/exprtk_quantile.hpp"

namespace ss {

double exprtk::NormQuantile::operator()(const double& alpha) {
	return normQuantile(alpha);
}

void Vector::setExprtkSymbolTable() {
  v_exprtkSymbolTable.add_constant("e", M_E);
  v_exprtkSymbolTable.add_constant("pi", M_PI);

  exprtk_mean *eMean = new exprtk_mean(this);
  v_exprtkSymbolTable.add_function("mean", *eMean);

  exprtk_med *eMed = new exprtk_med(this);
  v_exprtkSymbolTable.add_function("med", *eMed);

  exprtk_mad *eMad = new exprtk_mad(this);
  v_exprtkSymbolTable.add_function("mad", *eMad);

  exprtk_kurtosis *eKurtosis = new exprtk_kurtosis(this);
  v_exprtkSymbolTable.add_function("kurtosis", *eKurtosis);

  exprtk_skew *eSkew = new exprtk_skew(this);
  v_exprtkSymbolTable.add_function("skew", *eSkew);

  exprtk_variance *eVariance = new exprtk_variance(this);
  v_exprtkSymbolTable.add_function("variance", *eVariance);

  exprtk_min *eXmin = new exprtk_min(this);
  v_exprtkSymbolTable.add_function("xmin", *eXmin);

  exprtk_max *eXmax = new exprtk_max(this);
  v_exprtkSymbolTable.add_function("xmax", *eXmax);

  exprtk_cv *eVariationCoef = new exprtk_cv(this);
  v_exprtkSymbolTable.add_function("cv", *eVariationCoef);

  exprtk_size *eSize = new exprtk_size(this);
  v_exprtkSymbolTable.add_function("size", *eSize);

  exprtk_wam *e_Wam = new exprtk_wam(this);
  v_exprtkSymbolTable.add_function("wam", *e_Wam);

  exprtk_sd *eStandartDeviation = new exprtk_sd(this);
  v_exprtkSymbolTable.add_function("sd", *eStandartDeviation);

	exprtk_rawMoment *eRawMoment = new exprtk_rawMoment(this);
  v_exprtkSymbolTable.add_function("rawMoment", *eRawMoment);

  exprtk_centralMoment *eCentralMoment = new exprtk_centralMoment(this);
  v_exprtkSymbolTable.add_function("centralMoment", *eCentralMoment);

  exprtk_tmean *eTurncatedMean = new exprtk_tmean(this);
  v_exprtkSymbolTable.add_function("tmean", *eTurncatedMean);

	ss::exprtk::NormQuantile *eNormQuantile = new ss::exprtk::NormQuantile;
  v_exprtkSymbolTable.add_function("normQuantile", *eNormQuantile);

	ss::exprtk::StudQuantile *eStudQuantile = new ss::exprtk::StudQuantile;
  v_exprtkSymbolTable.add_function("studQuantile", *eStudQuantile);

	ss::exprtk::PearQuantile *ePearQuantile = new ss::exprtk::PearQuantile;
  v_exprtkSymbolTable.add_function("pearQuantile", *ePearQuantile);

	ss::exprtk::FishQuantile *eFishQuantile = new ss::exprtk::FishQuantile;
  v_exprtkSymbolTable.add_function("fishQuantile", *eFishQuantile);

  exprtk_beta *eBeta = new exprtk_beta(this);
  v_exprtkSymbolTable.add_function("beta", *eBeta);

  exprtk_counterKurtosis *eCounterKurtosis = new exprtk_counterKurtosis(this);
  v_exprtkSymbolTable.add_function("counterKurtosis", *eCounterKurtosis);

  exprtk_ncv *eNonparametricVariationCoef = new exprtk_ncv(this);
  v_exprtkSymbolTable.add_function("ncv", *eNonparametricVariationCoef);

	ss::exprtk::NormalDistributionCdf *eNormalDistribtuionCdf =
      new ss::exprtk::NormalDistributionCdf();

  v_exprtkSymbolTable.add_function("normCfd", *eNormalDistribtuionCdf);

  v_exprtkSymbolTable.add_function("uRand", *new ss::exprtk_uniform_real_distribution);
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
    "sd(m) — середньоквадратичне відхилення\n"
    "tmean(k) — усічене середнє (k ∈ (0;0.5])\n"
    "rawMoment(n) — початковий момент n-го порядку (n ∈ R)\n"
    "centralMoment(n, m) — центральний момент n-го порядку (n ∈ R)\n"
    "beta(k) — бета–коефіцієнт\n"
    "ncv() — непараметричний коефіцієнт варіації\n"
    "uRand(a, b) — рівномірно розподілена випадкова величина";

}
