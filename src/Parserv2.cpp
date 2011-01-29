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




	// ADD DEPENDENCIES TO DEPENDENCIE
	std::list<std::list<IDependence*> * >::iterator lit = newLeft->begin();
	std::list<std::list<IDependence*> * >::iterator lend = newLeft->end();

	//	LIST LOOK LIKE
	//	IT->IT->AND
	//	IT->IT->XOR
	//	IT->IT->FACT/FACT/FACT/FACT

	std::list<IDependence*> finalList;

	std::string prec = "";
	while (lit != lend)
	{
		std::cout << "-------------" <<  (*lit)->size() << std::endl;
		IDependence* current = *((*lit)->begin());

		if (this->getType(current) == "FACT")
			finalList.push_back(current);
		else
		{
			std::cout << this->getType(current) << std::endl;
			std::list<std::list<IDependence*> * >::iterator negative(lit);
			
			while (lit != lend && (getType((*((*lit)->begin()))) == "AND" || getType((*((*lit)->begin()))) == "XOR"))
				++lit;

			if (lit == negative)
				std::cout << "AHAHAHHAA" << std::endl;

			std::cout << "TEST" << std::endl;
			std::list<std::list<IDependence*> * >::iterator start(negative);
			++start;
			std::list<IDependence*> * dependence;
			dependence = new std::list<IDependence*>();
			while (start != lit)
			{
				dependence->push_back((*((*start)->begin())));
				++start;
			}
			if (dependence->size() == 0)
				finalList.push_back(current);
			else
				finalList.push_back(new And(dependence));
			--lit;
		}
		++lit;
	}


	std::list<Fact*>* newRight = parseRight(right, nLine);

	std::list<Fact*>::iterator rit = newRight->begin();
	std::list<Fact*>::iterator rend = newRight->begin();
	for (;rit != rend; ++rit)
	{
		std::list<IDependence*>::iterator it = finalList.begin();
		std::list<IDependence*>::iterator end = finalList.end();

		while (it != end)
		{
			std::cout << "FINISH" << getType(*it) << std::endl;
			(*rit)->addDependence(*it);
			++it;
		}
	}


}




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

	/*			A+B*C-D			*/


	while (end != std::string::npos)
	{
		std::cout << std::endl << "LOOP" << std::endl << std::endl;
		current = left[end];
		std::cout << "CLASSIC" << std::endl;
		dependence->push_back(createOrGetFact(left.substr(start, end - start)));
		if (current == '+')
		{
			result->push_back(dependence);
			dependence = new std::list<IDependence *>();
			std::cout << "[" << left.substr(start, end - start) << "]" << "OR  :  CREATE NEW" << std::endl;
		}
		else if (current != prec && (current == '*' || current == '-') && (prec == '*' || prec == '-'))
		{
			IDependence* Dep;
			if (prec == '*')
				Dep = new And(dependence);
			else if (prec == '-')
				Dep = new Xor(dependence);
			std::list<IDependence *> * listDep = new std::list<IDependence *>();
			listDep->push_back(Dep);
			result->push_back(listDep);
			// Create the end

			dependence = new std::list<IDependence *>();
			std::cout << "[" << left.substr(start, end - start) << "]" << "CHANGE DEP  :  CREATE NEW" << std::endl;
			//dependence->push_back(createOrGetFact(left.substr(start, end - start)));
		}
		else if (current == prec)
		{
			std::cout << "[" << left.substr(start, end - start) << "]" << "SAME" << std::endl;
		}
		else
		{
			// DO NOTHING
			std::cout << "[" << left.substr(start, end - start) << "]" << "OTHER CASE" << std::endl;
		}
		prec = current;
		start = end + 1;
		end = left.find_first_of("*+-", end + 1);
	}

	std::cout << std::endl << "END LOOP" << std::endl << std::endl << "start:" << start << std::endl << "end" << end << std::endl;
	if (start < left.length())
	{

		dependence->push_back(createOrGetFact(left.substr(start)));
		IDependence* Dep;
		if (prec == '*' || prec == '-')
		{
			if (prec == '*')
				Dep = new And(dependence);
			else if (prec == '-')
				Dep = new Xor(dependence);
			std::list<IDependence *> * listDep = new std::list<IDependence *>();
			listDep->push_back(Dep);
			result->push_back(listDep);
		}
		else
			result->push_back(dependence);
	}
	return result;
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


bool Parserv2::factExists(std::string const & fact)
{
	if (_rules.find(fact.c_str()) == _rules.end())
		return false;
	return true;
}

Fact * Parserv2::createOrGetFact(std::string const & fact)
{
	if (!factExists(fact))
		this->_rules[fact] = new Fact(fact);
	return static_cast<Fact*>(_rules[fact]);
}


char const * Parserv2::getType(IDependence * dependence)
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

std::map<std::string, IDependence*> const & Parserv2::getRules()
{
	return _rules;
}