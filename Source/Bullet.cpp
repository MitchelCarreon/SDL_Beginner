#include "Bullet.h"

#include "Enemy.h"
#include "Player.h"
#include <iostream>
#include <algorithm>
#include <utility>

Bullet::Bullet(Vector2D position, Object* shooter, Vector2D target, const GUI* gui) 
	: AnimatedObject("./Assets/data/noAnimation.txt", position, Object::Type::bullet, gui)
{
	this->shooter = shooter;
	velocity = position;			
	velocity.target(target, speed);
}

Object* Bullet::update(Object::Command command, const std::vector<Object*>& objects, FactoryLibrary* factories)
{
	--life;
	if (life <= 0) kill(); 
	position += velocity;

	for (auto object : objects)
	{
		if (collision(object))
		{
			kill();
		}
		else if ((object->getName() == Object::Type::enemy))
		{
			if (shooter != object && collision(object, true))
			{
				object->kill();	// kills enemy! makes it disappear.
				kill();	// kills bullet
				
			}
		}
		else if ((object->getName() == Object::Type::player))
		{
			if (shooter != object && collision(object, true))
			{
				((Player*)object)->decrementLife();		// decrements life by 1 each time
				
				if (((Player*)object)->behaviors.size() != 1)	// deletes the strategy/behavior with the highest precedence.
				{
 					((Player*)object)->behaviors.erase(std::max_element(((Player*)object)->behaviors.begin(), ((Player*)object)->behaviors.end(),
					[](std::pair<char, IShootStrategy*> i, std::pair<char, IShootStrategy*> j)
					{
						return i.second->precedence < j.second->precedence;
					}));
				}
	
				auto itr = std::find_if(objects.rbegin(), objects.rend(), [](Object* object) // used reverse iterator to start removing hearts from the right.
				{
						return object->getName() == Object::Type::heart;
				});
				(*itr)->kill();		// true display. this kills the heart if you get hit.

				std::cout << "Life Remaining: " << ((Player*)object)->getLife() << std::endl;	// display test.
				//}
				kill();	// kills bullet

			}
		}
	}
	return nullptr;	
}

Object* Bullet::copyMe()
{
	return new Bullet(*this);
}

//void Bullet::extendRange()	// for specialShot . snipe.
//{
//	if (((Player*)shooter)->getState() == AnimatedObject::State::crouchRight ||
//		((Player*)shooter)->getState() == AnimatedObject::State::crouchLeft)
//	{
//		life += 20;
//	}	
//}
