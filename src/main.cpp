#include "Fact.hpp"
#include "And.hpp"
#include <iostream>

int main()//int argc, char **argv)
{
  /*
  Fact *a = new Fact("A");
  Fact *b = new Fact("B");
  Fact *c = new Fact("C");
  Fact *d = new Fact("D");
  Fact *e = new Fact("E");

  e->setStatus(ST_TRUE);

  //a->addDependencie(c);
  //a->addDependencie(b);
  And *cb = new And(c, b);
  a->addDependencie(cb);

  b->addDependencie(d);
  b->addDependencie(e);

  c->addDependencie(b);*/

  std::cout << "a.status = " << a->getStatus() << std::endl;
  return (0);
}
