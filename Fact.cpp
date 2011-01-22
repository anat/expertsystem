#include "Fact.hpp"

Fact::Fact(std::string const & name)
{
  _name = name;
  _status = ST_UNDEF;
}

std::string const & Fact::getName() const
{
  return _name;
}

int Fact::getStatus()
{
  std::list<IDependence *>::const_iterator it = _dependencies.begin();
  std::list<IDependence *>::const_iterator ite = _dependencies.end();

  if (_status == ST_UNDEF)
    {
      while (it != ite)
	{
	  std::cout << _name << ": " << (*it)->getName() << std::endl;
	  if ((*it)->getStatus() == ST_TRUE)
	    return ((_status = ST_TRUE));
	  ++it;
	}
    }
  return _status;
}

void Fact::setStatus(int status)
{
  _status = status;
}

void Fact::addDependencie(IDependence *dependencie)
{
  _dependencies.push_back(dependencie);
}
