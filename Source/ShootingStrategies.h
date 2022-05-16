#ifndef SHOOTINGSTRATEGIES_H
#define SHOOTINGSTRATEGIES_H

#include "IShootStrategy.h"
#include "Bullet.h"
#include "Player.h"
#include "FactoryLibrary.h"

#include "Object.h"
#include "engine.h"
#include <algorithm>

#include "Enemy.h"



class normalShotStrategy : public IShootStrategy
{
public:
	normalShotStrategy() : IShootStrategy(5) {}; // behavior with the highest precedence will be EXECUTED if certain conditions are met (for sniping: crouch to extend bullet range)
	void execute(Object*& bullet, const FactoryLibrary* factories, Initializers& initializer) override
	{
		bullet = factories->library.find(Object::Type::bullet)->second->create(initializer); 
	}
	
};


class specialShotStrategy : public IShootStrategy	// i want to RENAME this to : snipeShotStrategy (only works when crouched/sniping position)
{
public:
	specialShotStrategy() : IShootStrategy(10) {};	// constructor for setting the precedence. 
	void execute(Object*& bullet, const FactoryLibrary* factories, Initializers& initializer) override
	{
		bullet = factories->library.find(Object::Type::bullet)->second->create(initializer); // make the bullet and set the trajectory first.
		if (((Player*)((Bullet*)bullet)->shooter)->getState() == AnimatedObject::State::crouchRight ||
			((Player*)((Bullet*)bullet)->shooter)->getState() == AnimatedObject::State::crouchLeft)
		{
			((Bullet*)bullet)->life += 20;
		}
	}
};

// TO ADD MORE SPECIAL MOVES: start here.

class areaShotStrategy : public IShootStrategy	// this isn't used.
{
public:
	areaShotStrategy() : IShootStrategy(15) {};
	void execute(Object*& bullet, const FactoryLibrary* factories, Initializers& initializer) override
	{
		bullet = factories->library.find(Object::Type::bullet)->second->create(initializer); // make the bullet and set the trajectory first.
		
	}
	
};



#endif