#include "../dataVector.hpp"
#include "classSeries.hpp"

void DataVector::makeClassSeries(unsigned short cls) {
  if (cls == 0)
    cls = cs->calculateClassCount();

  if (csReady == false or cls != cs->classCount()) {
    cs->makeSeries(cls);
    csReady = true;
  }
}

DataVector::ClassSeries *DataVector::classSeries() {
  if (csReady)
    return cs;
  else
    return nullptr;
}
