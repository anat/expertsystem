#ifndef NOT_HPP_
# define NOT_HPP_

# include "IDependence.hpp"
# include "Fact.hpp"

class Not : public Fact
{
public:
	inline Not(std::string const & name, bool interactiveMode) : Fact(name, interactiveMode) {}
};

#endif
