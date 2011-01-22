#include "Parser.hpp"
#include <iostream>
#include <sstream>
#include <list>

Parser::Parser(std::string filename, std::string factToCheck)
  : _ifs(filename.c_str())
{
  run(factToCheck);
}

void Parser::run(std::string factToCheck)
{
  std::string line;

  while (0)
    {
      std::getline(_ifs, line);
      //std::stringstream lstream(line);
      std::cout << line << std::endl;
    }
}

IDependence *Parser::getFactToCheck()
{
  return _factToCheck;
}
