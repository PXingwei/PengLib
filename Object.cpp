#include <cstdlib>
#include "Object.h"

namespace PengLib
{
	/**Overload the new operator */
    	void* Object::operator new(unsigned int size) throw()
	{
		return malloc(size);
	}
	/**Overload the new[] operator */
  	void* Object::operator new[](unsigned int size) throw()
	{
		return  malloc(size);
	}
	/**Overload the delete operator */
    	void Object::operator delete (void* pn)
	{
		free(pn);
	}
	/**Overload the delete[] operator */
	void Object::operator delete[] (void* pn)
	{
		free(pn);
	}
	/**Overload the == operator */
    	bool Object::operator == (const Object& e)
    	{
        	return (this == &e);
    	}
    	/**Overload the != operator */
    	bool Object::operator != (const Object& e)
    	{
        	return (this != &e);
    	}

	Object::~Object() {}
}
