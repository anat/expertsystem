#include "Xor.hpp"
#include "Fact.hpp"

Xor::Xor(std::list<IDependence *> * dependencies) : _dependencies(dependencies)
{
}

TStatus Xor::getStatus()
{
	return TRUE;
  //if (_dep1->getStatus() == TRUE ^ _dep2->getStatus() == TRUE)
  //    return (TRUE);
  //return (FALSE);
}

void Xor::setStatus(TStatus status)
{
	std::cout << "Erreur : Cannot set a XOR !" << std::endl;
}