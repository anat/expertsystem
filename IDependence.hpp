#ifndef IDEPENDENCE_HPP_
# define IDEPENDENCE_HPP_

# include <iostream>

class IDependence
{
public:
  virtual int getStatus() = 0;
  virtual std::string const & getName() const = 0;
};

#endif
