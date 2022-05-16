#ifndef ANIMATEDOBJECT_H
#define ANIMATEDOBJECT_H
#include <map>
#include <vector>
#include <string>
#include "Object.h"

class AnimatedObject : public Object
{
public:
	AnimatedObject() = delete;
	AnimatedObject(std::string animationFile, Vector2D columnRow, Type name, const GUI* gui);
	
	int getCurrentSprite() const;
	
	enum class State { stillLeft, stillRight, walkLeft, walkRight, crouchLeft, crouchRight, upLeft, upRight, jumpLeft, jumpRight };
	State getState() const;

	
protected:
	void doPhysics(const std::vector<Object*> objects);
	void applyGravity();
	bool collision(const Object* object, bool full = false);	// by default, non-full collision is done unless full is specified as true.
	void updateSprite();

	const int walkSpeed{ 12 };
	const int jumpStrength{ 35 };
	
	static const float deltaT;
	static const Vector2D gravity;
	Vector2D velocity{ 0,0 };

	int currentSprite{ 0 };
	int currentAnimation{ 0 };
	State state{ State::stillRight };
	std::map<State, std::vector<int>> sprites;


};
#endif // !ANIMATION_H
