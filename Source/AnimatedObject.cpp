#include <fstream>
#include <iostream>
#include "AnimatedObject.h"
#include "Block.h"
#include "GUI.h"
using namespace std;
const Vector2D AnimatedObject::gravity{ 0.0f, 10.0f };
const float AnimatedObject::deltaT{ 0.5f };
AnimatedObject::AnimatedObject(std::string animationFile, Vector2D position, Type name, const GUI* gui): Object(position, name, gui)
{
	fstream fin;
	fin.open(animationFile);
	if (!fin.is_open()) cout << "File does not exist!";


	int numStates;

	fin >> numStates;
	for (int i{ 0 }; i < numStates; i++)
	{
		int numAnimations;
		fin >> numAnimations;
		for (int j{ 0 }; j < numAnimations; j++)
		{
			int spriteSequence;
			fin >> spriteSequence;
			sprites[(State)i].push_back(spriteSequence);
		}
	}
	updateSprite();
}
int AnimatedObject::getCurrentSprite() const
{
	return currentSprite;
}
AnimatedObject::State AnimatedObject::getState() const
{
	return state;
}
void AnimatedObject::updateSprite()
{
	currentAnimation++;
	currentAnimation %= sprites[state].size();

	currentSprite = sprites[state][currentAnimation];
}
void AnimatedObject::doPhysics(const std::vector<Object*> objects)
{
	applyGravity();

	for (const auto& object : objects)
	{
		switch (object->getName())
		{
		case Object::Type::bridge_center:
		case Object::Type::bridge_end:
		case Object::Type::bridge_start:
		case Object::Type::top_block:
		case Object::Type::water_top:
			if (collision(object) && velocity.y > 0)
			{
				position.y = object->getPosition().y - gui->getDimensions(this).y;
				velocity.y = 0;
				if (state == AnimatedObject::State::jumpLeft)
				{
					state = AnimatedObject::State::stillLeft;
				}
				else if (state == AnimatedObject::State::jumpRight)
				{
					state = AnimatedObject::State::stillRight;
				}
			}
	
		}

	}
}

void AnimatedObject::applyGravity()
{
	position.y += deltaT * velocity.y;
	velocity.y += deltaT * gravity.y;
}

bool AnimatedObject::collision(const Object* object, bool full)
{
	bool leftInColumn{ (position.x >= object->getPosition().x
					&& position.x <= object->getPosition().x + object->getDimensions().x) };
	bool rightInColumn{ (position.x + getDimensions().x >= object->getPosition().x
		&& position.x + getDimensions().x <= object->getPosition().x + object->getDimensions().x) };
	bool sameColumn{ leftInColumn || rightInColumn };
	bool sameRow{ false };

	if (sameColumn)
	{
		bool objectTopInThis{ (object->getPosition().y > position.y
				&& object->getPosition().y < position.y + getDimensions().y) };

		if (full)
		{
			bool topInRow{ (position.y >= object->getPosition().y
				&& position.y < object->getPosition().y + object->getDimensions().y) };
			bool bottomInRow{ (position.y + getDimensions().y > object->getPosition().y
			&& position.y + getDimensions().y <= object->getPosition().y + object->getDimensions().y) };
			sameRow = topInRow || bottomInRow || objectTopInThis;
		}
		else
		{
			bool bottomInRow{ (position.y + getDimensions().y > object->getPosition().y
				&& position.y + getDimensions().y <= object->getPosition().y + gravity.y) };//object->getDimensions().y) };
			sameRow = bottomInRow || objectTopInThis;
		}
	}

	return sameRow && sameColumn;
}