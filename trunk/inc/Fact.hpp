#ifndef FACT_HPP_
# define FACT_HPP_

# include "IDependence.hpp"
# include "And.hpp"
# include <iostream>
# include <list>

# define ST_FALSE 0
# define ST_TRUE  1
# define ST_UNDEF 2

class Fact : public IDependence
{
private:
  int _status;
  std::string _name;
  std::list<IDependence *> _dependencies;

public:
  Fact(std::string const & name);
  virtual std::string const & getName() const;
  virtual int getStatus();
  void setStatus(int status);
  void addDependencie(IDependence *dependencie);
};

#endif
