#ifndef FACTORYLIBRARY_H
#define FACTORYLIBRARY_H

#include <map>

#include "Object.h"
class ObjectFactory;
class FactoryLibrary
{
public:
	FactoryLibrary();
	~FactoryLibrary();
	
	FactoryLibrary(const FactoryLibrary& src);	// copy constructor
	FactoryLibrary(FactoryLibrary&& src);		// move constructor
	FactoryLibrary& operator=(const FactoryLibrary& src) noexcept;	// copy assignment
	FactoryLibrary& operator=(FactoryLibrary&& src) noexcept;		// move assignment


	std::map<Object::Type, ObjectFactory*> library;
};

#endif // !FACTORYLIBRARY_H