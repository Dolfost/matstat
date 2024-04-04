#include "../dataVector.hpp"

std::list<double> &DataVector::walshAverages() {
  if (!stat.walshAverages.second)
    computeWalshAverages();

  return stat.walshAverages.first;
}

double DataVector::walshAveragesMed() {
  if (!stat.walshAveragesMed.second)
    computeWalshAveragesMed();

  return stat.walshAveragesMed.first;
}

void DataVector::computeWalshAverages() {
  for (auto const &i : dataVector) {
    for (auto const &j : dataVector) {
      stat.walshAverages.first.push_back((i + j) * 0.5);
    }
  }

  stat.walshAverages.second = true;
}

void DataVector::computeWalshAveragesMed() {
  DataVector walshAveragesVector(walshAverages());
  stat.walshAveragesMed.first = walshAveragesVector.med();

  stat.walshAveragesMed.second = true;
}

