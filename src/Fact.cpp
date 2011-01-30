#include "Fact.hpp"

Fact::Fact(std::string const & name, bool interactiveMode) : _interactiveMode(interactiveMode), _name(name), _status(UNDEF)
{
}

std::string const & Fact::getName() const
{
	return _name;
}

TStatus Fact::getStatus()
{
	std::list<IDependence *>::const_iterator it = _dependencies.begin();
	std::list<IDependence *>::const_iterator ite = _dependencies.end();
	char * response = new char[128];

	if (_status == UNDEF)
	{
		while (it != ite)
		{
			if ((*it)->getStatus() == TRUE)
				return ((_status = TRUE));
			++it;
		}

		if (_interactiveMode)
		{
			input:
			std::cout << this->getName().c_str() << " ? (\"yes\" or \"no\")" << std::endl;
			std::cin.getline(response, 128);

			if (std::string("yes").compare(response) == 0)
				return ((_status = TRUE));
			else if (std::string("no").compare(response) == 0)
				return ((_status = FALSE));
			else
				goto input;
		}
	}
	return _status;
}

void Fact::showStatus()
{
	TStatus s = this->getStatus();
	if (s == UNDEF)
		std::cout << this->_name.c_str() << " n'est pas définit" << std::endl;
	else if (s == TRUE)
		std::cout << this->_name.c_str()  << " est vrai" << std::endl;
	else if (s == FALSE)
		std::cout << this->_name.c_str()  << " est faux" << std::endl;
}

void Fact::setStatus(TStatus status)
{
	_status = status;
}

void Fact::addDependence(IDependence *dependence)
{
	_dependencies.push_back(dependence);
}
