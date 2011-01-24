#include "Parser.hpp"
#include <iostream>
#include <sstream>
#include <list>
#include <map>

Parser::Parser(char** param, int count) : _param(param), _count(count)
{
	run();
}

void Parser::run()
{
	if (_count <= 2)
		std::cout << "Usage : " << _param[0] << " rulesSource factToCheck [factToCheck] ..." << std::endl;
	else
	{
		int nLine = 1;
		_ifs = new std::ifstream(_param[1]);
		std::string line;
		while (std::getline(*_ifs,line))
		{
			std::cout << "Parsing line " << nLine << std::endl;
			if (line.length() == 0)
				std::cout << "Warning line " << nLine  << " :" << std::endl << "Useless NewLine" << std::endl;
			else if (line[0] == '=')
				setFact(line.substr(1), nLine);
			else
				decomposeAndCreate(line, nLine);
			nLine++;
		}
		std::cout << "End of file" << std::endl;

	}

}

IDependence *Parser::getFactToCheck()
{
	return _factToCheck;
}


void Parser::setFact(std::string const & fact, int nLine)
{
	if (!this->factExists(fact))
	{
		std::cerr << "Syntax error on line " << nLine << " :" << std::endl << "Setting a fact before creating it." << std::endl;
		exit(1);
	}
	_rules[fact]->setStatus(TRUE);
}

void Parser::decomposeAndCreate(std::string const & line, int nLine)
{
	if (line.find_first_of("=") == std::string::npos)
	{
		std::cerr << "Syntax error on line " << nLine << " :" << std::endl << "No \"=\"" << std::endl;
	}
	std::string left = line.substr(0, line.find_first_of("="));
	std::string right = line.substr(line.find_first_of("=") + 1);
	std::cout << left << std::endl;
	std::cout << right << std::endl;



	if (right.find_first_of("+-") != std::string::npos)
		std::cerr << "Syntax error on line " << nLine << " :" << std::endl << "No \"+ or - on right operand\"" << std::endl;


	size_t first = left.find_first_of("*+-");

	if (first == std::string::npos)
	{
		// Solo fact
	////	if (!
	////		_rules[left]
	}

}

bool Parser::factExists(std::string const & fact)
{
	if (_rules.find(fact) == _rules.end())
		return false;
	return true;
}

