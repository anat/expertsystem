#include "And.hpp"
#include "Fact.hpp"

And::And(std::list<IDependence *> * dependencies, bool interactiveMode) : _dependencies(dependencies), _interactiveMode(interactiveMode)
{
}

TStatus And::getStatus()
{
	std::list<IDependence *>::iterator it = _dependencies->begin(), end = _dependencies->end();
	if (!_interactiveMode)
		for (; it != end ; ++it)
			if ((*it)->getStatus() == UNDEF)
				return UNDEF;
	it = _dependencies->begin();
	end = _dependencies->end();
	for (; it != end ; ++it)
		if ((*it)->getStatus() == FALSE)
			return FALSE;
	return TRUE;
}

void And::setStatus(TStatus status)
{
	std::cerr << "Erreur : Cannot set a AND !" << std::endl;
}
