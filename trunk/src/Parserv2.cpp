#include "..\inc\Parserv2.hpp"
#include "Fact.hpp"
#include "IDependence.hpp"
#include "Xor.hpp"
#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include <list>

Parserv2::Parserv2(char** param, int count) : _param(param), _count(count)
{
	run();
}

void Parserv2::run()
{
	if (_count != 3)
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
				setFact(line.substr(1), nLine);		// if it's a fact like =A
			else
				decompose(line, nLine);	// all other case
			nLine++;
		}
		std::cout << std::endl << std::endl << std::endl << std::endl << "End of file" << std::endl << std::endl << std::endl;
	}

}

void Parserv2::setFact(std::string const & fact, int nLine)
{
	if (!this->factExists(fact))
	{
		std::cerr << "Syntax error on line " << nLine << " :" << std::endl << "Setting a fact before creating it." << std::endl;
		exit(1);
	}
	_rules[fact.c_str()]->setStatus(TRUE);
}

void Parserv2::decompose(std::string const & line, int nLine)
{
	if (line.find_first_of("=") == std::string::npos)
	{
		std::cerr << "Syntax error on line " << nLine << " :" << std::endl << "No \"=\"" << std::endl;
		exit(0);
	}
	std::string left = line.substr(0, line.find_first_of("="));
	std::string right = line.substr(line.find_first_of("=") + 1);

	// check if there is Or or Xor in right operand <!> forbidden !
	if (right.find_first_of("+-") != std::string::npos)
	{
		std::cerr << "Syntax error on line " << nLine << " :" << std::endl << "No \"+ or - on right operand\"" << std::endl;
		exit(0);
	}
	std::list<std::list<IDependence*> * > * newLeft = parseLeft(left, nLine);
	//std::list<Fact*>* newRight = parseRight(right, nLine);
}


/*
A+B*C-D
*/

std::list < std::list<IDependence *> * > * Parserv2::parseLeft(std::string const & left, int nLine)
{
	std::list < std::list<IDependence *> * > * result = new std::list < std::list<IDependence *> * >();
	size_t start, end;

	start = 0;
	end = left.find_first_of("*+-");

	std::list<IDependence *> * dependence = new std::list<IDependence *>();

	if (end == std::string::npos)		// Case just one !
	{
		dependence->push_back(new Fact(left));
		result->push_back(dependence);
		return result;
	}


	char prec, current;
	
	prec = left[end];

	while (end != std::string::npos)
	{
		current = left[end];

		dependence->push_back(new Fact(left.substr(start, end - 1)));
		if (current == '+')
		{
			result->push_back(dependence);
			std::list<IDependence *> * dependence = new std::list<IDependence *>();
		}
		else if (current != prec)
		{
			result->push_back(dependence);
			std::list<IDependence *> * dependence = new std::list<IDependence *>();
			dependence->push_back(new Fact(left.substr(start, end - 1)));
		}
		else if (current == '*' || current == '-')
		{


		}

		prec = current;
		end = left.find_first_of("*+-");
	}




		return 0;
}
/*
A*B*C+D
A*B+C*D

Fact *a = new Fact("A");
Fact *b = new Fact("B");
Fact *c = new Fact("C");
Fact *d = new Fact("D");
Fact *e = new Fact("E");

=E
e->setStatus(TRUE);


B*C=A
And *cb = new And(c, b);
a->addDependencie(cb);


D+E=B
b->addDependencie(d);
b->addDependencie(e);


B=C
c->addDependencie(b);
*/


std::list<Fact*> * Parserv2::parseRight(std::string right, int nLine)
{
	std::list<Fact*> * result = new std::list<Fact*>();

	size_t index = right.find_first_of("*");
	if (index == std::string::npos)
	{
		result->push_back(new Fact(right));
		return result;
	}
	while (index != std::string::npos)
	{
		result->push_back(new Fact(right.substr(0, index)));
		right = right.substr(index + 1);
		index = right.find_first_of("*");
	}
	if (right.length() != 0)
		result->push_back(new Fact(right));
	return result;
}


bool Parserv2::factExists(std::string const & fact)
{
	if (_rules.find(fact.c_str()) == _rules.end())
		return false;
	return true;
}