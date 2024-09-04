#include "vector.hpp"
#include "classSeries.hpp"

namespace ss {

void Vector::makeClassSeries(unsigned short cls) {
  if (cls == 0)
    cls = cs->calculateClassCount();

  if (csReady == false or cls != cs->classCount()) {
    cs->makeSeries(cls);
    csReady = true;
  }
}

Vector::ClassSeries *Vector::classSeries() {
  if (csReady)
    return cs;
  else
    return nullptr;
}

}
