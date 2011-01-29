#include "And.hpp"
#include "Fact.hpp"

And::And(std::list<IDependence *> * dependencies) : _dependencies(dependencies)
{
}

TStatus And::getStatus()
{
	return TRUE;
  //if (_dep1->getStatus() == TRUE && _dep2->getStatus() == TRUE)
  //    return (TRUE);
  //return (FALSE);
}

void And::setStatus(TStatus status)
{
	std::cout << "Erreur : Cannot set a AND !" << std::endl;
}