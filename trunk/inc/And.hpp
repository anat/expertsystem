#ifndef AND_HPP_
# define AND_HPP_

# include "IDependence.hpp"
# include <iostream>

class And : public IDependence
{
private:
  IDependence *_dep1;
  IDependence *_dep2;

public:
	
  And(IDependence *d1, IDependence *d2);
  virtual TStatus getStatus();
  void setStatus(TStatus status);
};

#endif
