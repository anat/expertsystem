#ifndef AND_HPP_
# define AND_HPP_

# include "IDependence.hpp"
# include <iostream>
# include <list>

class And : public IDependence
{
private:
  std::list<IDependence *> * _dependencies;
  bool _interactiveMode;
public:
	
  And(std::list<IDependence *> * dependencies, bool interactiveMode);
  virtual TStatus getStatus();
  void setStatus(TStatus status);
};

#endif
