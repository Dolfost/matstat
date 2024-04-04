#include "../dataVector.hpp"
#include "varSeries.hpp"

DataVector::VarSeries *DataVector::varSeries() {
  if (vsReady == false) {
    vs->makeSeries();
    vsReady = true;
  }

  return vs;
}
