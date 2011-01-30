#include "Fact.hpp"

Fact::Fact(std::string const & name)
{
	_name = name;
	std::cout << _name.c_str() << " a SPAWN !" << std::endl;
	_status = UNDEF;
}

std::string const & Fact::getName() const
{
	return _name;
}

TStatus Fact::getStatus()
{
	std::list<IDependence *>::const_iterator it = _dependencies.begin();
	std::list<IDependence *>::const_iterator ite = _dependencies.end();
	std::string tmp;

	if (_status == UNDEF)
	{
		while (it != ite)
		{
			/* std::cout << _name.c_str() << ": " << (*it)->getName().c_str() << std::endl;*/
			if ((*it)->getStatus() == TRUE)
				return ((_status = TRUE));
			++it;
		}
	    std::cout << this->getName() << " ?" << std::endl;
	    std::cin >> tmp;
	    if (tmp == std::string("yes"))
	      return ((_status = TRUE));
	    else
	      return ((_status = FALSE));
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
