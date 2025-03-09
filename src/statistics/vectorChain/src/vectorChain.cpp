#include <vectorChain.hpp>

#include <stdexcept>
#include <ios>
#include <vector>
#include <fstream>
#include <sstream>

namespace ss {

void VectorChain::invalidate() {
}

void VectorChain::checkSize() {
}

void VectorChain::writeToFile(std::string filename) {
  size_t n = at(0).size();

  for (size_t i = 1; i < size(); i++) {
	  if (at(i).size() != n)
		  throw std::logic_error("Вектори не однакового розміру!");
  }

	std::ofstream file;
	file.exceptions(std::ios::badbit | std::ios::failbit);
	file.open(filename, std::ios::out);

  std::vector<std::vector<double>::const_iterator> its;

  for (auto& v : *this) {
	  its.push_back(v.begin());
  }

	std::stringstream line;
	line.setf(std::ios::fixed);
  for (size_t i = 0; i < n; i++) {
		line.str("");
	  for (auto& xi : its) {
			line << *xi << ", ";
		  ++xi;
	  }
	  
	  file << (line.str().substr(0, line.str().size() - 2)) << "\n";
  }

  file.close();
}


}
