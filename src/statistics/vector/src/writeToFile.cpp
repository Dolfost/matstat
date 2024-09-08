#include "vector.hpp"
#include <fstream>

namespace ss {

bool Vector::writeToFile(std::string filename) {
	std::ofstream file(filename, std::ofstream::out);

  if (!file.good())
    return false;

  for (auto const &x : *this) {
    file << x << "\n";
  }

  file.close();

  return true;
}

}
