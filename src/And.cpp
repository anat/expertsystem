#include "And.hpp"
#include "Fact.hpp"

And::And(IDependence *d1, IDependence *d2)
{
  _dep1 = d1;
  _dep2 = d2;
}

TStatus And::getStatus()
{
  if (_dep1->getStatus() == TRUE && _dep2->getStatus() == TRUE)
      return (TRUE);
  return (FALSE);
}

void And::setStatus(TStatus status)
{
	std::cout << "Erreur : Cannot set a AND !" << std::endl;
}