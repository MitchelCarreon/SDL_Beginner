#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H
#include "Object.h"
class GUI;
struct Initializers
{
	Initializers(const GUI* gui, std::vector<Object*> objects) :gui(gui), objects(objects){}
	Vector2D position{ 0,0 };
	Object::Type name{ Object::Type::none };
	const GUI* gui;
	std::vector<Object*> objects;
	Object* creator{ nullptr };
};
class ObjectFactory
{
public:
	virtual Object* create(Initializers list) = 0;
};

class BlockFactory : public ObjectFactory
{
public:
	Object* create(Initializers list) override;
};

class PlayerFactory : public ObjectFactory
{
public:
	Object* create(Initializers list) override;
};

class EnemyFactory : public ObjectFactory
{
public:
	Object* create(Initializers list) override;
};

class BulletFactory : public ObjectFactory
{
public:
	Object* create(Initializers list) override;
};

// finals stuff
class PowerUpFactory : public ObjectFactory
{
public:
	Object* create(Initializers list) override;
};

#endif // !OBJECTFACTORY_H