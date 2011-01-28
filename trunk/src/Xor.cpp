#include "Xor.hpp"
#include "Fact.hpp"

Xor::Xor(IDependence *d1, IDependence *d2)
{
  _dep1 = d1;
  _dep2 = d2;
}

TStatus Xor::getStatus()
{
  if (_dep1->getStatus() == TRUE ^ _dep2->getStatus() == TRUE)
      return (TRUE);
  return (FALSE);
}

void Xor::setStatus(TStatus status)
{
	std::cout << "Erreur : Cannot set a XOR !" << std::endl;
}