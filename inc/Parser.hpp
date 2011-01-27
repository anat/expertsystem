#ifndef PARSER_HPP_
# define PARSER_HPP_

# include "IDependence.hpp"
# include <iostream>
# include <fstream>
# include <map>


class Parser
{
private:
  std::ifstream* _ifs;
  IDependence* _factToCheck;
  char** _param;
  int _count;
  std::map<std::string, IDependence*> _rules;
  void setFact(std::string const & fact, int nLine);
  void decomposeAndCreate(std::string const & line, int nLine);
  bool factExists(std::string const & fact);
  void simple(std::string const & line, int nLine);
public:
  Parser(char** param, int count);
  void run();
  IDependence *getFactToCheck();
  std::map<std::string, IDependence*> const & getRules();

};

#endif
