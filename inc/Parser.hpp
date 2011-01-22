#ifndef PARSER_HPP_
# define PARSER_HPP_

# include "IDependence.hpp"
# include <iostream>
# include <fstream>

class Parser
{
private:
  std::ifstream _ifs;
  IDependence *_factToCheck;

public:
  Parser(std::string filename, std::string factToCheck);
  void run(std::string factToCheck);
  IDependence *getFactToCheck();
};

#endif
