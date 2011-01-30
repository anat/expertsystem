#include "Fact.hpp"
#include "And.hpp"
#include "Parser.hpp"
#include <iostream>
#include <map>
#include <sstream>
int main(int argc, char **argv)
{

  char n1[] = "SuperProgram";
  char n2[] = "./RS_CUSTOM.txt";
  char n3[] = "Je peux rouler a maximum 130Km/h";
  char n4[] = "1";
  char *test[] = {n1, n2, n3, n4};
  argv = test;
  argc = 4;

	Parser p(argv, argc);


	std::map<std::string, IDependence*> rules = p.getRules();

	std::map<std::string, IDependence*>::iterator it = rules.begin(), end = rules.end();

	std::cout << "Result : " << std::endl << "----------===========----------" << std::endl;
	std::stringstream s(argv[2]);
	char * line = new char[1024];
	while (s.getline(line, 1024, ';'))
	{
		int status = -1;
		for (; it != end; ++it)
			if (static_cast<Fact*>((it)->second)->getName() == line)
			{
				status = static_cast<Fact*>((it)->second)->getStatus();
				break;
			}
		if (status == UNDEF)
			std::cout << (it)->first.c_str() << " n'est pas définit" << std::endl;
		else if (status == TRUE)
			std::cout << (it)->first.c_str() << " est vrai" << std::endl;
		else if (status == FALSE)
			std::cout << (it)->first.c_str() << " est faux" << std::endl;
		else
			std::cerr << "This fact doesn't exists" << std::endl;
		std::cout << std::endl << "----------===========----------" << std::endl;
	}
	
	return (1);
}
