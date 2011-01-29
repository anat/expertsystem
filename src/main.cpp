#include "Fact.hpp"
#include "And.hpp"
#include "Parser.hpp"
#include "Parserv2.hpp"
#include <iostream>
#include <map>
int main(int argc, char **argv)
{

	char n1[] = "SuperProgram";
	char n2[] = "./RS_CUSTOM.txt";
	char n3[] = "Je peux rouler a maximum 130Km/h";
	char *test[] = {n1, n2, n3};
	argv = test;
	argc = 3;

	Parserv2 p(argv, argc);


	std::map<std::string, IDependence*> rules = p.getRules();

	// à debugguer pour que ca compile
	// rules.find("A");
	std::map<std::string, IDependence*>::iterator it = rules.begin();
	std::map<std::string, IDependence*>::iterator end = rules.end();

	int s = -1;
	for (; it != end; ++it)
		if (static_cast<Fact*>((it)->second)->getName() == argv[2])
		{
			s = static_cast<Fact*>((it)->second)->getStatus();
			break;
		}


	if (s == UNDEF)
		std::cout << (it)->first.c_str() << " n'est pas définit" << std::endl;
	else if (s == TRUE)
		std::cout << (it)->first.c_str() << " est vrai" << std::endl;
	else if (s == FALSE)
		std::cout << (it)->first.c_str() << " est faux" << std::endl;
	else
		std::cerr << "This fact doesn't exists" << std::endl;
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

	std::cout << "a.status = " << a->getStatus() << std::endl;
	return (0);
	}
	std::cerr << "Usage " << argv[0] << ": rules fact_to_check" << std::endl;*/
	return (1);
}
