#include "Fact.hpp"

Fact::Fact(std::string const & name)
{
  _name = name;
  _status = Status::UNDEF;
}

std::string const & Fact::getName() const
{
  return _name;
}

TStatus Fact::getStatus()
{
  std::list<IDependence *>::const_iterator it = _dependencies.begin();
  std::list<IDependence *>::const_iterator ite = _dependencies.end();

  if (_status == Status::UNDEF)
    {
		  while (it != ite)
		{
		  std::cout << _name.c_str() << ": " << (*it)->getName().c_str() << std::endl;
		  if ((*it)->getStatus() == Status::TRUE)
			return ((_status = Status::TRUE));
		  ++it;
		}
    }
  return _status;
}

void Fact::setStatus(TStatus status)
{
  _status = status;
}

void Fact::addDependencie(IDependence *dependencie)
{
  _dependencies.push_back(dependencie);
}
