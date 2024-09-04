#include "vector.hpp"
#include "varSeries.hpp"

namespace ss {

Vector::VarSeries *Vector::varSeries() {
  if (vsReady == false) {
    vs->makeSeries();
    vsReady = true;
  }

  return vs;
}

}
