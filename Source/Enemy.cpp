#include "Enemy.h"
#include "GUI.h"
#include "Player.h"
#include "FactoryLibrary.h"

// finals stuff

#include"ObjectFactory.h"
#include "Bullet.h"


Enemy::Enemy(std::string animationFile, Vector2D position, const GUI* gui): AnimatedObject(animationFile, position, Object::Type::enemy, gui)
{

}

Object* Enemy::update(Object::Command command, const std::vector<Object*>& objects, FactoryLibrary* factories)
{
	Object* bullet{ nullptr };			// final quest stuff
	float originalPosition{ position.y };	// for collision.

	auto objectIter{objects.begin()};
	while (objectIter != objects.end() && (*objectIter)->getName() != Object::Type::player)
	{
		objectIter++;
	}
	if (objectIter != objects.end())
	{
		Player* player1{ (Player*)(*objectIter) };

		if (isWithinRange(objects) && canShoot(objects))
		{
			Initializers initializer(gui, objects);
			initializer.creator = this;				
			bullet = factories->library.find(Object::Type::bullet)->second->create(initializer);
		}
		else if (position > player1->getPosition()) state = State::stillLeft;
		else if (position < player1->getPosition()) state = State::stillRight;
		
		for (auto object : objects)	// this is so that it goes back to its original position after shooting.
		{
			if (collision(object, true))position.y = originalPosition;
		}
	}
	int tempHeight{ (int)gui->getDimensions(this).y };
	updateSprite();
	position.y -= gui->getDimensions(this).y - tempHeight;
	
	return bullet;
}

Object* Enemy::copyMe()
{
	return new Enemy(*this);
}

// ALL FINALS STUFF
bool Enemy::isWithinRange(const std::vector<Object*>& objects)
{
	auto itr{ objects.begin() };
	for (; itr != objects.end() && (*itr)->getName() != Object::Type::player; ++itr) {}	// find the player in the vector
	if (itr != objects.end())
	{
		Player* player{ (Player*)(*itr) };
		if (player->getPosition().x < (this->position.x) && player->getPosition().x > (this->position.x - 200)
			|| (player->getPosition().x > (this->position.x) && player->getPosition().x <(this->position.x + 200)))
		{
			if  (player->getPosition().y == this->position.y) return true;
		}
		else return false;
		
	}
	return false;
}

bool Enemy::canShoot(const std::vector<Object*>& objects)
{
	for (auto object : objects)
	{
		if (object->getName() == Object::Type::bullet)
		{
			if (((Bullet*)object)->shooter == this)
			{
				return false;
			}
		}
	}
	return true;
}
