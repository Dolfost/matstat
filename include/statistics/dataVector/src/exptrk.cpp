#include "../dataVector.hpp"
#include "dataVectorExprtk.hpp"
#include "statisticsExprtk.hpp"

void DataVector::setTransformationSymbolTable() {
  if (transformationSymbolTableReady)
    return;

  transformationSymbolTable.add_constant("e", M_E);
  transformationSymbolTable.add_constant("pi", M_PI);

  exprtkMean *eMean = new exprtkMean(this);
  transformationSymbolTable.add_function("mean", *eMean);

  exprtkMed *eMed = new exprtkMed(this);
  transformationSymbolTable.add_function("med", *eMed);

  exprtkMad *eMad = new exprtkMad(this);
  transformationSymbolTable.add_function("mad", *eMad);

  exprtkKurtosis *eKurtosis = new exprtkKurtosis(this);
  transformationSymbolTable.add_function("kurtosis", *eKurtosis);

  exprtkSkew *eSkew = new exprtkSkew(this);
  transformationSymbolTable.add_function("skew", *eSkew);

  exprtkWalshAveragesMed *eWalshAveragesMed = new exprtkWalshAveragesMed(this);
  transformationSymbolTable.add_function("wam", *eWalshAveragesMed);

  exprtkVariance *eVariance = new exprtkVariance(this);
  transformationSymbolTable.add_function("variance", *eVariance);

  exprtkXmin *eXmin = new exprtkXmin(this);
  transformationSymbolTable.add_function("xmin", *eXmin);

  exprtkXmax *eXmax = new exprtkXmax(this);
  transformationSymbolTable.add_function("xmax", *eXmax);

  exprtkVariationCoef *eVariationCoef = new exprtkVariationCoef(this);
  transformationSymbolTable.add_function("cv", *eVariationCoef);

  exprtkSize *eSize = new exprtkSize(this);
  transformationSymbolTable.add_function("size", *eSize);

  exprtkStandartDeviation *eStandartDeviation =
      new exprtkStandartDeviation(this);
  transformationSymbolTable.add_function("standartDeviation",
                                         *eStandartDeviation);

  exprtkRawMoment *eRawMoment = new exprtkRawMoment(this);
  transformationSymbolTable.add_function("rawMoment", *eRawMoment);

  exprtkCentralMoment *eCentralMoment = new exprtkCentralMoment(this);
  transformationSymbolTable.add_function("centralMoment", *eCentralMoment);

  exprtkTurncatedMean *eTurncatedMean = new exprtkTurncatedMean(this);
  transformationSymbolTable.add_function("turncatedMean", *eTurncatedMean);

  exprtkNormQuantile *eNormQuantile = new exprtkNormQuantile;
  transformationSymbolTable.add_function("normQuantile", *eNormQuantile);

  exprtkStudQuantile *eStudQuantile = new exprtkStudQuantile;
  transformationSymbolTable.add_function("studQuantile", *eStudQuantile);

  exprtkPearQuantile *ePearQuantile = new exprtkPearQuantile;
  transformationSymbolTable.add_function("pearQuantile", *ePearQuantile);

  exprtkFishQuantile *eFishQuantile = new exprtkFishQuantile;
  transformationSymbolTable.add_function("fishQuantile", *eFishQuantile);

  exprtkBeta *eBeta = new exprtkBeta(this);
  transformationSymbolTable.add_function("beta", *eBeta);

  exprtkCounterKurtosis *eCounterKurtosis = new exprtkCounterKurtosis(this);
  transformationSymbolTable.add_function("counterKurtosis", *eCounterKurtosis);

  exprtkNonparametricVariationCoef *eNonparametricVariationCoef =
      new exprtkNonparametricVariationCoef(this);
  transformationSymbolTable.add_function("nonparametricCv",
                                         *eNonparametricVariationCoef);

  exprtkNormalDistributionCdf *eNormalDistribtuionCdf =
      new exprtkNormalDistributionCdf();

  transformationSymbolTable.add_function("normCfd", *eNormalDistribtuionCdf);

  transformationSymbolTableReady = true;
}

const QString DataVector::exprtkFuncitons =
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
    "beta(k) — бета–коефіцієнт";
