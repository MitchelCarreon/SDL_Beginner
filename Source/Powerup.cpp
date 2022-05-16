#include "Powerup.h"

PowerUp::PowerUp(std::string AnimationFile, Vector2D position, const GUI* gui) : AnimatedObject(AnimationFile, position, Object::Type::powerup, gui)
{

}
Object* PowerUp::update(Object::Command command, const std::vector<Object*>& objects, FactoryLibrary* libraries) 
{
	for (auto object : objects)
	{
		if (collision(object, true) && object->getName() == Object::Type::player)
		{
			((Player*)objects.back())->behaviors['s'] = new specialShotStrategy();	// SNIPE: this only works when you're crouched (sniping position).
			//((Player*)objects.back())->behaviors['r'] = new areaShotStrategy();			// this doesn't work.
			kill(); // makes this powerup disappear.
		}
	}
	return nullptr;
}
Object* PowerUp::copyMe() 
{
	return new PowerUp(*this); 
}