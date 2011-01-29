#include "Xor.hpp"
#include "Fact.hpp"

Xor::Xor(std::list<IDependence *> * dependencies) : _dependencies(dependencies)
{
	std::cout << "XOR spawn with length : " << _dependencies->size() <<  std::endl;
	//std::list<IDependence *>::iterator it = _dependencies->begin();
	//std::list<IDependence *>::iterator end = _dependencies->end();
	//std::cout << "Xor : ";
	//while (it != end)
	//{
	//	std::cout <<  static_cast<Fact*>(*it)->getName().c_str() << ",";
	//	++it;
	//}
	//std::cout << "." << std::endl;
}

TStatus Xor::getStatus()
{
	//std::list<IDependence *>::iterator it = _dependencies->begin(), end = _dependencies->end();
	//while (it != end)
	//{
	//	Xor * prec = static_cast<Xor*>(*it);
	//	++it;
	//	if (
	//	if (->getStatus() == FALSE)
	//		return FALSE;
	//	
	//}
	return TRUE;
}

void Xor::setStatus(TStatus status)
{
	std::cout << "Erreur : Cannot set a XOR !" << std::endl;
}