#include "Parser.hpp"
#include "Fact.hpp"
#include "IDependence.hpp"
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
			std::cout << "\n\tParsing line " << nLine << " : ";
			if (line.length() == 0)
				std::cout << "Warning line " << nLine  << " :" << std::endl << "Useless NewLine" << std::endl;
			else if (line[0] == '=')
				setFact(line.substr(1), nLine);
			else if (line.find_first_of("*-+") == std::string::npos && line.find_first_of("=") != std::string::npos)
				simple(line, nLine);
			else
				decomposeAndCreate(line, nLine);
			nLine++;
		}
		std::cout << std::endl << std::endl << std::endl << std::endl << "End of file" << std::endl << std::endl << std::endl;

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
	_rules[fact.c_str()]->setStatus(TRUE);
}

void Parser::decomposeAndCreate(std::string const & line, int nLine)
{
	if (line.find_first_of("=") == std::string::npos)
	{
		std::cerr << "Syntax error on line " << nLine << " :" << std::endl << "No \"=\"" << std::endl;
	}
	std::string left = line.substr(0, line.find_first_of("="));
	std::string right = line.substr(line.find_first_of("=") + 1);
	std::cout << "Left : " << left << " Right : " << right << std::endl;



	if (right.find_first_of("+-") != std::string::npos)
		std::cerr << "Syntax error on line " << nLine << " :" << std::endl << "No \"+ or - on right operand\"" << std::endl;







	// Traitement des opérandes droite
	size_t rightStart = 0, rightEnd = 1;
	while (rightEnd != std::string::npos)
	{
		rightEnd = right.find_first_of("*", rightStart);
		if (rightEnd != right.length() - 1)
		{
			std::string currentLeft = right.substr(rightStart,rightEnd - rightStart);
			std::cout << "Right : " << currentLeft << std::endl;

			// Traitement des opérandes gauche
			size_t leftStart = 0;
			size_t leftEnd = left.find_first_of("*+-");


			while (leftEnd != std::string::npos)
			{
				std::string currentSubLeft = left.substr(leftStart, leftEnd - leftStart);
				std::cout << "SUB LEFT : " << currentSubLeft << std::endl;



				std::cout << "TestCHAR : -" << left[leftEnd] << "-" << std::endl;
				if (left[leftEnd] == '+')
				{
					if (!factExists(currentLeft))
						_rules[currentLeft.c_str()] = new Fact(currentLeft);
					if (!factExists(currentSubLeft))
						_rules[currentSubLeft.c_str()] = new Fact(currentSubLeft);
					static_cast<Fact*>(_rules[currentLeft.c_str()])->addDependence(_rules[currentSubLeft.c_str()]);
					if (left.find_first_of("*+-", leftEnd + 1) == std::string::npos)
					{
						if (leftEnd + 2 == left.length())
							leftEnd = left.length() - 1;
					}
				}
				else if (left[leftEnd] == '*')
				{
					std::cout << "It's a AND" << std::endl;
					size_t subLeftEnd = left.find_first_of("*+-", leftEnd + 1);
					subLeftEnd = (subLeftEnd == std::string::npos ? left.length() - 1 : subLeftEnd);

					std::string currentSubRight = left.substr(leftEnd + 1, subLeftEnd - leftEnd + 1);
					if (currentSubRight.length() > 0)
					{
						std::cout << "-" << currentSubRight << "-" << std::endl;
						if (!factExists(currentLeft))
							_rules[currentLeft.c_str()] = new Fact(currentLeft);
						if (!factExists(currentSubRight))
							_rules[currentSubRight.c_str()] = new Fact(currentSubRight);
						if (!factExists(currentSubLeft))
							_rules[currentSubLeft.c_str()] = new Fact(currentSubLeft);
						And* dep = new And(_rules[currentSubRight.c_str()], _rules[currentSubLeft.c_str()]);

						static_cast<Fact*>(_rules[currentLeft.c_str()])->addDependence(dep);
						leftEnd = left.find_first_of("*+-", subLeftEnd + 1);
					}
					else
						std::cerr << "Syntax error on line " << nLine << " :" << std::endl << "WTF ?" << std::endl;
					
				}
				else if (left[leftEnd] == '-')
				{
					std::cout << "It's a XOR" << std::endl;
				}
				else
				{
					std::string OrFact = left.substr(leftEnd);
					if (!factExists(OrFact))
						_rules[OrFact.c_str()] = new Fact(OrFact);
					static_cast<Fact*>(_rules[currentLeft.c_str()])->addDependence(_rules[OrFact.c_str()]);
					break;
				}
			}



			rightStart = rightEnd + 1;
		}
	}
}

void Parser::simple(std::string const & line, int nLine)
{
	std::string left = line.substr(0, line.find_first_of("="));
	std::string right = line.substr(line.find_first_of("=") + 1);

	if (!factExists(right))
		_rules[right.c_str()] = new Fact(right);
	if (!factExists(left))
		_rules[left.c_str()] = new Fact(left);

	static_cast<Fact*>(_rules[right.c_str()])->addDependence(_rules[left.c_str()]);

}


bool Parser::factExists(std::string const & fact)
{
	if (_rules.find(fact.c_str()) == _rules.end())
		return false;
	return true;
}


std::map<std::string, IDependence*> const & Parser::getRules()
{
	return _rules;
}