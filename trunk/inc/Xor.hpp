#ifndef XOR_HPP_
# define XOR_HPP_

# include "IDependence.hpp"
# include <iostream>
# include <list>

class Xor : public IDependence
{
private:
	std::list<IDependence *> * _dependencies;

public:
	
  Xor(std::list<IDependence *> * dependencies);
  virtual TStatus getStatus();
  void setStatus(TStatus status);
};

#endif
