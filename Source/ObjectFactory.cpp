#include "ObjectFactory.h"

#include "Block.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "GUI.h"

// finals stuff
#include "Powerup.h"

// BlockFactory 
Object* BlockFactory::create(Initializers list)
{
	return ((Object*)(new Block(list.position, list.name, list.gui)));
}

Object* PlayerFactory::create(Initializers list)
{
	return ((Object*)(new Player("./Assets/data/animation.txt", list.position, list.gui))); 
}
Object* EnemyFactory::create(Initializers list)
{
	Object* temp {((Object*)(new Enemy("./Assets/data/EnemyAnimations.txt", list.position, list.gui)))};
	((Enemy*)temp)->setPosition({ list.position.x, list.position.y -= list.gui->getDimensions(temp).y - list.gui->columnRowDimensions.y });
	return temp;
}

Object* BulletFactory::create(Initializers list)	// assigns the trajectory and starting position of the bullet based on player.state
{
	Vector2D target;
	switch (((Player*)list.creator)->getState())
	{
	case AnimatedObject::State::stillRight:
	case AnimatedObject::State::stillLeft:
		list.creator->setPosition({ ((Player*)list.creator)->getPosition().x, ((Player*)list.creator)->getPosition().y + 12 });		// this keeps the bullet coming out of the edge of the gun.
		if (((Player*)list.creator)->getState() == AnimatedObject::State::stillRight)
		{
			target = { (list.creator->getPosition().x + 50), list.creator->getPosition().y  };
			list.position = { (list.creator->getPosition().x + list.creator->getDimensions().x), list.creator->getPosition().y /*+ 20 */ };
		}
		else
		{
			target = { (list.creator->getPosition().x - 50), list.creator->getPosition().y  };
			list.position =  list.creator->getPosition();
		}
		break;

	case AnimatedObject::State::upRight:
	case AnimatedObject::State::upLeft:
		target = { list.creator->getPosition().x, (list.creator->getPosition().y - 10000) };			
		if (((Player*)list.creator)->getState() == AnimatedObject::State::upRight)
		{
			list.position = { list.creator->getPosition().x + 11, list.creator->getPosition().y };
		}
		else list.position = { list.creator->getPosition() };
		break;

	case AnimatedObject::State::crouchLeft:
	case AnimatedObject::State::crouchRight:
		list.creator->setPosition({ ((Player*)list.creator)->getPosition().x, ((Player*)list.creator)->getPosition().y + 5 });		// this keeps the bullet coming out of the edge of the gun.
		if (((Player*)list.creator)->getState() == AnimatedObject::State::crouchRight)
		{
			target = { (list.creator->getPosition().x + 50), list.creator->getPosition().y };
			list.position = { (list.creator->getPosition().x + list.creator->getDimensions().x), list.creator->getPosition().y };
		}
		else
		{
			target = { (list.creator->getPosition().x - 50), list.creator->getPosition().y };
			list.position = list.creator->getPosition();
		}
		break;
	}
	return ((Object*)new Bullet(list.position, list.creator, target, list.gui));
}

Object* PowerUpFactory::create(Initializers list)
{
	Object* temp{ new PowerUp("./Assets/data/noAnimation.txt", list.position, list.gui) };
	((PowerUp*)temp)->setPosition({ list.position.x, list.position.y -= list.gui->getDimensions(temp).y/2 - list.gui->columnRowDimensions.y/2});	// put it on top of the block.
	return temp;
}
