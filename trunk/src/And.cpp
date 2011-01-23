#include "And.hpp"
#include "Fact.hpp"

And::And(IDependence *d1, IDependence *d2)
{
  _dep1 = d1;
  _dep2 = d2;
}

int And::getStatus()
{
  std::cout << _dep1->getName().c_str() << " & " << _dep2->getName().c_str() << std::endl;
  if (_dep1->getStatus() == ST_TRUE && _dep2->getStatus() == ST_TRUE)
    {
      std::cout << "And::getStatus() = ST_TRUE" << std::endl;
      return (ST_TRUE);
    }
  std::cout << "And::getStatus() = ST_FALSE" << std::endl;
  return (ST_FALSE);
}
