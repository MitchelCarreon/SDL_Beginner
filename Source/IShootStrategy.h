#ifndef ISHOOTSTRATEGY_H
#define ISHOOTSTRATEGY_H

#include "Bullet.h"
#include "ObjectFactory.h"

class IShootStrategy
{
public:
	IShootStrategy(int precedence) : precedence(precedence) {};
	virtual void execute(Object*& bullet, const FactoryLibrary* factories, Initializers& initializer) = 0;
	int precedence;	// this determines which shooting behavior will occur once spacebar is pressed.
};

#endif
