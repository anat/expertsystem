#ifndef PARSER_HPP_
# define PARSER_HPP_

# include "IDependence.hpp"
# include "Fact.hpp"
# include <iostream>
# include <fstream>
# include <map>
# include <list>
# include <string>
class Parser
{
private:
	std::ifstream* _ifs;
	IDependence* _factToCheck;
	char** _param;
	int _count;
	bool _interactive;
	std::map<std::string, IDependence*> _rules;

	void setFact(std::string const & fact, TStatus status, int nLine);
	bool factExists(std::string const & fact);
	void decompose(std::string const & line, int nLine);
	std::list < IDependence * > * parseLeft(std::string const & left, int nLine);
	std::list < IDependence * > * parseRight(std::string right, int nLine);
	IDependence * createOrGetFact(std::string const & fact);
	char const * getType(IDependence * dependence);
	char getNext(std::string const & rule, int index);
public:
	Parser(char** param, int count);
	std::map<std::string, IDependence*> const & getRules();

	void run();
};

#endif
