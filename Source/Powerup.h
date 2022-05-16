#ifndef POWERUP_H
#define POWERUP_H

#include "AnimatedObject.h"
#include "GUI.h"
#include "ShootingStrategies.h"

class PowerUp : public AnimatedObject		// the only reason we inherit from AnimatedObject is we want the logic from collision().
{
public:
	PowerUp(std::string AnimationFile, Vector2D position, const GUI* gui);
	Object* update(Object::Command command, const std::vector<Object*>& objects, FactoryLibrary* libraries) override;
	Object* copyMe() override;
};
#endif // !POWERUP_H

