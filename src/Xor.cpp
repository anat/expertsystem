#include "Xor.hpp"
#include "Fact.hpp"

Xor::Xor(std::list<IDependence *> * dependencies, bool interactiveMode) : _dependencies(dependencies), _interactiveMode(interactiveMode)
{
}

TStatus Xor::getStatus()
{
	std::list<IDependence *>::iterator it = _dependencies->begin(), end = _dependencies->end();
	if (!_interactiveMode)
		for (; it != end ; ++it)
			if ((*it)->getStatus() == UNDEF)
				return UNDEF;
	
	bool allTrue = true, noTrue = true;

	it = _dependencies->begin();
	end = _dependencies->end();
	for (; it != end ; ++it)
	{
		// CHECK 0 ^ 0 ^ 0
		if ((*it)->getStatus() == TRUE)
		{
			// all value in set is not true
			noTrue = false;
			break;
		}
		// CHECK 1 ^ 1 ^ 1
		else if ((*it)->getStatus() == FALSE)
		{
			allTrue = false;
			break;
		}
	}
	if (noTrue || allTrue)
		return FALSE;
	return TRUE;
}

void Xor::setStatus(TStatus status)
{
	std::cerr << "Erreur : Cannot set a XOR !" << std::endl;
}