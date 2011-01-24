#include "Fact.hpp"
#include "And.hpp"
#include "Parser.hpp"
#include <iostream>

int main(int argc, char **argv)
{

	char n1[] = "SuperProgram";
		char n2[] = "./RS_2.txt";
		char n3[] = "A";
		char *test[] = {n1, n2, n3};
      Parser p(test, 3);
      
	/*Fact *a = new Fact("A");
	Fact *b = new Fact("B");
	Fact *c = new Fact("C");
	Fact *d = new Fact("D");
	Fact *e = new Fact("E");
	
	e->setStatus(TRUE);
	
	And *cb = new And(c, b);
	a->addDependencie(cb);
	
	b->addDependencie(d);
	b->addDependencie(e);
	
	c->addDependencie(b);
      
      std::cout << "a.status = " << a->getStatus() << std::endl;
      return (0);
    }
  std::cerr << "Usage " << argv[0] << ": rules fact_to_check" << std::endl;*/
  return (1);
}
