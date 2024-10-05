#include "vector.hpp"
#include "vector/exprtk_quantile.hpp"

namespace ss {

double exprtk::NormQuantile::operator()(const double& alpha) {
	return normQuantile(alpha);
}

void Vector::addGenericsToSymbolTable(::exprtk::symbol_table<double>& t, std::string p) {
  t.add_constant("e", M_E);
  t.add_constant("pi", M_PI);

	ss::exprtk::NormQuantile *eNormQuantile = new ss::exprtk::NormQuantile;
  t.add_function("normQuantile", *eNormQuantile);

	ss::exprtk::StudQuantile *eStudQuantile = new ss::exprtk::StudQuantile;
  t.add_function("studQuantile", *eStudQuantile);

	ss::exprtk::PearQuantile *ePearQuantile = new ss::exprtk::PearQuantile;
  t.add_function("pearQuantile", *ePearQuantile);

	ss::exprtk::FishQuantile *eFishQuantile = new ss::exprtk::FishQuantile;
  t.add_function("fishQuantile", *eFishQuantile);

	ss::exprtk::NormalDistributionCdf *eNormalDistribtuionCdf =
      new ss::exprtk::NormalDistributionCdf();

  t.add_function("normCfd", *eNormalDistribtuionCdf);

  t.add_function("uRand", *new ss::exprtk::exprtk_uniform_real_distribution);
}

void Vector::addStatisticsToSymbolTable(::exprtk::symbol_table<double>& t, Vector* v, std::string p) {
	SS_ADD_FUNCTION(mean)
	SS_ADD_FUNCTION(med)
	SS_ADD_FUNCTION(mad)
	SS_ADD_FUNCTION(kurtosis)
	SS_ADD_FUNCTION(skew)
	SS_ADD_FUNCTION(variance)
	SS_ADD_FUNCTION_N(min, "first")
	SS_ADD_FUNCTION_N(max, "last")
	SS_ADD_FUNCTION(cv)
	SS_ADD_FUNCTION(size)
	SS_ADD_FUNCTION(wam)
	SS_ADD_FUNCTION(sd)
	SS_ADD_FUNCTION(rawMoment)
	SS_ADD_FUNCTION(centralMoment)
	SS_ADD_FUNCTION(tmean)
	SS_ADD_FUNCTION(beta)
	SS_ADD_FUNCTION(counterKurtosis)
	SS_ADD_FUNCTION(ncv)
}

const std::string Vector::exprtkFuncitons =
	"Аргументи:\n "
	"m — тип оцінки. 'pop' – зсунена, 'spl' – не зсунена\n"
	"Функції:\n"
	"med() — медіана\n"
	"first() — наймешний xᵢ\n"
	"last() — найбільший xᵢ\n"
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
