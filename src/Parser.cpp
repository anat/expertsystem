#include "Parser.hpp"
#include "Fact.hpp"
#include "IDependence.hpp"
#include "Xor.hpp"
#include "Not.hpp"
#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include <list>
#include <cstdlib>

Parser::Parser(char** param, int count) : _param(param), _count(count)
{
	if (_count == 4)
	{	
		if (param[3] == std::string("1"))
			_interactive = true;
		else if (param[3] == std::string("0"))
			_interactive = false;
		else
		{
			std::cerr << "Usage : " << _param[0] << " \"rulesSource\" \"factToCheck factToCheck...\" [interactiveMode=0/1]" << std::endl << "Bad parameter : interactiveMode" << std::endl;
			exit(0);
		}
	}
	else
		_interactive = false;
	run();
}

void Parser::run()
{
	if (_count < 3 || _count > 4)
	{
		std::cerr << "Usage : " << _param[0] << " \"rulesSource\" \"factToCheck factToCheck...\" [interactiveMode=0/1]" << std::endl;
		exit(0);
	}
	else
	{
		int nLine = 1;
		_ifs = new std::ifstream(_param[1]);
		std::string line;
		while (std::getline(*_ifs,line))
		{
			if (line.length() == 0)
				std::cout << "Notice line " << nLine  << " :" << std::endl << "Useless NewLine" << std::endl;
			else if (line.length() >= 2 && line.substr(0, 2) == "//")
				; // comment
			else if (line[0] == '=' && line[1] == '!') 
				setFact(line.substr(2), FALSE , nLine);		// if it's a fact like =A
			else if (line[0] == '=') 
				setFact(line.substr(1), TRUE, nLine);		// if it's a fact like =A
			else
				decompose(line, nLine);	// all other case
			nLine++;
		}
	}

}

void Parser::setFact(std::string const & fact, TStatus status, int nLine)
{
	if (!this->factExists(fact))
	{
		std::cerr << "Syntax error on line " << nLine << " :" << std::endl << "Setting a fact before creating it." << std::endl;
		exit(1);
	}
	_rules[fact.c_str()]->setStatus(status);
}

void Parser::decompose(std::string const & line, int nLine)
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
	std::list<IDependence*> * newLeft = parseLeft(left, nLine);


	std::list<IDependence*>::iterator it = newLeft->begin();
	std::list<IDependence*>::iterator end = newLeft->end();

	std::list<IDependence*> finalList;

	std::string prec = "";

	while (it != end)
	{
		IDependence* current = *(it);
		if (this->getType(current) == std::string("FACT"))
			finalList.push_back(current);
		else
		{
			std::list<IDependence*>::iterator negative(it);

			while (it != end && (getType(*it) == std::string("AND") || getType(*it) == std::string("XOR")))
				++it;

			std::list<IDependence*>::iterator start(negative);
			std::list<IDependence*> * dependence;
			dependence = new std::list<IDependence*>();

			while (start != it)
			{
				dependence->push_back(*start);
				++start;
			}
			// CREATE SUB DEPENDENCIES, NO "!" implementation
			if (dependence->size() == 0)
				finalList.push_back(current);
			else
				finalList.push_back(new And(dependence, _interactive));
			--it;
		}
		++it;
	}


	std::list<Fact*>* newRight = (std::list<Fact*>*)parseRight(right, nLine);

	std::list<Fact*>::iterator rit = newRight->begin();
	std::list<Fact*>::iterator rend = newRight->end();
	for (;rit != rend; ++rit)
	{
		std::list<IDependence*>::iterator it = finalList.begin();
		std::list<IDependence*>::iterator end = finalList.end();

		while (it != end)
		{
			(*rit)->addDependence(*it);
			++it;
		}
	}


}




std::list<IDependence *> *  Parser::parseLeft(std::string const & left, int nLine)
{
	std::list<IDependence *> * result = new std::list<IDependence *> ();

	size_t start, end;

	start = 0;
	end = left.find_first_of("*+-");

	if (end == std::string::npos)		// Case just one !
	{
		result->push_back(createOrGetFact(left));
		return result;
	}
	char prec, current, next;
	prec = left[end];
	next = getNext(left, end);

	std::list<IDependence *> * dependence = new std::list<IDependence *>();

	while (end != std::string::npos)
	{
		current = left[end];
		next = getNext(left, end);
		IDependence * currentFact = createOrGetFact(left.substr(start, end - start));
		if (current == '+')
		{
			if (prec == '*' || prec == '-')
				dependence->push_back(currentFact);
			if (prec == '*')
				result->push_back(new And(dependence, _interactive));
			else if (prec == '-')
				result->push_back(new Xor(dependence, _interactive));
			else
				result->push_back(currentFact);

			if ((prec == '*') || (prec == '-'))
				dependence = new std::list<IDependence *>();
		}
		else if (current != prec && (current == '*' || current == '-') && (prec == '*' || prec == '-'))
		{
			if (prec == '*' || prec == '-')
				dependence->push_back(currentFact);
			if (prec == '*')
				result->push_back(new And(dependence, _interactive));
			else if (prec == '-')
				result->push_back(new Xor(dependence, _interactive));
			else
				result->push_back(currentFact);

			if ((prec == '*') || (prec == '-'))
				dependence = new std::list<IDependence *>();
			dependence->push_back(currentFact);
		}
		else if (current == prec)
		{
			if (prec == '*' || prec == '-')
				dependence->push_back(currentFact);
		}
		else
		{
			if (next == '+')
				result->push_back(currentFact);
			else
				dependence->push_back(currentFact);
		}
		prec = current;
		start = end + 1;
		end = left.find_first_of("*+-", end + 1);
	}

	if (start < left.length())
	{
		if (prec == '*')
		{
			dependence->push_back(createOrGetFact(left.substr(start, end - start)));
			result->push_back(new And(dependence, _interactive));
		}
		else if (prec == '-')
		{
			dependence->push_back(createOrGetFact(left.substr(start, end - start)));
			result->push_back(new Xor(dependence, _interactive));
		}
		else
			result->push_back(createOrGetFact(left.substr(start, end - start)));
	}
	return result;
}


std::list<IDependence*> * Parser::parseRight(std::string right, int nLine)
{
	std::list<IDependence*> * result = new std::list<IDependence*>();

	size_t index = right.find_first_of("*");
	if (index == std::string::npos)
	{
		result->push_back(createOrGetFact(right));
		return result;
	}
	while (index != std::string::npos)
	{
		result->push_back(createOrGetFact(right.substr(0, index)));
		right = right.substr(index + 1);
		index = right.find_first_of("*");
	}
	if (right.length() != 0)
		result->push_back(createOrGetFact(right));
	return result;
}


bool Parser::factExists(std::string const & fact)
{
	if (_rules.find(fact.c_str()) == _rules.end())
		return false;
	return true;
}

IDependence * Parser::createOrGetFact(std::string const & fact)
{
	if (fact[0] == '!')
	{
		// NOT
		if (!factExists(fact.substr(1)))
			this->_rules[fact.substr(1)] = new Not(fact.substr(1), _interactive);
	}
	if (!factExists(fact))
		this->_rules[fact] = new Fact(fact, _interactive);
	return static_cast<Fact*>(_rules[fact]);
}


char const * Parser::getType(IDependence * dependence)
{
	Fact * current = dynamic_cast<Fact *>(dependence);
	if (current)
		return "FACT";
	else
	{
		And * current = dynamic_cast<And *>(dependence);
		if (current)
			return "AND";
		else
		{
			Xor * current = dynamic_cast<Xor *>(dependence);
			if (current)
				return "XOR";
			else
			{
				std::cerr << "Unknow type !" << std::endl;
				exit(1);
			}
		}
	}
}

std::map<std::string, IDependence*> const & Parser::getRules()
{
	return _rules;
}


char Parser::getNext(std::string const & rule, int index)
{
	index = rule.find_first_of("+-*", index -1);
	if (index == std::string::npos)
		return 0;
	return rule[index];
}
