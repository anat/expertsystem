#ifndef PARSERV2_HPP_
# define PARSERV2_HPP_

# include "IDependence.hpp"
# include "Fact.hpp"
# include <iostream>
# include <fstream>
# include <map>
# include <list>
# include <string>
class Parserv2
{
private:
	std::ifstream* _ifs;
	IDependence* _factToCheck;
	char** _param;
	int _count;
	std::map<std::string, IDependence*> _rules;

	void setFact(std::string const & fact, int nLine);
	bool factExists(std::string const & fact);
	void decompose(std::string const & line, int nLine);
	std::list < std::list < IDependence * > * > * parseLeft(std::string const & left, int nLine);
	std::list < Fact * > * parseRight(std::string right, int nLine);
	Fact * createOrGetFact(std::string const & fact);
	char const * getType(IDependence * dependence);
public:
	Parserv2(char** param, int count);
	std::map<std::string, IDependence*> const & getRules();

	void run();
};

#endif
