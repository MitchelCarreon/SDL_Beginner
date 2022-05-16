#include "FactoryLibrary.h"
#include "ObjectFactory.h"

// finals stuff
#include "Powerup.h"


FactoryLibrary::FactoryLibrary()
{
	// The constructor needs to create ObjectFactory*’s for 
	// the factories for each type of object that can be created in the game. 
	int numblockTypes{ 13 };			// from 12 to 13, because of heart. CANCELLED: from 13 to 14, because of powerup.
	for (int i{ 0 }; i < numblockTypes; ++i)
	{
		library[(Object::Type)i] = new BlockFactory();
	}
	library[Object::Type::bullet] = new BulletFactory();
	library[Object::Type::player] = new PlayerFactory();
	library[Object::Type::enemy] = new EnemyFactory();
	library[Object::Type::powerup] = new PowerUpFactory(); // finals stuff
}

FactoryLibrary::~FactoryLibrary()
{
	for (auto element : library)
	{
		delete element.second;
	}
}

FactoryLibrary::FactoryLibrary(const FactoryLibrary& src)
{
	library.insert(src.library.begin(), src.library.end());
}

FactoryLibrary::FactoryLibrary(FactoryLibrary&& src)
{
	library.insert(src.library.begin(), src.library.end());
	for (auto object : src.library)
	{
		delete object.second;			// deallocate memory
	}
	
}

FactoryLibrary& FactoryLibrary::operator=(const FactoryLibrary& src) noexcept
{
	for (auto object : library) if (object.second != nullptr) delete object.second;
	library.clear();
	library.insert(src.library.begin(), src.library.end());
	return *this;
}

FactoryLibrary& FactoryLibrary::operator=(FactoryLibrary&& src) noexcept
{
	for (auto object : library) if (object.second != nullptr) delete object.second;
	library.clear();
	library.insert(src.library.begin(), src.library.end());

	for (auto object : src.library) delete object.second;	// deallocate memory 
	return *this;
}
