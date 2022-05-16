#include <fstream>
#include <iostream>
#include "Player.h"
#include "GUI.h"
#include "Block.h"
#include "Bullet.h"
#include "FactoryLibrary.h"
#include "ObjectFactory.h"

#include "ShootingStrategies.h"
//#include "IShootStrategy.h"
#include <map>
#include <algorithm>

using namespace std;
Player::Player(std::string animationFile, Vector2D position, const GUI* gui): AnimatedObject(animationFile, position, Object::Type::player,gui)
{
	// finals stuff: 
	behaviors['n'] = new normalShotStrategy();	// that's all it gets at first, its normal attack
	//behaviors['s'] = new specialShotStrategy();	// uncomment this to test out, new Super-Ranged attack
}


bool lastBlockOnScreen(const std::vector<Object*>& objects)
{
	int maxX{ 0 };
	for (auto object : objects)
	{
		if (object->getPosition().x + object->getDimensions().x > maxX && object->getName() != Object::Type::player)
		{
			maxX = object->getPosition().x + object->getDimensions().x;
		}
	}
	return maxX <= GUI::screenDimensions.x;
}

Object* Player::update(Object::Command command, const std::vector<Object*>& objects, FactoryLibrary* factories)
{
	Object* bullet{ nullptr };
	switch (command)
	{
	case Object::Command::right:moveRight(); break;
	case Object::Command::left:moveLeft(); break;
	case Object::Command::down:moveDown(); break;
	case Object::Command::up:moveUp(); break;
	case Object::Command::jump:moveJump(); break;
	case Object::Command::NA:noAction(); break;
	case Object::Command::shoot:
	{
		if (moveShoot())							
		{
			Initializers initializer(gui, objects);											
			initializer.creator = this;				
			map<char, IShootStrategy*>::iterator max = behaviors.begin();	// look for the behavior that has the highest precedence.
			for (auto i{ behaviors.begin() }; i != behaviors.end(); ++i)
			{
				if (i->second->precedence > max->second->precedence) max = i;
			}
			max->second->execute(bullet, factories, initializer);		// strategy pattern : this line MODIFIES THE BULLET returned before .update() returns.
		}
	}
		break;
	}


	doPhysics(objects);
	//sprite update and height adjustment
	int tempHeight{ (int)gui->getDimensions(this).y };
	updateSprite();
	position.y -= gui->getDimensions(this).y - tempHeight;

	//border detection.
	//left side of screen.
	if (position.x < 0)position.x = 0;


	//half screen. side-scrolling.
	else if (position.x > gui->screenDimensions.x / 2 && !lastBlockOnScreen(objects))
	{
		for (auto object : objects)
		{
			if (object->getName() == Object::Type::heart) continue;		// dont scroll the hearts.
			if (object->getName() != Object::Type::player)
			{
				object->setPosition({ object->getPosition().x - (position.x - gui->screenDimensions.x / 2), object->getPosition().y });
			}
		}
		position.x = gui->screenDimensions.x / 2;
	}
	//at the edge.
	else if (position.x + getDimensions().x >= GUI::screenDimensions.x) position.x = GUI::screenDimensions.x - getDimensions().x;
	for (auto object : objects)
	{
		if (object->getName() == Object::Type::enemy && collision(object, true))	// death by collision with enemy.
		{
			kill();
		}
	}
	if (position.y > GUI::screenDimensions.y)
	{
		kill();
	}
	if (life == 0) kill();	// death by getting shot.
 	return bullet;
}

Object* Player::copyMe()
{
	return new Player(*this);
}

void Player::moveRight()
{
	switch (state)
	{
	case State::stillLeft:
		state = State::stillRight;
		break;
	case State::stillRight:
		state = State::walkRight;
		break;
	case State::jumpRight:
	case State::walkRight:
		position.x += walkSpeed;
		break;
	
	}
}

void Player::moveLeft()
{
	switch (state)
	{
	case AnimatedObject::State::stillRight:
		state = AnimatedObject::State::stillLeft;
		break;
	case AnimatedObject::State::stillLeft:
		state = AnimatedObject::State::walkLeft;
		break;
	case AnimatedObject::State::jumpLeft:
	case AnimatedObject::State::walkLeft:
		position.x -= walkSpeed;
		break;
	default:
		break;
	}
}

void Player::moveDown()
{
	switch (state)
	{
	case AnimatedObject::State::stillLeft:
		state = AnimatedObject::State::crouchLeft;
		break;
	case AnimatedObject::State::stillRight:
		state = AnimatedObject::State::crouchRight;
		break;
	}
}

void Player::moveJump()
{
	if (velocity.y == 0)
	{
		switch (state)
		{
		case Player::State::stillRight:
			state = State::jumpRight;
 			velocity.y = -jumpStrength;
			break;
		case Player::State::stillLeft:
			state = State::jumpLeft;
			velocity.y = -jumpStrength;
			break;
		case Player::State::jumpRight:
			break;
		case Player::State::jumpLeft:
			break;
		case State::crouchLeft:
			state = State::jumpLeft;
			position.y += gravity.y + 10;
			break;
		case State::crouchRight:
			state = State::jumpRight;
			position.y += gravity.y + 10;
			break;
		default:
			break;
		}

	}
}

bool Player::moveShoot()	// this just checks if you are coming from a VALID STATE to shoot.
{
	switch (state)
	{
		case AnimatedObject::State::crouchLeft:
		case AnimatedObject::State::crouchRight:
		case AnimatedObject::State::stillLeft:
		case AnimatedObject::State::stillRight:
		case AnimatedObject::State::upLeft:
		case AnimatedObject::State::upRight:
			return true;
		default:
			return false;
	}
}

void Player::moveUp()
{
	switch (state)
	{
	case AnimatedObject::State::stillLeft:
		state = AnimatedObject::State::upLeft;
		break;
	case AnimatedObject::State::stillRight:
		state = AnimatedObject::State::upRight;
		break;
	}
}

void Player::noAction()
{
	switch (state)
	{
	case AnimatedObject::State::walkLeft:
	case AnimatedObject::State::crouchLeft:
	case AnimatedObject::State::upLeft:
		state = AnimatedObject::State::stillLeft;
		break;
	case AnimatedObject::State::walkRight:
	case AnimatedObject::State::crouchRight:
	case AnimatedObject::State::upRight:
		state = AnimatedObject::State::stillRight;
		break;
	}
}

