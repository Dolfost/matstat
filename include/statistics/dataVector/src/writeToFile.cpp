#include "../dataVector.hpp"

bool DataVector::writeToFile(QString filename) {
  QFile file(filename);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return false;
  QTextStream stream(&file);

  for (auto const &x : dataVector) {
    stream << x << "\n";
  }

  file.close();

  return true;
}
