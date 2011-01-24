#ifndef IDEPENDENCE_HPP_
# define IDEPENDENCE_HPP_

# include <iostream>


typedef enum Status{
	FALSE,
	TRUE,
	UNDEF
} TStatus;

class IDependence
{
	
public:
  virtual TStatus getStatus() = 0;
  virtual void setStatus(TStatus status) = 0;
  virtual std::string const & getName() const = 0; // A virer
};

#endif
