#ifndef XOR_HPP_
# define XOR_HPP_

# include "IDependence.hpp"
# include <iostream>

class Xor : public IDependence
{
private:
  IDependence *_dep1;
  IDependence *_dep2;

public:
	
  Xor(IDependence *d1, IDependence *d2);
  virtual TStatus getStatus();
  void setStatus(TStatus status);
};

#endif
