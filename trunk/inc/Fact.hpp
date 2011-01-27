#ifndef FACT_HPP_
# define FACT_HPP_

# include "IDependence.hpp"
# include "And.hpp"
# include <iostream>
# include <list>


class Fact : public IDependence
{
private:
  TStatus _status;
  std::string _name;
  std::list<IDependence *> _dependencies;

public:
  Fact(std::string const & name);
  virtual std::string const & getName() const;
  virtual TStatus getStatus();
  void setStatus(TStatus status);
  void addDependence(IDependence *dependence);
  void showStatus();
};

#endif
