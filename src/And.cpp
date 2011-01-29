#include "And.hpp"
#include "Fact.hpp"

And::And(std::list<IDependence *> * dependencies) : _dependencies(dependencies)
{
	std::cout << "AND spawn with length : " << _dependencies->size() <<  std::endl;
	//std::list<IDependence *>::iterator it = _dependencies->begin();
	//std::list<IDependence *>::iterator end = _dependencies->end();
	//std::cout << "And : ";
	//while (it != end)
	//{
	//	std::cout <<  static_cast<Fact*>(*it)->getName().c_str() << ",";
	//	++it;
	//}
	//std::cout << "." << std::endl;
}

TStatus And::getStatus()
{
	std::list<IDependence *>::iterator it = _dependencies->begin(), end = _dependencies->end();
	for (; it != end ; ++it)
		if ((*it)->getStatus() == FALSE)
			return FALSE;
	return TRUE;
}

void And::setStatus(TStatus status)
{
	std::cout << "Erreur : Cannot set a AND !" << std::endl;
}